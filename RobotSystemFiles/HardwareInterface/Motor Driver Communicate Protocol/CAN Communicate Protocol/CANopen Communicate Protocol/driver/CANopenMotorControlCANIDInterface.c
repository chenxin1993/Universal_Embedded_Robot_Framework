/*
 * CANInterface.c
 *
 *  Created on: 2016-12-18
 *      Author: e701
 */

#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/driver/CANopenMotorControlCANIDInterface.h>

/************************************
 *
 *	变量说明：	来自 CANopen_TestMaster.c
 *
 ***********************************/
extern CO_Data TestMaster_Data;


/*********************************
 *
 *	函数说明：	初始化 CANInterface 模型
 *
 *********************************/
void CANInterface_init(
		struct CANInterface * canInterface,
		int canID,
		int enable) {

	canInterface->canID = canID;
	canInterface->enable = enable;
}

/*********************************
 *
 *	函数说明：	拷贝 CANInterface 模型
 *
 *********************************/
void CANInterface_copy(
		struct CANInterface * canInterfaceTo,
		struct CANInterface * canInterfaceFrom) {

	canInterfaceTo->canID 	= canInterfaceFrom->canID;
	canInterfaceTo->enable 	= canInterfaceFrom->enable;
}

/*********************************
 *
 *	函数说明：	CANInterface 模型 功能刷新
 *
 *********************************/
void CANInterface_flush(
		struct CANInterface * canInterface) {

	if (canInterface->enable) {
		CANInterface_enableCANNode(canInterface);
	}
	else {
		CANInterface_disableCANNode(canInterface);
	}
}

/*********************************
 *
 *	函数说明：	启动远程 CAN 节点
 *
 *********************************/
void CANInterface_enableCANNode(
		struct CANInterface * canInterface) {

	Message message;

	message.cob_id = 0x0;
	message.rtr = 0;
	message.len = 2;
	message.data[0] = 0x01;
	message.data[1] = canInterface->canID;

	canSendDispatch(&TestMaster_Data, &message);

	canInterface->enable = TRUE;
}

/*********************************
 *
 *	函数说明：	关闭远程 CAN 节点
 *
 *********************************/
void CANInterface_disableCANNode(
		struct CANInterface * canInterface) {

	Message message;

	message.cob_id = 0x0;
	message.rtr = 0;
	message.len = 2;
	message.data[0] = 0x02;
	message.data[1] = canInterface->canID;

	canSendDispatch(&TestMaster_Data, &message);

	canInterface->enable = FALSE;
}

/*********************************
 *
 *	函数说明：	配置远程 CAN 节点 pre-operational
 *
 *********************************/
void CANInterface_setCANNodePreOperational(
		struct CANInterface * canInterface) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	Message message;

	message.cob_id = 0x0;
	message.rtr = 0;
	message.len = 2;
	message.data[0] = 0x80;
	message.data[1] = canInterface->canID;

	canSendDispatch(&TestMaster_Data, &message);
}

/*********************************
 *
 *	函数说明：	复位远程 CAN 节点
 *
 *********************************/
void CANInterface_resetCANNode(
		struct CANInterface * canInterface) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	Message message;

	message.cob_id = 0x0;
	message.rtr = 0;
	message.len = 2;
	message.data[0] = 0x81;
	message.data[1] = canInterface->canID;

	canSendDispatch(&TestMaster_Data, &message);
}

/*********************************
 *
 *	函数说明：	复位远程 CAN 节点通信
 *
 *********************************/
static void CANInterface_resetCANNodeCommunication(
		struct CANInterface * canInterface) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	Message message;

	message.cob_id = 0x0;
	message.rtr = 0;
	message.len = 2;
	message.data[0] = 0x82;
	message.data[1] = canInterface->canID;

	canSendDispatch(&TestMaster_Data, &message);
}

/*********************************
 *
 *	函数说明：	对对象字典的读操作
 *
 *********************************/
