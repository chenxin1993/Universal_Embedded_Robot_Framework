/*
 * FuncDeclaration.h
 *
 *  Created on: 2017-3-14
 *      Author: e701
 */

#ifndef __FUNCDECLARATION_H__
#define __FUNCDECLARATION_H__

#include "CO_DataModel.h"
#include "MessageModel.h"

//-------------------------- CANopen_Driver ---------------------------
void CANopenDriver_InitCanOpen(void);

void CANInit(void);
void InitECanaGpio_1(void);
void InitECana_1(void);
void canMailboxInit(void);
void InitCanInterrupt(void);
UNS8 canSend(Message *m);
UNS8 canReceive(Message *m);
UNS8 canReceiveSDO(int canID, Message *m);
void testCanSend(void);
//-------------------------- CANopen_Driver ---------------------------

//-------------------------- TestMaster ---------------------------

//-------------------------- TestMaster ---------------------------

//-------------------------- CANopen_STATE ---------------------------

UNS32 	canSendDispatch(CO_Data* d, Message *m);
void 	canReceiveDispatch(CO_Data* d, Message *m);
e_nodeState getState (CO_Data* d);
UNS8 		setState (CO_Data* d, e_nodeState newState);

//-------------------------- CANopen_STATE ---------------------------

//-------------------------- CANopen_SDO ---------------------------

void 	setSDOReceiveDataFlag(void);
void 	clearSDOReceiveDataFlag(void);
UNS32 	getSDOReceiveData(void);
void 	resetSDO (CO_Data* d);
void 	resetSDOline (CO_Data* d, UNS8 line);
UNS32 	SDOlineToObjdict (CO_Data* d, UNS8 line);
UNS32 	objdictToSDOline (CO_Data* d, UNS8 line);
UNS8 	lineToSDO (CO_Data* d, UNS8 line, UNS32 nbBytes, UNS8 * data);
UNS8 	SDOtoLine (CO_Data* d, UNS8 line, UNS32 nbBytes, UNS8 * data);
UNS8 	failedSDO (CO_Data* d, UNS8 CliServNbr, UNS8 whoami, UNS16 index, UNS8 subIndex, UNS32 abortCode);
UNS8 	initSDOline (CO_Data* d, UNS8 line, UNS8 CliServNbr, UNS16 index, UNS8 subIndex, UNS8 state);
UNS8 	getSDOfreeLine (CO_Data* d, UNS8 whoami, UNS8 *line);
UNS8 	getSDOlineOnUse (CO_Data* d, UNS8 CliServNbr, UNS8 whoami, UNS8 *line);
UNS8 	getSDOlineRestBytes (CO_Data* d, UNS8 line, UNS32 * nbBytes);
UNS8 	setSDOlineRestBytes (CO_Data* d, UNS8 line, UNS32 nbBytes);
UNS8 	sendSDO (CO_Data* d, UNS8 whoami, UNS8 CliServNbr, UNS8 *pData);
UNS8 	sendSDOabort (CO_Data* d, UNS8 whoami, UNS8 CliServNbr, UNS16 index, UNS8 subIndex, UNS32 abortCode);
void 	processSendSDOCallBack(CO_Data* d, UNS8 nodeId, UNS8 line);
UNS32 	processSendSDO(CO_Data* d, Message *m);
UNS8 	proceedReceiveSDO (CO_Data* d, Message *m);

//-------------------------- CANopen_SDO ---------------------------

//-------------------------- CANopen_NMT --------------------------
UNS8 	masterSendNMTstateChange(CO_Data* d, UNS8 Node_ID, UNS8 cs);
UNS32 	processSendNMT(CO_Data* d, Message *m);

//-------------------------- CANopen_NMT --------------------------

//-------------------------- CANopen_OD --------------------------

UNS32 getODentry( CO_Data* d,UNS16 wIndex,UNS8 bSubindex,
                   void * pDestData,
                   UNS32 * pExpectedSize,
                   UNS8 * pDataType,
                   UNS8 checkAccess,
                   UNS8 endianize);

UNS32 setODentry( CO_Data* d,
                   UNS16 wIndex,
                   UNS8 bSubindex,
                   void * pSourceData,
                   UNS32 * pExpectedSize,
                   UNS8 checkAccess,
                   UNS8 endianize);

const indextable * scanIndexOD (CO_Data* d, UNS16 wIndex, UNS32 *errorCode, ODCallback_t **Callback);
UNS32 RegisterSetODentryCallBack(CO_Data* d, UNS16 wIndex, UNS8 bSubindex, ODCallback_t Callback);
void* memcpy_1(void* dest, void* src, UNS16 count);
void* memcpy_2(void* dest, void* src, UNS16 count);
//-------------------------- CANopen_OD --------------------------

//-------------------------- CANopen_other --------------------------

//-------------------------- CANopen_other --------------------------

#ifdef __cplusplus
};
#endif

#endif /* __data_h__ */
