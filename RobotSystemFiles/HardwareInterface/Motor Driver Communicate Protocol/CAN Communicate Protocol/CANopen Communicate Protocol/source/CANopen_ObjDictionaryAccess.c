/*
 * CANopen_ObjDictionaryAccess.c
 *
 *  Created on: 2017-3-15
 *      Author: e701
 */

#include "../include/CO_DataModel.h"
#include "../include/DataParamPreDefine.h"
#include "../include/FuncDeclaration.h"
#include "../include/FuncPointerModel.h"

/*************************************
 *
 *	函数说明：	读取对象字典中的内容
 *
 *	@param		*d			参数结构体
 *	@param		wIndex		索引
 *	@param		bSubindex	子索引
 *	@param		*pDestData	将数据读取到的目标缓存空间指针
 *	@param		*pExpectedSize	期望读取的大小
 *	@param		*pDataType	数据类型
 *	@param		checkAccess	是否检查可读取性
 *	@param		endianize	大小头方式选择
 *
 *************************************/
UNS32 getODentry(
		CO_Data* d,
		UNS16 wIndex,
		UNS8 bSubindex,
		void * pDestData,
		UNS32 * pExpectedSize,
		UNS8 * pDataType,
		UNS8 checkAccess,
		UNS8 endianize)
{
	/* DO NOT USE MSG_ERR because the macro may send a PDO -> infinite loop if it fails. */
	UNS32 errorCode;
	UNS32 szData;
	const indextable *ptrTable;
	ODCallback_t *Callback;

	ptrTable = (*d->scanIndexOD)(wIndex, &errorCode, &Callback);

	if (errorCode != OD_SUCCESSFUL)
		return errorCode;

	if( ptrTable->bSubCount <= bSubindex ) {
		/* Subindex not found */
		return OD_NO_SUCH_SUBINDEX;
	}

	if (checkAccess && (ptrTable->pSubindex[bSubindex].bAccessType & WO)) {
		return OD_READ_NOT_ALLOWED;
	}

	if (pDestData == 0) {
		return SDOABT_GENERAL_ERROR;
	}

	if (ptrTable->pSubindex[bSubindex].size > *pExpectedSize) {
		/* Requested variable is too large to fit into a transfer line, inform    *

		 * the caller about the real size of the requested variable.              */
		*pExpectedSize = ptrTable->pSubindex[bSubindex].size;
		return SDOABT_OUT_OF_MEMORY;
	}

	*pDataType = ptrTable->pSubindex[bSubindex].bDataType;
	szData = ptrTable->pSubindex[bSubindex].size;

	if(*pDataType != visible_string) {//��ptrTable->pSubindex[bSubindex].pObject����szData����ݵ�pDestData
		memcpy_2(pDestData, ptrTable->pSubindex[bSubindex].pObject,szData);
		*pExpectedSize = szData;
	}
	else{
		/* Copy null terminated string to user, and return discovered size */
		UNS8 *ptr = (UNS8*)ptrTable->pSubindex[bSubindex].pObject;
		UNS8 *ptr_start = ptr;

		/* *pExpectedSize IS < szData . if null, use szData */
		UNS8 *ptr_end = ptr + (*pExpectedSize ? *pExpectedSize : szData) ;
		UNS8 *ptr_dest = (UNS8*)pDestData;

		while( *ptr && ptr < ptr_end){
			*(ptr_dest++) = *(ptr++);
		}

		*pExpectedSize = (UNS32) (ptr - ptr_start);
		/* terminate string if not maximum length */
		if (*pExpectedSize < szData)
			*(ptr) = 0;
	}

	return OD_SUCCESSFUL;
}

/**********************************************
 *
 *	函数说明：	写入数据到 Object Dictionary
 *
 **********************************************/
