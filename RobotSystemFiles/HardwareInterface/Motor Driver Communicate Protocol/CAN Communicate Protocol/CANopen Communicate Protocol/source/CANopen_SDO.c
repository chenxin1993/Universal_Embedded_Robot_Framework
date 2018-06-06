
#include "../include/CO_DataModel.h"
#include "../include/DataParamPreDefine.h"
#include "../include/FuncDeclaration.h"
#include "../include/MessageModel.h"

/************************************
 *
 *	变量说明：	来自 CANopen_TestMaster.c
 *
 ***********************************/
extern CO_Data TestMaster_Data;

#define SDO_BLOCK_SIZE 	32

/*Internals prototypes*/

/***************************************************************************/
/* SDO (un)packing macros */
/** Returns the command specifier (cs, ccs, scs) from the first byte of the SDO*/
#define getSDOcs(byte) (byte >> 5)
/** Returns the number of bytes without data from the first byte of the SDO. Coded in 2 bits*/
#define getSDOn2(byte) ((byte >> 2) & 3)
/** Returns the number of bytes without data from the first byte of the SDO. Coded in 3 bits*/
#define getSDOn3(byte) ((byte >> 1) & 7)
/** Returns the transfer type from the first byte of the SDO
 * 通过最后一位确定符合 Expedited SDO 数据位数传输格式 */
#define getSDOe(byte) ((byte >> 1) & 1)
/** Returns the size indicator from the first byte of the SDO
 * 通过最后一位确定符合 Normal SDO 数据位数传输格式 */
#define getSDOs(byte) (byte & 1)
/** Returns the indicator of end transmission from the first byte of the SDO*/
#define getSDOc(byte) (byte & 1)
/** Returns the toggle from the first byte of the SDO*/
#define getSDOt(byte) ((byte >> 4) & 1)
/** Returns the index from the bytes 1 and 2 of the SDO*/
#define getSDOindex(byte1, byte2) (((UNS16)byte2 << 8) | ((UNS16)byte1))
/** Returns the subIndex from the byte 3 of the SDO*/
#define getSDOsubIndex(byte3) (byte3)
/** Returns the subcommand in SDO block transfert*/
#define getSDOblockSC(byte) (byte & 3)

#define StopSDO_TIMER(id) \
		d->transfers[id].timer = DelAlarm(d->transfers[id].timer);

//#define StartSDO_TIMER(id) \
//d->transfers[id].timer = SetAlarm(d,id,&SDOTimeoutAlarm,MS_TO_TIMEVAL(SDO_TIMEOUT_MS),0);
//
//#define RestartSDO_TIMER(id) \
//if(d->transfers[id].timer != TIMER_NONE) { StopSDO_TIMER(id) StartSDO_TIMER(id) }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 全局变量定义区域 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
volatile UNS8 sdoReceivedData[4] = {0, 0, 0, 0};
volatile int sdoReceiveDataFlag = 0;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 函数具体实现区域 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*********************************************************
 *
 *	函数说明：	设置 SDO 接收标志位
 *
 *********************************************************/
void setSDOReceiveDataFlag(void) {

	sdoReceiveDataFlag = 1;
}

/*********************************************************
 *
 *	函数说明：	清除 SDO 接收标志位
 *
 *********************************************************/
void clearSDOReceiveDataFlag(void) {

	sdoReceiveDataFlag = 0;
}

/*********************************************************
 *
 *	函数说明：	读取 SDO 接收到的数据
 *
 *********************************************************/
UNS32 getSDOReceiveData(void) {

	UNS32 result = 0;

	result += ((UNS32)(sdoReceivedData[0]) << 0);
	result += ((UNS32)(sdoReceivedData[1]) << 8);
	result += ((UNS32)(sdoReceivedData[2]) << 16);
	result += ((UNS32)(sdoReceivedData[3]) << 24);

	return result;
}

/*********************************************************
 *
 *	函数说明：	等待 SDO 接收标志位清0
 *
 *	说明：		这个等待的过程有时候会很漫长，
 *				所以对于一些不需要确认回复的消息，不调用此函数。
 *
 *********************************************************/
UNS32 waitTillReceiveDataFlagSet() {

	UNS32 result = 0;
	int count = 0;
	while(sdoReceiveDataFlag == 0) {
		count++;
		/*
		 *	说明：	500KHz --> 0.000002s
		 */
		if (count > (10000)) {
			result = 0;
			return result;
		}
	}

	result = getSDOReceiveData();

	return result;
}