static unsigned long CANInterface_readObjectDictionary(
		struct CANInterface * canInterface,
		unsigned long index,
		unsigned char subIndex,
		int readByteCount,
		unsigned long * response) {

	if (canInterface->enable) {
	}
	else {
		return 0;
	}

	unsigned long result;

	// 1. 发送请求消息
	Message tempMessage;

	tempMessage.cob_id = 0x600 + canInterface->canID;
	tempMessage.rtr = 0;
	tempMessage.len = 8;
	switch (readByteCount) {
	case 1:tempMessage.data[0] = SDO_EXPEDITED_UPLOAD_ONE_BYTE_REQUEST;break;
	case 2:tempMessage.data[0] = SDO_EXPEDITED_UPLOAD_TWO_BYTE_REQUEST;break;
	case 3:tempMessage.data[0] = SDO_EXPEDITED_UPLOAD_THREE_BYTE_REQUEST;break;
	case 4:tempMessage.data[0] = SDO_EXPEDITED_UPLOAD_FOUR_BYTE_REQUEST;break;
	default:break;
	}
	tempMessage.data[1] = index & 0xFF;
	tempMessage.data[2] = (index >> 8) & 0xFF;
	tempMessage.data[3] = subIndex & 0xFF;
	tempMessage.data[4] = 0x0;
	tempMessage.data[5] = 0x0;
	tempMessage.data[6] = 0x0;
	tempMessage.data[7] = 0x0;

	canSendDispatch(&TestMaster_Data, &tempMessage);

	// 2. 等待数据接收(轮询模式)
	/**
	 *	说明，成功接收判断流程：
	 *			1. 确认收到数据
	 *			2. 比较数据帧的 index, subindex 是否符合
	 */
	result = canReceiveSDO(canInterface->canID, &tempMessage);
	while((tempMessage.data[1] != (index & 0xFF))
			|| (tempMessage.data[2] != ((index >> 8) & 0xFF))
			|| (tempMessage.data[3] != (subIndex & 0xFF))) {
		result = canReceiveSDO(canInterface->canID, &tempMessage);
		if (result == TRUE) {
		}
		else {
			break;
		}
	}

	if (result) {
		canReceiveDispatch(&TestMaster_Data, &tempMessage);
		*response = getSDOReceiveData();
		result = TRUE;
	}
	else {
		resetSDO(&TestMaster_Data);
		result = FALSE;
	}

	return result;
}

/*********************************
 *
 *	函数说明：	对对象字典的写操作
 *
 *	@param		writeByteCount 	写入字节数(1 ~ 4)
 *
 *	@return		TRUE	接收数据成功
 *				FALSE	接收数据失败
 *
 *********************************/
static unsigned long CANInterface_writeObjectDictionary(
		struct CANInterface * canInterface,
		unsigned long index,
		unsigned char subIndex,
		unsigned char writeByteCount,
		unsigned char* bytes,
		unsigned long * response) {

	if (canInterface->enable) {
	}
	else {
		return 0;
	}

	int i;
	unsigned long result;

	// 1. 发送请求消息
	Message tempMessage;

	tempMessage.cob_id = 0x600 + canInterface->canID;
	tempMessage.rtr = 0;
	tempMessage.len = 8;
	switch (writeByteCount) {
	case 1:tempMessage.data[0] = SDO_EXPEDITED_DOWNLOAD_ONE_BYTE_REQUEST;break;
	case 2:tempMessage.data[0] = SDO_EXPEDITED_DOWNLOAD_TWO_BYTE_REQUEST;break;
	case 3:tempMessage.data[0] = SDO_EXPEDITED_DOWNLOAD_THREE_BYTE_REQUEST;break;
	case 4:tempMessage.data[0] = SDO_EXPEDITED_DOWNLOAD_FOUR_BYTE_REQUEST;break;
	default:break;
	}
	tempMessage.data[1] = index & 0xFF;
	tempMessage.data[2] = (index >> 8) & 0xFF;
	tempMessage.data[3] = subIndex & 0xFF;
	for (i = 0; i < 4; i++) {
		if (i < writeByteCount) {
			tempMessage.data[4 + i] = *(bytes + i);
		}
		else {
			tempMessage.data[4 + i] = 0;
		}
	}

	canSendDispatch(&TestMaster_Data, &tempMessage);

	// 2. 等待数据接收(轮询模式)
	if (canReceiveSDO(canInterface->canID, &tempMessage)) {
		canReceiveDispatch(&TestMaster_Data, &tempMessage);
		*response = getSDOReceiveData();
		result = TRUE;
	}
	else {
		resetSDO(&TestMaster_Data);
		result = FALSE;
	}

	return result;
}

/*********************************
 *
 *	函数说明：	对对象字典的写操作
 *
 *	@param		writeByteCount 	写入字节数(1 ~ 4)
 *
 *	@return		0	发送成功
 *
 *********************************/
