
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/CO_DataModel.h>
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/DataParamPreDefine.h>
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/FuncDeclaration.h>
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/MessageModel.h>

/************************************
 *
 *	变量说明：	来自 CANopen_FuncCode.c
 *
 ***********************************/
extern struct FUNCCODE Func;

/******************The timer table********************/

unsigned int  DriverState			= 0;
unsigned int  ControlwordState		= 0;
unsigned int  ControlwordStatebak	= 0xff;
unsigned int  HomingOperStartbak	= 0;

#define min_val(a,b) ((a<b)?a:b)

/*****************************************
 *
 *	函数说明：	CAN 发送分支函数
 *
 *	函数描述：	根据要发送的不同消息，进行分别处理
 *
 *	@param		*d				CO_Data 结构体的指针
 *	@param		*m				Message	消息
 *
 *****************************************/
UNS32 canSendDispatch(CO_Data* d, Message *m) {

	/*************************************
	 *
	 *	说明：	COB-ID 的 [10:7]bits 是功能码，所以这里进行解析
	 *
	 *************************************/
	UNS16 cob_id 	= UNS16_LE(m->cob_id);
	UNS16 cob_idbak = (cob_id >> 7);

	switch(cob_idbak)
	{
	case SYNC:		/* can be a SYNC or a EMCY message */
		break;
	case PDO1tx:
	case PDO1rx:
	case PDO2tx:
	case PDO2rx:
	case PDO3tx:
	case PDO3rx:
	case PDO4tx:
	case PDO4rx:
		break;
	case SDOtx:
	case SDOrx:
		return processSendSDO(d, m);
	case NODE_GUARD:
		break;
	case NMT:
		return processSendNMT(d, m);
	}

	return 0;
}

/*****************************************
 *
 *	函数说明：	CAN 接收分支函数
 *
 *	函数描述：	根据收到的不同的消息，进行不同的解析以及处理。
 *
 *	@param		*d		CO_Data 结构体的指针
 *	@param		*m		Message	消息
 *
 *****************************************/
void canReceiveDispatch(CO_Data* d, Message *m)
{
	/*************************************
	 *
	 *	说明：	COB-ID 的 [10:7]bits 是功能码，所以这里进行解析
	 *
	 *************************************/
	UNS16 cob_id 	= UNS16_LE(m->cob_id);
	UNS16 cob_idbak = (cob_id >> 7);

	//----------- 解析收到的信息内容 --------------
	switch(cob_idbak)
	{
	case SYNC:		/* can be a SYNC or a EMCY message */
#if USE_SYNC
		if(cob_id == 0x080)	/* SYNC */
		{
			if(d->CurrentCommunicationState.csSYNC)
				proceedReceiveSYNC(d);
		}
		else 		/* EMCY */
		{
			if(d->CurrentCommunicationState.csEmergency)
				proceedReceiveEMCY(d,m);
		}
#endif
		break;
	case PDO1tx:
	case PDO1rx:
	case PDO2tx:
	case PDO2rx:
	case PDO3tx:
	case PDO3rx:
	case PDO4tx:
	case PDO4rx:
		break;
	case SDOtx:
	case SDOrx:
		proceedReceiveSDO(d,m);
		break;
	case NODE_GUARD:
		break;
	case NMT:
		break;
	}
}

/*****************************************
 *
 *	函数说明：	读取 CAN 主机状态配置函数
 *
 *****************************************/
e_nodeState getState (CO_Data* d) {

	return d->nodeState;
}
/*****************************************
 *
 *	函数说明：	CAN 主机状态配置函数
 *
 *****************************************/
UNS8 setState(CO_Data* d, e_nodeState newState) {

	if(newState != d->nodeState){
		switch( newState ){
		case Initialisation:
			d->nodeState = Initialisation;
		case Pre_operational:
			d->nodeState = Pre_operational;
			break;

		case Operational:
			if(d->nodeState == Initialisation) {
				return 0xFF;
			}
			else {
				d->nodeState = Operational;
			}
			break;

		case Stopped:
			if(d->nodeState == Initialisation) {
				return 0xFF;
			}
			else {
				d->nodeState = Stopped;
			}
			break;
		default:
			return 0xFF;

		}/* end switch case */
	}
	return d->nodeState;
}