UNS32 setODentry( CO_Data* d,
		UNS16 wIndex,
		UNS8 bSubindex,
		void * pSourceData,
		UNS32 * pExpectedSize,
		UNS8 checkAccess,
		UNS8 endianize)
{
	UNS32 dataSize;
	UNS8 dataType;
	UNS32 errorCode;
	const indextable *ptrTable;
	ODCallback_t *Callback;

	ptrTable =(*d->scanIndexOD)(wIndex, &errorCode, &Callback);
	if (errorCode != OD_SUCCESSFUL)
		return errorCode;

	if( ptrTable->bSubCount <= bSubindex ) {
		return OD_NO_SUCH_SUBINDEX;/* Subindex not found */
	}

	if (checkAccess && (ptrTable->pSubindex[bSubindex].bAccessType == RO)) {
		return OD_WRITE_NOT_ALLOWED;
	}

	dataType = ptrTable->pSubindex[bSubindex].bDataType;
	dataSize = ptrTable->pSubindex[bSubindex].size;

	if( *pExpectedSize == 0 || *pExpectedSize == dataSize ||
			/* allow to store a shorter string than entry size */
			(dataType == visible_string && *pExpectedSize < dataSize))
	{
		errorCode = 0;//(*d->valueRangeTest)(dataType, pSourceData);
		if (errorCode) {
			return errorCode;
		}

		memcpy_1(ptrTable->pSubindex[bSubindex].pObject, pSourceData, *pExpectedSize);

		/*
		 *  说明：	对特定类型数据的判断，
		 *  		我们所定义的对象字典中没有 visible_string 类型的数据，
		 * 			所以不进该判断
		 */
		if(dataType == visible_string && *pExpectedSize < dataSize) {
			((UNS8*)ptrTable->pSubindex[bSubindex].pObject)[*pExpectedSize] = 0;
		}

		*pExpectedSize = dataSize;

		/*
		 * 	说明：	 Callbacks，Callback 函数指针在上面 scanIndexOD 中进行赋值
		 * 			这个函数内容不知道在哪里有初始化过，应该一直都为 NULL，所以不进行调用
		 */
		if(Callback && Callback[bSubindex]){
			errorCode = (Callback[bSubindex])(d, ptrTable, bSubindex);
			if(errorCode != OD_SUCCESSFUL) {
				return errorCode;
			}
		}
		return OD_SUCCESSFUL;
	}
	else{
		*pExpectedSize = dataSize;
		return OD_LENGTH_DATA_INVALID;
	}
}

const indextable * scanIndexOD (CO_Data* d, UNS16 wIndex, UNS32 *errorCode, ODCallback_t **Callback)
{
  	return (*d->scanIndexOD)(wIndex, errorCode, Callback);
}

UNS32 RegisterSetODentryCallBack(CO_Data* d, UNS16 wIndex, UNS8 bSubindex, ODCallback_t Callback)
{
	UNS32 errorCode;
	ODCallback_t *CallbackList;
	const indextable *odentry;

	odentry = scanIndexOD (d, wIndex, &errorCode, &CallbackList);
	if(errorCode == OD_SUCCESSFUL  &&  CallbackList  &&  bSubindex < odentry->bSubCount)
		CallbackList[bSubindex] = Callback;
	return errorCode;
}


/************************************************
 *
 *	函数说明：	拷贝数据
 *
 *	函数描述：	由于 DSP 特殊的最小的单位为 16bit，所以这里需要做特殊处理
 *
 *	@param		* dest		目标存储位置
 *	@param		* src		源数据数组地址
 *	@param		count		打算存储的空间 Byte 数目
 *
 ************************************************/
void* memcpy_1(void* dest, void* src, UNS16 count)
{
	UNS16* destODValuePtr 	= dest;
	int i;
	const UNS16* s 			= src;

	for(i=0; i < count; i++)
	{
		if(i%2 == 0)
			destODValuePtr[i/2] = s[i] & 0xff;
		else
			destODValuePtr[i/2] |=(s[i] << 8) & 0xff00;
	}
	return dest;
}

/************************************************
 *
 *	函数说明：	拷贝数据
 *
 *	函数描述：	由于 DSP 特殊的最小的单位为 16bit，所以这里需要做特殊处理
 *
 *	@param		* dest		目标存储位置
 *	@param		* src		源数据数组地址
 *	@param		count		打算存储的空间 Byte 数目
 *
 ************************************************/
void* memcpy_2(void* dest, void* src, UNS16 count)
{
	UNS16* tmp = dest;
	int i;
	const UNS16* s = src;
	for(i=0; i < count; i++)
	{
		if(i%2 == 0)
			tmp[i] = s[i/2] & 0xff;
		else
			tmp[i] = (s[i/2] >> 8) & 0xff;
	}
	return dest;
}