static unsigned long CANInterface_writeObjectDictionaryNotCareResponse(
		struct CANInterface * canInterface,
		unsigned long index,
		unsigned char subIndex,
		unsigned char writeByteCount,
		unsigned char* bytes) {

	if (canInterface->enable) {
	}
	else {
		return 0;
	}

	int i;

	// 1. 发送请求消息
	Message tempMessage;

	tempMessage.cob_id = 0x600 + canInterface->canID;
	tempMessage.rtr = 0;
	tempMessage.len = 8;
	switch (writeByteCount) {
	case 1:tempMessage.data[0] = SDO_EXPEDITED_DOWNLOAD_ONE_BYTE_REQUEST;break;
	case 2:tempMessage.data[0] = SDO_EXPEDITED_DOWNLOAD_TWO_BYTE_REQUEST;break;
	case 3:tempMessage.data[0] = SDO_EXPEDITED_DOWNLOAD_THREE_BYTE_REQUEST;break;
	case 4:tempMessage.data[0] = SDO_EXPEDITED_DOWNLOAD_FOUR_BYTE_REQUEST;break;
	default:break;
	}
	tempMessage.data[1] = index & 0xFF;
	tempMessage.data[2] = (index >> 8) & 0xFF;
	tempMessage.data[3] = subIndex & 0xFF;
	for (i = 0; i < 4; i++) {
		if (i < writeByteCount) {
			tempMessage.data[4 + i] = *(bytes + i);
		}
		else {
			tempMessage.data[4 + i] = 0;
		}
	}

	canSendDispatch(&TestMaster_Data, &tempMessage);

	// 2. 等待数据接收(轮询模式)
	//	canReceiveSDO(canInterface->canID, &tempMessage);
	//	canReceiveDispatch(&TestMaster_Data, &tempMessage);
	//	result = getSDOReceiveData();
	resetSDO(&TestMaster_Data);

	return 0;
}

/*********************************
 *
 *	函数说明：	启动控制器，电机使能
 *
 *********************************/
void CANInterface_enableDriver(struct CANInterface * canInterface) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	unsigned char bytes[4] = {0x0F, 0x00, 0x00, 0x00};

	CANInterface_writeObjectDictionaryNotCareResponse(
			canInterface,
			MOTOR_DRIVER_CONTROL_WORD_INDEX,
			MOTOR_DRIVER_CONTROL_WORD_SUBINDEX,
			MOTOR_DRIVER_CONTROL_WORD_WRITE_LENGTH,
			bytes);
}

/*********************************
 *
 *	函数说明：	关闭控制器，电机失能
 *
 *********************************/
void CANInterface_disableDriver(struct CANInterface * canInterface) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	unsigned char bytes[4] = {0x00, 0x00, 0x00, 0x00};

	CANInterface_writeObjectDictionaryNotCareResponse(
			canInterface,
			MOTOR_DRIVER_CONTROL_WORD_INDEX,
			MOTOR_DRIVER_CONTROL_WORD_SUBINDEX,
			MOTOR_DRIVER_CONTROL_WORD_WRITE_LENGTH,
			bytes);
}

/*********************************
 *
 *	函数说明：	设置驱动器为位置控制模式
 *
 *********************************/
void CANInterface_setPositionControlMode(struct CANInterface * canInterface) {

}

/*********************************
 *
 *	函数说明：	设置驱动器为速度控制模式
 *
 *********************************/
void CANInterface_setVelocityControlMode(struct CANInterface * canInterface) {

	unsigned char bytes[4] = {0x03, 0x00, 0x00, 0x00};

	CANInterface_writeObjectDictionaryNotCareResponse(
			canInterface,
			MOTOR_DRIVER_MODE_OF_OPERATION_INDEX,
			MOTOR_DRIVER_MODE_OF_OPERATION_SUBINDEX,
			MOTOR_DRIVER_MODE_OF_OPERATION_WRITE_LENGTH,
			bytes);
}

/*********************************
 *
 *	函数说明：	设置驱动器为速度控制模式
 *
 *********************************/
void CANInterface_setTorqueControlMode(struct CANInterface * canInterface) {

}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 电机参数读取 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*********************************
 *
 *	函数说明：	读取当前电流值
 *
 *********************************/
unsigned long CANInterface_getActualCurrent(
		struct CANInterface * canInterface) {

	if (canInterface->enable) {
	}
	else {
		return 0;
	}

	unsigned long response;

	CANInterface_readObjectDictionary(
			canInterface,
			MOTOR_DRIVER_ACTUAL_CURRENT_INDEX,
			MOTOR_DRIVER_ACTUAL_CURRENT_SUBINDEX,
			MOTOR_DRIVER_ACTUAL_CURRENT_READ_LENGTH,
			&response);

	return response;
}