/*********************************************************/
//Reset all sdoline
/*********************************************************/
void resetSDO (CO_Data* d) {

	UNS8 j;
	for (j = 0 ; j < SDO_MAX_SIMULTANEOUS_TRANSFERTS ; j++)
		resetSDOline(d, j);
}

/*********************************************************
 *
 *	函数说明：	复位某个 SDOline
 *
 *
 * 	@param 		*d 		Pointer on a CAN object data structure
 * 	@param 		line 	SDO line
 *
 **********************************************************/
void resetSDOline ( CO_Data* d, UNS8 line ) {

	UNS32 i;

	initSDOline(d, line, 0, 0, 0, SDO_RESET);

	for (i = 0 ; i < SDO_MAX_LENGTH_TRANSFERT ; i++)
		d->transfers[line].data[i] 	= 0;

	d->transfers[line].whoami 		= 0;
	d->transfers[line].abortCode 	= 0;
}


/*********************************************
 *
 * @brief 	Initialize some fields of the structure.
 * 			初始化 SDO 线程参数
 *
 * @param 	*d Pointer on a CAN object data structure
 * @param 	line
 * @param 	CliServNbr
 * @param 	index
 * @param 	subIndex
 * @param 	state
 *
 * @return 	0
 *
 *********************************************/
UNS8 initSDOline (
		CO_Data* d,
		UNS8 line,
		UNS8 CliServNbr,
		UNS16 index,
		UNS8 subIndex,
		UNS8 state) {
	//	if (state == SDO_DOWNLOAD_IN_PROGRESS       || state == SDO_UPLOAD_IN_PROGRESS ||
	//        state == SDO_BLOCK_DOWNLOAD_IN_PROGRESS || state == SDO_BLOCK_UPLOAD_IN_PROGRESS){
	//		StartSDO_TIMER(line)
	//	}else{
	//		StopSDO_TIMER(line)
	//	}

	d->transfers[line].CliServNbr 		= CliServNbr;
	d->transfers[line].index 			= index;
	d->transfers[line].subIndex 		= subIndex;
	d->transfers[line].state 			= state;
	d->transfers[line].toggle 			= 0;
	d->transfers[line].count 			= 0;
	d->transfers[line].offset 			= 0;
	d->transfers[line].peerCRCsupport 	= 0;
	d->transfers[line].blksize 			= 0;
	d->transfers[line].ackseq 			= 0;
	d->transfers[line].objsize 			= 0;
	d->transfers[line].lastblockoffset 	= 0;
	d->transfers[line].seqno 			= 0;
	d->transfers[line].endfield 		= 0;
	d->transfers[line].rxstep 			= RXSTEP_INIT;
	d->transfers[line].dataType 		= 0;
	d->transfers[line].Callback 		= NULL;

	return 0;
}

/*********************************************************
 *
 *	函数说明：	SDOline 数据存储到对象字典 OD，实际执行的是 setODentry()
 *
 **********************************************************/
UNS32 SDOlineToObjdict (CO_Data* d, UNS8 line) {

	UNS32 size;
	UNS32 errorCode;
	/* if SDO initiated with e=0 and s=0 count is null, offset carry effective size*/
	if( d->transfers[line].count == 0)
		d->transfers[line].count = d->transfers[line].offset;
	size = d->transfers[line].count;

	errorCode = setODentry(
			d,
			d->transfers[line].index,
			d->transfers[line].subIndex,
			(void *) d->transfers[line].data,
			&size,
			1,
			1);

	if (errorCode != OD_SUCCESSFUL)
		return errorCode;
	return 0;
}

/*********************************************************
 *
 *	函数说明：	将对象字典的内容复制到 d->transfer(line) 的 data
 *
 **********************************************************/
UNS32 objdictToSDOline (CO_Data* d, UNS8 line) {

	UNS32 size = SDO_MAX_LENGTH_TRANSFERT;
	UNS8  dataType;
	UNS32 errorCode;

	errorCode = getODentry(
			d,
			d->transfers[line].index,
			d->transfers[line].subIndex,
			(void *)d->transfers[line].data,
			&size,
			&dataType,
			1,
			1);

	if (errorCode != OD_SUCCESSFUL)
		return errorCode;

	d->transfers[line].count = size;
	d->transfers[line].offset = 0;

	return 0;
}

