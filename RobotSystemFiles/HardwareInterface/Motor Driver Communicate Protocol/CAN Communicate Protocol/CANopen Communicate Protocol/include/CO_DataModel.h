/*
 * CO_DataStruct.h
 *
 *  Created on: 2016-10-24
 *      Author: e701
 */

#ifndef CO_DATASTRUCT_H_
#define CO_DATASTRUCT_H_

struct struct_CO_Data;
typedef struct struct_CO_Data CO_Data;

#include "../../../../../../RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/DataParamPreDefine.h"
#include "../../../../../../RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/TestMasterStruct.h"
#include "../../../../../../RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/SDOModel.h"

/*********************************
 *
 *	结构体说明：		CAN 通讯参数集，很重要!!!
 *
 *	结构体描述：		对于这个结构体，会在 CANopen_TestSlave.c 中进行初始化
 *					由于本来使用的是从机模式，所以这里需要修改为主机模式 CANopen_TestMaster.c
 *
 *********************************/
struct struct_CO_Data {

	/* Object dictionary */
	UNS8 *bDeviceNodeId; 									// node id
	const indextable *objdict;								// index + subindex
//	s_PDO_status *PDO_status;
//	TIMER_HANDLE *RxPDO_EventTimers;
//	void (*RxPDO_EventTimers_Handler)(CO_Data*, UNS32);
	const quick_index *firstIndex;
	const quick_index *lastIndex;
	const UNS16 *ObjdictSize;
	const UNS8 *iam_a_slave;
//	valueRangeTest_t valueRangeTest;

	/* SDO */
	s_transfer transfers[SDO_MAX_SIMULTANEOUS_TRANSFERTS];

	/* State machine */
	e_nodeState nodeState;
//	s_state_communication CurrentCommunicationState;

	/* NMT-heartbeat */
//	UNS8 *ConsumerHeartbeatCount;
//	UNS32 *ConsumerHeartbeatEntries;
//	TIMER_HANDLE *ConsumerHeartBeatTimers;
//	UNS16 *ProducerHeartBeatTime;
//	TIMER_HANDLE ProducerHeartBeatTimer;
//	e_nodeState NMTable[NMT_MAX_NODE_ID];

	/* SYNC */
//	TIMER_HANDLE syncTimer;
//	UNS32 *COB_ID_Sync;
//	UNS32 *Sync_Cycle_Period;

	/*UNS32 *Sync_window_length;*/
//	post_sync_t post_sync;
//	post_TPDO_t post_TPDO;

	/* General */
//	UNS8 toggle;
	scanIndexOD_t scanIndexOD;

	/* EMCY */
//	e_errorState error_state;
//	UNS8 error_history_size;
//	UNS8* error_number;
//	UNS32* error_first_element;
//	UNS8* error_register;
//	UNS32* error_cobid;
};

/*********************************
 *
 *	宏定义说明：		CO_Data structure Init
 *
 *********************************/
#define CANOPEN_NODE_DATA_INITIALIZER(NODE_PREFIX) {\
		/* Object dictionary*/\
		& NODE_PREFIX ## _bDeviceNodeId,     /* bDeviceNodeId */\
		NODE_PREFIX ## _objdict,             /* objdict  */\
		\
		& NODE_PREFIX ## _firstIndex,        /* firstIndex */\
		& NODE_PREFIX ## _lastIndex,         /* lastIndex */\
		& NODE_PREFIX ## _ObjdictSize,       /* ObjdictSize */\
		& NODE_PREFIX ## _iam_a_slave,       /* iam_a_slave */\
		\
		/* SDO, structure s_transfer */\
		{\
			s_transfer_Initializer\
		},\
		\
		/* State machine*/\
		Unknown_state,      /* nodeState */\
		/* structure s_state_communication */\
		\
		/* SYNC */\
		\
		/* General */\
		NODE_PREFIX ## _scanIndexOD /* scanIndexOD */\
		\
		/* EMCY */\
		}

#endif /* CO_DATASTRUCT_H_ */