/*********************************
 *
 *	函数说明：	读取当前速度值 (0.1 enc count / sec)
 *
 *********************************/
unsigned long CANInterface_getActualVelocity(
		struct CANInterface * canInterface) {

	if (canInterface->enable) {
	}
	else {
		return 0;
	}

	unsigned long response;

	CANInterface_readObjectDictionary(
			canInterface,
			MOTOR_DRIVER_ACTUAL_VELOCITY_INDEX,
			MOTOR_DRIVER_ACTUAL_VELOCITY_SUBINDEX,
			MOTOR_DRIVER_ACTUAL_VELOCITY_READ_LENGTH,
			&response);

	return response;
}

/*********************************
 *
 *	函数说明：	读取当前位置计数值
 *
 *********************************/
unsigned long CANInterface_getActualPositionCount(
		struct CANInterface * canInterface) {

	if (canInterface->enable) {
	}
	else {
		return 0;
	}

	unsigned long response;

	CANInterface_readObjectDictionary(
			canInterface,
			MOTOR_DRIVER_ACTUAL_POSITION_INDEX,
			MOTOR_DRIVER_ACTUAL_POSITION_SUBINDEX,
			MOTOR_DRIVER_ACTUAL_POSITION_READ_LENGTH,
			&response);

	return response;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 电机参数配置 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*********************************
 *
 *	函数说明：	设置 MaxAcceleration
 *
 *	@var	canInterface->canID			驱动器 CAN ID 号
 *	@var	accLimitation	加速度约束		(1000 enc counts / sec2)
 *
 *********************************/
void CANInterface_setAccelerationInCPS2(
		struct CANInterface * canInterface,
		long accLimitationCPS2) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	unsigned char bytes[4] = {0x00, 0x00, 0x00, 0x00};

	bytes[0] = (accLimitationCPS2 >> 0) & 0xFF;
	bytes[1] = (accLimitationCPS2 >> 8) & 0xFF;
	bytes[2] = (accLimitationCPS2 >> 16) & 0xFF;
	bytes[3] = (accLimitationCPS2 >> 24) & 0xFF;

	CANInterface_writeObjectDictionaryNotCareResponse(
			canInterface,
			MOTOR_DRIVER_ACCELERATE_LIMITATION_INDEX,
			MOTOR_DRIVER_ACCELERATE_LIMITATION_SUBINDEX,
			MOTOR_DRIVER_ACCELERATE_LIMITATION_WRITE_LENGTH,
			bytes);
}

/*********************************
 *
 *	函数说明：	设置 MaxAcceleration
 *
 *	@var	canInterface->canID			驱动器 CAN ID 号
 *	@var	accLimitation	加速度约束		(r / sec2)
 *
 *********************************/
void CANInterface_setAccelerationInRPS2(
		struct CANInterface * canInterface,
		long accLimitationRPS2) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	// 单位转换
	long _accLimitation = accLimitationRPS2 * 2000.0 / 1000.0;

	CANInterface_setAccelerationInCPS2(canInterface, _accLimitation);
}

/*********************************
 *
 *	函数说明：	设置 MaxDeceleration
 *
 *	@var	canInterface->canID			驱动器 CAN ID 号
 *	@var	decLimitation	加速度约束		(1000 enc counts / sec2)
 *
 *********************************/
void CANInterface_setDecelerationInCPS2(
		struct CANInterface * canInterface,
		long decLimitationCPS2) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	unsigned char bytes[4] = {0x00, 0x00, 0x00, 0x00};

	bytes[0] = (decLimitationCPS2 >> 0) & 0xFF;
	bytes[1] = (decLimitationCPS2 >> 8) & 0xFF;
	bytes[2] = (decLimitationCPS2 >> 16) & 0xFF;
	bytes[3] = (decLimitationCPS2 >> 24) & 0xFF;

	CANInterface_writeObjectDictionaryNotCareResponse(
			canInterface,
			MOTOR_DRIVER_DECELERATE_LIMITATION_INDEX,
			MOTOR_DRIVER_DECELERATE_LIMITATION_SUBINDEX,
			MOTOR_DRIVER_DECELERATE_LIMITATION_WRITE_LENGTH,
			bytes);
}

/*********************************
 *
 *	函数说明：	设置 MaxDeceleration
 *
 *	@var	canInterface->canID			驱动器 CAN ID 号
 *	@var	decLimitation	加速度约束			(r / sec2)
 *
 *********************************/