/*********************************************************
 *
 *	函数说明：	SDOline(d->transfer[line].data) 中的数据复制到 UNS8* data 中
 *
 *	@param		nbBytes	拷贝的字节数目
 *
 **********************************************************/
UNS8 lineToSDO (CO_Data* d, UNS8 line, UNS32 nbBytes, UNS8* data) {

	UNS8 i;
	UNS32 offset;

	if ((d->transfers[line].offset + nbBytes) > SDO_MAX_LENGTH_TRANSFERT) {//SDO Size of data too large. Exceed SDO_MAX_LENGTH_TRANSFERT"
		return 0xFF;
	}

	if ((d->transfers[line].offset + nbBytes) > d->transfers[line].count) {//SDO Size of data too large. Exceed count
		return 0xFF;
	}
	offset = d->transfers[line].offset;
	for (i = 0 ; i < nbBytes ; i++)
		* (data + i) = d->transfers[line].data[offset + i];

	d->transfers[line].offset = d->transfers[line].offset + nbBytes;
	return 0;
}

/*********************************************************
 *
 *	函数说明：	将 Message *m 中的内容保存到 d->transfer 的 data 中
 *
 *	@param		*d			参数结构体指针
 *	@param		line		SDO line
 *	@param		nbBytes		传输过来的的字节数
 *	@param		*data		数据帧的数据段的开始位置的地址指针
 *
 *	@return		0xFF		执行失败
 *				0			执行成功
 *
 **********************************************************/
UNS8 SDOtoLine (CO_Data* d, UNS8 line, UNS32 nbBytes, UNS8* data) {

	UNS8 i;
	UNS32 offset;

	if ((d->transfers[line].offset + nbBytes) > SDO_MAX_LENGTH_TRANSFERT) {
		return 0xFF;
	}

	// 拷贝 data[] 内容到　ｄ->transfers[line].data[] 中
	offset = d->transfers[line].offset;
	for (i = 0 ; i < nbBytes ; i++)
		d->transfers[line].data[offset + i] = * (data + i);

	d->transfers[line].offset = d->transfers[line].offset + nbBytes;
	return 0;
}

/*********************************************************
 *
 * @brief Called when an internal SDO abort occurs.
 * SDO 错误处理函数
 *
 * Release the line * Only if server *
 * If client, the line must be released manually in the core application.
 * The reason of that is to permit the program to read the transfers structure before its reset,
 * because many informations are stored on it : index, subindex, data received or trasmited, ...
 * In all cases, sends a SDO abort.
 * @param	*d 			Pointer on a CAN object data structure
 * @param 	CliServNbr	SDO 通道偏移值(例：0x1200 / 0x1280 的偏移值为 0)
 * @param 	whoami
 * @param 	index		索引
 * @param 	subIndex	子索引
 * @param 	abortCode
 * @return 	0
 *
 *********************************************************/
UNS8 failedSDO (
		CO_Data* d,
		UNS8 CliServNbr,
		UNS8 whoami,
		UNS16 index,
		UNS8 subIndex,
		UNS32 abortCode) {

	UNS8 err;
	UNS8 line;

	// 获取到出现问题的 SDOline, line 编号
	err = getSDOlineOnUse( d, CliServNbr, whoami, &line );
	if ((!err) && (whoami == SDO_SERVER)) {
		resetSDOline( d, line );
	}

	// 发送 SDO abort 信号
	err = sendSDOabort(d, whoami, CliServNbr, index, subIndex, abortCode);
	if (err) {//"Unable to send the SDO abort
		return 0xFF;
	}

	return 0;
}


/************************************************
 *
 * @brief Search for an unused line in the transfers array
 * to store a new SDO.
 * 获取一个为 SDO_RESET 状态的线程, 对 line 的 whoami 进行赋值
 * ie a line which value of the field "state" is "SDO_RESET"
 * An unused line have the field "state" at the value SDO_RESET
 *
 * @param 	*d 			Pointer on a CAN object data structure
 * @param 	whoami 		Create the line for a SDO_SERVER or SDO_CLIENT.
 * @param 	*line 		Pointer on a SDO line
 *
 * @return 0xFF if all the lines are on use. Else, return 0.
 *
 *************************************************/
UNS8 getSDOfreeLine ( CO_Data* d, UNS8 whoami, UNS8 *line ) {

	UNS8 i;

	for (i = 0 ; i < SDO_MAX_SIMULTANEOUS_TRANSFERTS ; i++){
		if ( d->transfers[i].state == SDO_RESET ) {
			*line = i;
			d->transfers[i].whoami = whoami;
			return 0;
		} /* end if */
	} /* end for */
	return 0xFF;
}


