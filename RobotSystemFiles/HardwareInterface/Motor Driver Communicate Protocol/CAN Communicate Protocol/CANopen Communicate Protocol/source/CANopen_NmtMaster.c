/*
 * CANope_NMTMaster.c
 *
 *  Created on: 2016-10-28
 *      Author: e701
 */

#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/CO_DataModel.h>
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/DataParamPreDefine.h>
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/FuncDeclaration.h>
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/MessageModel.h>

/**
 *	函数说明：	发送 NMT 状态变更消息
 */
UNS32 processSendNMT(
		CO_Data* d,
		Message *m) {

	switch(m->data[0]) {
	case NMT_Start_Node:
	case NMT_Stop_Node:
	case NMT_Enter_PreOperational:
	case NMT_Reset_Node:
	case NMT_Reset_Comunication:
		masterSendNMTstateChange(d, m->data[1], m->data[0]);
		break;
	default:
		/* if can not find the state word, just do nothing */
		return 0xFFFF;
	}

	return 0;
}

/**
 * @ingroup nmtmaster
 * @brief Transmit a NMT message on the network to the slave whose nodeId is node ID.
 *
 * @param *d Pointer to a CAN object data structure
 * @param nodeId Id of the slave node
 * @param cs The order of state changement \n\n
 *
 * Allowed states :
 *  - cs =  NMT_Start_Node               // Put the node in operational mode
 *  - cs =	NMT_Stop_Node		         // Put the node in stopped mode
 *  - cs =	NMT_Enter_PreOperational     // Put the node in pre_operational mode
 *  - cs =  NMT_Reset_Node		         // Put the node in initialization mode
 *  - cs =  NMT_Reset_Comunication	     // Put the node in initialization mode
 *
 * The mode is changed according to the slave state machine mode :
 *  - initialisation  ---> pre-operational (Automatic transition)
 *  - pre-operational <--> operational
 *  - pre-operational <--> stopped
 *  - pre-operational, operational, stopped -> initialisation
 * \n\n
 * @return errorcode
 *                   - 0 if the NMT message was send
 *                   - 1 if an error occurs
 */
UNS8 masterSendNMTstateChange(
		CO_Data* d,
		UNS8 Node_ID,
		UNS8 cs) {

	Message m;

	/* message configuration */
	m.cob_id 	= 0x0000; /*(NMT) << 7*/
	m.rtr 		= NOT_A_REQUEST;
	m.len 		= 2;
	m.data[0] 	= cs;
	m.data[1] 	= Node_ID;

	return canSend(&m);
}


/**
 * @ingroup nmtmaster
 * @brief Transmit a NodeGuard message on the network to the slave whose nodeId is node ID
 *
 * @param *d Pointer to a CAN object data structure
 * @param nodeId Id of the slave node
 * @return
 *         - 0 is returned if the NodeGuard message was send.
 *         - 1 is returned if an error occurs.
 */
UNS8 masterSendNMTnodeguard(
		CO_Data* d,
		UNS8 nodeId) {

	Message m;

	/* message configuration */
	UNS16 tmp 	= nodeId | (NODE_GUARD << 7);
	m.cob_id 	= UNS16_LE(tmp);
	m.rtr 		= REQUEST;
	m.len 		= 0;

	return canSend(&m);
}

/**
 * @ingroup nmtmaster
 * @brief Ask the state of the slave node whose nodeId is node Id.
 *
 * To ask states of all nodes on the network (NMT broadcast), nodeId must be equal to 0
 * @param *d Pointer to a CAN object data structure
 * @param nodeId Id of the slave node
 */
UNS8 masterRequestNodeState(
		CO_Data* d,
		UNS8 nodeId) {
	/* FIXME: should warn for bad toggle bit. */

	/* NMTable configuration to indicate that the master is waiting
    for a Node_Guard frame from the slave whose node_id is ID
	 */
//	d->NMTable[nodeId] = Unknown_state; /* A state that does not exist
//	 */
//
//	if (nodeId == 0) { /* NMT broadcast */
//		UNS8 i = 0;
//		for (i = 0 ; i < NMT_MAX_NODE_ID ; i++) {
//			d->NMTable[i] = Unknown_state;
//		}
//	}
//
//	return masterSendNMTnodeguard(d, nodeId);
	return 0;
}
