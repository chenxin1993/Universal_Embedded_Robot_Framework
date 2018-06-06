/*
 * CANInterface.h
 *
 *  Created on: 2016-12-18
 *      Author: e701
 */

#ifndef CANOPENMOTORCONTROLCANIDINTERFACE_H_
#define CANOPENMOTORCONTROLCANIDINTERFACE_H_

#include "CAN_OPEN_OBJECT_DICTIONARY_INDEX.h"
#include "../include/CO_DataModel.h"
#include "../include/DataParamPreDefine.h"
#include "../include/FuncDeclaration.h"
#include "../include/MessageModel.h"

struct CANInterface {

	int enable;
	int canID;
};

//-------------------- 模型相关 ----------------------
void CANInterface_init(
		struct CANInterface * canInterface,
		int canID,
		int enable);
void CANInterface_copy(
		struct CANInterface * canInterfaceTo,
		struct CANInterface * canInterfaceFrom);
void CANInterface_flush(
		struct CANInterface * canInterface);
//-------------------- 模型相关 ----------------------

//-------------------- 节点控制相关 ----------------------
void 	CANInterface_enableCANNode(struct CANInterface * canInterface);
void 	CANInterface_disableCANNode(struct CANInterface * canInterface);
void 	CANInterface_setCANNodePreOperational(struct CANInterface * canInterface);
void 	CANInterface_resetCANNode(struct CANInterface * canInterface);
//-------------------- 节点控制相关 ----------------------

//-------------------- 电机控制相关 ----------------------
void 	CANInterface_enableDriver(struct CANInterface * canInterface);
void 	CANInterface_disableDriver(struct CANInterface * canInterface);

void 	CANInterface_setPositionControlMode(struct CANInterface * canInterface);
void 	CANInterface_setVelocityControlMode(struct CANInterface * canInterface);
void 	CANInterface_setTorqueControlMode(struct CANInterface * canInterface);

unsigned long	CANInterface_getActualCurrent(struct CANInterface * canInterface);
unsigned long 	CANInterface_getActualVelocity(struct CANInterface * canInterface);
unsigned long 	CANInterface_getActualPositionCount(struct CANInterface * canInterface);

void 	CANInterface_setAccelerationInCPS2(struct CANInterface * canInterface, long accLimitationCPS2);
void 	CANInterface_setAccelerationInRPS2(struct CANInterface * canInterface, long accLimitationRPS2);
void 	CANInterface_setDecelerationInCPS2(struct CANInterface * canInterface, long decLimitationCPS2);
void 	CANInterface_setDecelerationInRPS2(struct CANInterface * canInterface, long decLimitationRPS2);
void 	CANInterface_setMaxVelocityInCPS(struct CANInterface * canInterface, long maxVelCPS);
void 	CANInterface_setMaxVelocityInRPS(struct CANInterface * canInterface, float maxVelRPS);
void 	CANInterface_setVelocityInCPS(struct CANInterface * canInterface, long velCPS);
void 	CANInterface_setVelocityInRPS(struct CANInterface * canInterface, float velRPS);
void 	CANInterface_setPositionInCount(struct CANInterface * canInterface, long positionCount);
//-------------------- 电机控制相关 ----------------------

#endif /* CANOPENMOTORCONTROLCANIDINTERFACE_H_ */