/*********************************************************
 *
 *	函数说明：	获取已经在使用的 SDO，获取 initial 状态的 line
 *
 *	@return		0		当前有已经启用的对应的 SDO 通讯线路
 *	@return		0xFF	当前没有已经启用的对应的 SDO 通讯线路
 *
 **********************************************************/
UNS8 getSDOlineOnUse (CO_Data* d, UNS8 CliServNbr, UNS8 whoami, UNS8 *line) {

	UNS8 i;

	/**
	 *	说明：	获取与服务器已经建立的连接
	 */
	for (i = 0 ; i < SDO_MAX_SIMULTANEOUS_TRANSFERTS ; i++){
		if ((d->transfers[i].state != SDO_RESET) &&
				(d->transfers[i].state != SDO_ABORTED_INTERNAL) &&
				(d->transfers[i].CliServNbr == CliServNbr) &&
				(d->transfers[i].whoami == whoami) ) {
			if (line)
				*line = i;
			return 0;
		}
	}
	return 0xFF;
}

/*********************************************************
 *
 *	函数说明：	获取需要从 d->tranfer 复制到 data 中的字节数
 *
 **********************************************************/
UNS8 getSDOlineRestBytes (CO_Data* d, UNS8 line, UNS32 * nbBytes) {
	/* SDO initiated with e=0 and s=0 have count set to null */
	if (d->transfers[line].count == 0) {
		* nbBytes = 0;
	}
	else {
		* nbBytes = d->transfers[line].count - d->transfers[line].offset;
	}

	return 0;
}

/*********************************************************
 *
 *	函数说明：	设置 d->tranfer.data 要复制的字节数
 *
 **********************************************************/
UNS8 setSDOlineRestBytes (CO_Data* d, UNS8 line, UNS32 nbBytes)
{
	if (nbBytes > SDO_MAX_LENGTH_TRANSFERT) {
		return 0xFF;
	}

	d->transfers[line].count = nbBytes;
	return 0;
}

/*************************************
 *
 * @brief Transmit a SDO frame on the bus bus_id
 *
 * @param 	*d 				Pointer on a CAN object data structure
 * @param 	whoami 			Takes 2 values : SDO_CLIENT or SDO_SERVER
 * @param 	CliServNbr 		Client or Server object involved(第几个SDO通讯端口，通讯端口偏移量)
 * @param 	data Array 		of the 8 bytes to transmit
 *
 * @return canSend(bus_id,&m) or 0xFF if error.
 *
 *************************************/
UNS8 sendSDO (CO_Data* d, UNS8 whoami, UNS8 CliServNbr, UNS8 *pData)
{
	UNS16 offset;
	UNS8 i;
	Message m;

	if(!((d->nodeState == Operational) || (d->nodeState == Pre_operational ))){
		return 0xFF;
	}

	/* SDO_SERVER */
	if(whoami == SDO_SERVER){
		offset = d->firstIndex->SDO_SVR;
		if ((offset == 0) || ((offset+CliServNbr) > d->lastIndex->SDO_SVR)) {
			return 0xFF;
		}
		m.cob_id = *((UNS32*) d->objdict[offset+CliServNbr].pSubindex[2].pObject);
	}
	/* SDO_CLIENT */
	else {
		offset = d->firstIndex->SDO_CLT;
		if ((offset == 0) || ((offset+CliServNbr) > d->lastIndex->SDO_CLT)) {
			return 0xFF;
		}
		m.cob_id = *((UNS32*) d->objdict[offset+CliServNbr].pSubindex[1].pObject);
	}

	m.rtr = NOT_A_REQUEST;
	m.len = 8;

	for (i = 0 ; i < 8 ; i++) {
		m.data[i] =  pData[i];
	}

	return canSend(&m);
}

/*************************************
 *
 * @brief Transmit a SDO error to the client.
 * The reasons may be :
 * 		Read/Write to a undefined object
 * 		Read/Write to a undefined subindex
 * 		Read/write a not valid length object
 * 		Write a read only object
 *
 * @param 	*d 				Pointer on a CAN object data structure
 * @param 	whoami 			takes 2 values : SDO_CLIENT or SDO_SERVER
 * @param 	CliServNbr
 * @param 	index
 * @param 	subIndex
 * @param 	abortCode
 *
 * @return 	0
 *
 *************************************/