void CANInterface_setDecelerationInRPS2(
		struct CANInterface * canInterface,
		long decLimitationRPS2) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	long _decLimitation = decLimitationRPS2 * 2000.0 / 1000.0;

	CANInterface_setDecelerationInCPS2(canInterface, _decLimitation);
}

/*********************************
 *
 *	函数说明：	设置 MaxVelocity
 *
 *	@var	canInterface->canID		驱动器 CAN ID number
 *	@var	vel						速度值			(0.1 counts / sec)
 *									0 ~ 500,000,000
 *
 *********************************/
void CANInterface_setMaxVelocityInCPS(
		struct CANInterface * canInterface,
		long maxVelCPS) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	unsigned char bytes[4] = {0x00, 0x00, 0x00, 0x00};

	bytes[0] = (maxVelCPS >> 0) & 0xFF;
	bytes[1] = (maxVelCPS >> 8) & 0xFF;
	bytes[2] = (maxVelCPS >> 16) & 0xFF;
	bytes[3] = (maxVelCPS >> 24) & 0xFF;

	CANInterface_writeObjectDictionaryNotCareResponse(
			canInterface,
			MOTOR_DRIVER_VELOCITY_LIMITATION_INDEX,
			MOTOR_DRIVER_VELOCITY_LIMITATION_SUBINDEX,
			MOTOR_DRIVER_VELOCITY_LIMITATION_WRITE_LENGTH,
			bytes);
}

/*********************************
 *
 *	函数说明：	设置 TargetVelocity
 *
 *	@var	canInterface->canID		驱动器 CAN ID 号
 *	@var	vel						速度值（r/s）
 *
 *********************************/
void CANInterface_setMaxVelocityInRPS(
		struct CANInterface * canInterface,
		float maxVelRPS) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	CANInterface_setMaxVelocityInCPS(canInterface, (long)(maxVelRPS * 20000));
}

/*********************************
 *
 *	函数说明：	设置 TargetVelocity
 *
 *	@var	canInterface->canID		驱动器 CAN ID number
 *	@var	vel						速度值			(0.1 counts / sec)
 *									-500,000,000 ~ 500,000,000
 *
 *********************************/
void CANInterface_setVelocityInCPS(
		struct CANInterface * canInterface,
		long velCPS) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	unsigned char bytes[4] = {0x00, 0x00, 0x00, 0x00};

	bytes[0] = (velCPS >> 0) & 0xFF;
	bytes[1] = (velCPS >> 8) & 0xFF;
	bytes[2] = (velCPS >> 16) & 0xFF;
	bytes[3] = (velCPS >> 24) & 0xFF;

	CANInterface_writeObjectDictionaryNotCareResponse(
			canInterface,
			MOTOR_DRIVER_TARGET_VELOCITY_INDEX,
			MOTOR_DRIVER_TARGET_VELOCITY_SUBINDEX,
			MOTOR_DRIVER_TARGET_VELOCITY_WRITE_LENGTH,
			bytes);
}

/*********************************
 *
 *	函数说明：	设置 TargetVelocity
 *
 *	@var	canInterface->canID		驱动器 CAN ID 号
 *	@var	vel						速度值（r/s）
 *
 *********************************/
void CANInterface_setVelocityInRPS(
		struct CANInterface * canInterface,
		float velRPS) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	CANInterface_setVelocityInCPS(canInterface, (long)(velRPS * 20000));
}



/*********************************
 *
 *	函数说明：	设置 TargetPosition
 *
 *********************************/
void CANInterface_setPositionInCount(
		struct CANInterface * canInterface,
		long positionCount) {

	if (canInterface->enable) {
	}
	else {
		return;
	}

	unsigned char bytes[4] = {0x00, 0x00, 0x00, 0x00};

	bytes[0] = (positionCount >> 0) & 0xFF;
	bytes[1] = (positionCount >> 8) & 0xFF;
	bytes[2] = (positionCount >> 16) & 0xFF;
	bytes[3] = (positionCount >> 24) & 0xFF;

	CANInterface_writeObjectDictionaryNotCareResponse(
			canInterface,
			MOTOR_DRIVER_ACTUAL_POSITION_INDEX,
			MOTOR_DRIVER_ACTUAL_POSITION_SUBINDEX,
			MOTOR_DRIVER_ACTUAL_POSITION_WRITE_LENGTH,
			bytes);
}