UNS8 sendSDOabort (
		CO_Data* d,
		UNS8 whoami,
		UNS8 CliServNbr,
		UNS16 index,
		UNS8 subIndex,
		UNS32 abortCode)
{
	UNS8 data[8];
	UNS8 ret;

	data[0] = 0x80;
	/* Index */
	data[1] = index & 0xFF; /* LSB */
	data[2] = (index >> 8) & 0xFF; /* MSB */

	/* Subindex */
	data[3] = subIndex;

	/* Data */
	data[4] = (UNS8)(abortCode & 0xFF);
	data[5] = (UNS8)((abortCode >> 8) & 0xFF);
	data[6] = (UNS8)((abortCode >> 16) & 0xFF);
	data[7] = (UNS8)((abortCode >> 24) & 0xFF);

	ret = sendSDO(d, whoami, CliServNbr, data);

	return ret;
}

/**
 *	函数说明：	执行 SDO 的 request 程序完成后，
 *				收到的 response 的回调程序
 */
void processSendSDOCallBack(CO_Data* d, UNS8 nodeId, UNS8 line) {

	// 设置接收标志位
	setSDOReceiveDataFlag();
	int i;

	switch(d->transfers[line].state) {
	case SDO_RESET:
		break;
	case SDO_ABORTED_RCV:
		resetSDOline(d, line);
		break;
	case SDO_ABORTED_INTERNAL:
		resetSDOline(d, line);
		break;
	case SDO_DOWNLOAD_IN_PROGRESS:
		resetSDOline(d, line);
		break;
	case SDO_FINISHED:
	case SDO_UPLOAD_IN_PROGRESS:
		// 接收数据
		for (i = 0; i < 4; i++) {
			if (i < d->transfers[line].count) {
				sdoReceivedData[i] = d->transfers[line].data[i];
			}
			else {
				sdoReceivedData[i] = 0;
			}
		}
		resetSDOline(d, line);
		break;
	default:
		break;
	}
}

/*********************************************************
 *
 *	函数说明：	处理 SDO 消息
 *
 *	@var		*d		CANopen 数据结构指针
 *	@var		*m		Message 信息体结构指针
 *
 *	@return		0xFF	解析出来不是 SDO 消息
 *				0xFF	解析出来不满足 SDO 消息内容长度
 *
 **********************************************************/
UNS32 processSendSDO(CO_Data* d, Message *m) {

	int i = 0;
	UNS8 err;
	UNS8 line;
	UNS8 whoami = SDO_UNKNOWN;
	UNS8 CliServNbr;
	UNS8 cs;
	UNS8 state;
	UNS16 index;
	UNS8  subIndex;
	UNS32 *pCobId = NULL;
	UNS16 offset;
	UNS16 lastIndex;
	UNS8  j;

	UNS32 result = 0;

	/* 1. judge whether i am a client.
	 * only the client has the power
	 * to send request first. */
	/* Am-I client ? */
	if (whoami == SDO_UNKNOWN) {
		offset 		= d->firstIndex->SDO_CLT;
		lastIndex 	= d->lastIndex->SDO_CLT;
		j = 0;
		if(offset) {
			while (offset <= lastIndex) {
				if (d->objdict[offset].bSubCount <= 1) {
					return 0xFF;
				}

				/* Looking for the cobid received. */
				pCobId = (UNS32*) d->objdict[offset].pSubindex[1].pObject;
				if (*pCobId == UNS16_LE(m->cob_id) ) {
					whoami = SDO_CLIENT;
					CliServNbr = j;
					break;
				}
				j++;
				offset++;
			} /* end while */
		}
	}

	/* Who Am I? */
	if(whoami == SDO_UNKNOWN){
		return 0xFF;
	}

	/* 2. get a free line */
	err = getSDOfreeLine(d, whoami, &line);
	if (err) {
		return 0xFF;
	}

	/* 3. init a sdo line */
	cs 			= getSDOcs(m->data[0]);
	switch(cs) {
	case 1:
		state = SDO_DOWNLOAD_IN_PROGRESS;
		break;
	case 2:
		state = SDO_UPLOAD_IN_PROGRESS;
		break;
	default:
		return 0xFF;
	}
	index 		= getSDOindex(m->data[1], m->data[2]);
	subIndex 	= getSDOsubIndex(m->data[3]);
	err = initSDOline(d, line, CliServNbr, index, subIndex, state);
	if (err) {
		return 0xFF;
	}

	for (i = 0; i < m->len; i++) {
		d->transfers[line].data[i] = m->data[i];
	}

	/* if it is a block data segment,
	 * you need to set "count" and "offset",
	 * otherwise, you could just set
	 * "count = 0", "offset = 0" */
	d->transfers[line].count = 0;
	d->transfers[line].offset = 0;

	/* set callback func to get data */
	d->transfers[line].Callback = processSendSDOCallBack;

	/* 4. clear receive flag */
	clearSDOReceiveDataFlag();

	/* 5. send SDO request */
	sendSDO(d, whoami, CliServNbr, d->transfers[line].data);

	/* 6. wait for response */
	//	result = waitTillReceiveDataFlagSet();
	//	clearSDOReceiveDataFlag();

	/* 7. reset SDO line */
	//	resetSDOline(d, line);

	return result;
}

/*********************************************************
 *
 *	函数说明：	处理接收到的 SDO 消息
 *
 *	@return		0xFF	解析出来不是 SDO 消息
 *				0xFF	解析出来不满足 SDO 消息内容长度
 *
 **********************************************************/
UNS8 proceedReceiveSDO (CO_Data* d, Message *m)
{
	UNS8 err;
	UNS8 cs;
	UNS8 line;
	UNS32 nbBytes; 				/* received or to be transmited. */
	UNS8 nodeId = 0;  			/* The node Id of the server if client otherwise unused */
	UNS8 CliServNbr;			/* SDO 通道号，相对 0x1200 的偏移量 */
	UNS8 whoami = SDO_UNKNOWN;  /* SDO_SERVER or SDO_CLIENT.*/
	UNS16 index;
	UNS8 subIndex;
	UNS32 abortCode;
	UNS32 i;
	UNS8  j;
	UNS32 *pCobId = NULL;
	UNS16 offset;
	UNS16 lastIndex;

	whoami = SDO_UNKNOWN;

	/* Am-I a server ? */
	//	offset 		= d->firstIndex->SDO_SVR;
	//	lastIndex 	= d->lastIndex->SDO_SVR;
	//	j = 0;
	//	if(offset)
	//	{
	//		while (offset <= lastIndex) {
	//			// 作为 SDO 通信，至少有 0x600h, 0x580h 等
	//			if (d->objdict[offset].bSubCount <= 1) {
	//				return 0xFF;
	//			}
	//
	//			//Looking for the cobid received
	//			pCobId = (UNS32*) d->objdict[offset].pSubindex[1].pObject;
	//			if ( *pCobId == UNS16_LE(m->cob_id) ) {
	//				whoami = SDO_SERVER;
	//				CliServNbr = j;
	//				break;
	//			}
	//			j++;
	//			offset++;
	//		} /* end while */
	//	}

	/* Am-I client ? */
	if (whoami == SDO_UNKNOWN) {
		offset 		= d->firstIndex->SDO_CLT;
		lastIndex 	= d->lastIndex->SDO_CLT;
		j = 0;
		if(offset) {
			while (offset <= lastIndex) {
				if (d->objdict[offset].bSubCount <= 2) {
					return 0xFF;
				}

				/* Looking for the cobid received. */
				pCobId = (UNS32*) d->objdict[offset].pSubindex[2].pObject;
				if (*pCobId == UNS16_LE(m->cob_id) ) {
					whoami = SDO_CLIENT;
					CliServNbr = j;
					break;
				}
				j++;
				offset++;
			} /* end while */
		}
	}

	/* Who Am I? */
	if(whoami == SDO_UNKNOWN){
		return 0xFF;
	}

	/* Error Size Of SDO Message 如果 SDO 帧的数据段长度不为8，报错
	 * 说明：	SDO 消息内容里面没有的未用的补零 */
	if((*m).len != 8){
		failedSDO(d, CliServNbr, whoami, 0, 0, SDOABT_GENERAL_ERROR);
		return 0xFF;
	}

	/* Look for an SDO transfert already initiated. */
	err = getSDOlineOnUse( d, CliServNbr, whoami, &line );

	/* Let's find cs value, first it is set as "not valid" */
	cs = 0xFF; 

	/* Special cases for block transfert : in frames with segment data cs is not specified */
	if (!err) {
		if ((whoami == SDO_SERVER) && (d->transfers[line].state == SDO_BLOCK_DOWNLOAD_IN_PROGRESS) ||
				(whoami == SDO_CLIENT) && (d->transfers[line].state == SDO_BLOCK_UPLOAD_IN_PROGRESS)) {
			if(m->data[0] == 0x80)	/* If first byte is 0x80 it is an abort frame (seqno = 0 not allowed) */
				cs = 4;
			else
				cs = 6;
		}
	}

	/* Other cases: cs is specified */
	if (cs == 0xFF)
		cs = getSDOcs(m->data[0]);

	/*************************************************
	 *
	 *	说明：	这里需要查看 SDO 命令字的相关含义(Command Specifier, cs),
	 *			可以参考资料《德国工程师的 CANopen 手册》
	 *
	 *************************************************/
	/* Testing the command specifier
	 * Allowed: cs = 0,1,2,3,4,5,6.
	 * cs=other: Not allowed->abort*/
	switch (cs) {
	case 0:
		if (whoami == SDO_SERVER) {// I am SERVER : Receiving a download segment data
			/* I am SERVER */
		}
		else {
			/* I am CLIENT */
			//RestartSDO_TIMER(line);
			index = d->transfers[line].index;
			subIndex = d->transfers[line].subIndex;
			/* nb of data to be uploaded */
			nbBytes = 7 - getSDOn3(m->data[0]);
			/* Storing the data in the line structure. */
			err = SDOtoLine(d, line, nbBytes, (*m).data + 1);
			if (err) {
				failedSDO(d, CliServNbr, whoami, index, subIndex, SDOABT_GENERAL_ERROR);
				return 0xFF;
			}
			/* If it was the last segment,*/
			if (getSDOc(m->data[0])) {
				/* Put in state finished */
				/* The code is safe for the case e=s=0 in initiate frame. */
				//StopSDO_TIMER(line);
				d->transfers[line].state = SDO_FINISHED;
				if(d->transfers[line].Callback) {
					(*d->transfers[line].Callback)(d, nodeId, line);
				}
			}
			else { /* more segments to receive */
			}
		}	/* End if CLIENT */
		break;
	case 1:
		/**
		 *	case1 发生情况说明：
		 *		1. 服务器收到客户端发来的快速写请求：2Fh, 2Bh, 27h, 23h
		 *		2. 客户端收到服务器发来的块写完成回复，补充奇数次：20h; 补充偶数次：30h
		 */
		/* I am SERVER */
		if (whoami == SDO_SERVER) {
		} /* end if I am SERVER */
		else {
			/* I am CLIENT */
			/* 1. It is a response for a previous download segment. We should find a line opened for this. */
//			if (!err)
//				err = d->transfers[line].state != SDO_DOWNLOAD_IN_PROGRESS;
//			if (err) {
//				failedSDO(d, CliServNbr, whoami, 0, 0, SDOABT_LOCAL_CTRL_ERROR);
//				return 0xFF;
//			}

			/* 2. get index and subindex */
			index = d->transfers[line].index;
			subIndex = d->transfers[line].subIndex;

			/* 3. test of the toggle; */
//			if (d->transfers[line].toggle != getSDOt(m->data[0])) {
//				failedSDO(d, CliServNbr, whoami, index, subIndex, SDOABT_TOGGLE_NOT_ALTERNED);
//				return 0xFF;
//			}

			/* 4. End transmission or downloading next segment. We need to know if it will be the last one. */
			getSDOlineRestBytes(d, line, &nbBytes);
			if (nbBytes == 0) {
				//StopSDO_TIMER(line);
				d->transfers[line].state = SDO_FINISHED;
				if(d->transfers[line].Callback) {
					(*d->transfers[line].Callback)(d, nodeId, line);
				}
				return 0x00;
			}

		} /* end if I am a CLIENT */
		break;
	case 2:
		/**
		 *	case2 情况描述：
		 *		1. 服务器接收到来自客户端的快速读请求：4Fh, 4Bh, 47h, 43h
		 *		2. 客户端接收到来自服务器的快读读请求响应：4Fh, 4Bh, 47h, 43h
		 */
		/*****************************
		 *
		 *	说明：	这一部分的操作顺序可以作为发送 SDO 指令的参考模板
		 *
		 *****************************/
		/* I am SERVER */
		if (whoami == SDO_SERVER) {
		} /* end if I am SERVER*/
		else {
			/* I am CLIENT */
			/* It is the response for the previous initiate upload request.*/
			/* We should find a line opened for this. */
			/*
			 * 1. 查询是否有对应 SDO line
			 *
			 * 说明：
			 * case 2 对应的是服务器给出的 response 信息，
			 * 所以按理说应该会先开启一个 SDO 服务线程与接收到的 SDO 对应,
			 * 这里就是在检查是否有这么一个对应的 SDO 线程，
			 * 这个功能也可以人为关闭，此处为方便调试，我们关闭它 */
//			if (!err)
//				err = d->transfers[line].state != SDO_UPLOAD_IN_PROGRESS;
//			if (err) {
//				failedSDO(d, CliServNbr, whoami, 0, 0, SDOABT_LOCAL_CTRL_ERROR);
//				return 0xFF;
//			}

			// 1. 获取 index, subindex
			index 		= d->transfers[line].index;
			subIndex 	= d->transfers[line].subIndex;

			/* If SDO expedited */
			if (getSDOe(m->data[0])) {
				/* nb of data to be uploaded */
				nbBytes = 4 - getSDOn2(m->data[0]);

				/* 2. Storing the data in the line structure. */
				err = SDOtoLine(d, line, nbBytes, (*m).data + 4);
				if (err) {
					failedSDO(d, CliServNbr, whoami, index, subIndex, SDOABT_GENERAL_ERROR);
					return 0xFF;
				}
				/* SDO expedited -> transfer finished. data are available via  getReadResultNetworkDict(). */
				//StopSDO_TIMER(line);
				d->transfers[line].count = nbBytes;
				d->transfers[line].state = SDO_FINISHED;

				/* 3. 调用 Callback 方法，来读取 response 回来的数据，
				 * 		进行后续的数据处理 */
				if(d->transfers[line].Callback) {
					(*d->transfers[line].Callback)(d, nodeId, line);
				}

				return 0;
			}
			/* So, if it is not an expedited transfer */
			else {
			}
		} /* End if CLIENT */
		break;
	case 3:
		/**
		 *	case3 情况描述：
		 *		1.
		 *		2. 客户端收到来自服务器的快速写应答(写成功)：60h, 63h, 67h, 6Bh, 6Fh
		 */
		/* I am SERVER */
		if (whoami == SDO_SERVER) {
		} /* end if SERVER*/
		else {
			/* I am CLIENT */
			/* It is the response for the previous initiate download request. */
			/* We should find a line opened for this. */
			/* 1. 查询是否有对应 SDO line */
//			if (!err) {
//				err = d->transfers[line].state != SDO_DOWNLOAD_IN_PROGRESS;
//			}
//			if (err) {
//				failedSDO(d, CliServNbr, whoami, 0, 0, SDOABT_LOCAL_CTRL_ERROR);
//				return 0xFF;
//			}

			/* 2. 获取 index, subindex */
			index 		= d->transfers[line].index;
			subIndex 	= d->transfers[line].subIndex;

			/* 3. End transmission or requesting  next segment. 获取 SDO 剩余数据字节数 */
			getSDOlineRestBytes(d, line, &nbBytes);

			/* 4. 如果是 Expedited 模式，或是最后一帧数据 */
			if (nbBytes == 0) {
				d->transfers[line].state = SDO_FINISHED;
				if(d->transfers[line].Callback) {
					(*d->transfers[line].Callback)(d, nodeId, line);
				}

				return 0x00;
			}
		} /* end if I am a CLIENT */
		break;
	case 4:
		/**
		 *	case4 情况描述：
		 *		1. 服务器或客户端处理信息发生错误，中断通信：80h
		 */
		abortCode =
				(UNS32)m->data[4] |
				((UNS32)m->data[5] << 8) |
				((UNS32)m->data[6] << 16) |
				((UNS32)m->data[7] << 24);
		/* Received SDO abort. */
		if (whoami == SDO_SERVER) {
		}
		else { /* If I am CLIENT */
			if (!err) {
				/* The line *must* be released by the core program. */
				d->transfers[line].state = SDO_ABORTED_RCV;
				d->transfers[line].abortCode = abortCode;
				if(d->transfers[line].Callback) {
					(*d->transfers[line].Callback)(d, nodeId, line);
				}
			}
		}
		break;
	case 5:
		resetSDOline(d, line);
		break;
	case 6:
		resetSDOline(d, line);
		break;
	default:
		return 0xFF;/* Error : Unknown cs */
	} /* End switch */
	return 0;
}
