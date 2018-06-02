
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/CO_DataModel.h>
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/DataParamPreDefine.h>
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/TestMasterStruct.h>

/************************************
 *
 *	变量说明：	来自 CANopen_FuncCode.c
 *
 ***********************************/
extern struct FUNCCODE 		Func;
extern struct FUNCCODE 		FuncInit;

extern union ControlWord 	controlword;
extern union StatusWord 	statusword;
extern unsigned int 		DriverState;

union ControlWord controlword;
union StatusWord statusword;

/**************************************************************************/
/* Declaration of the value range types                                   */
/**************************************************************************/
#define valueRange_EMC 0x9F /* Type for index 0x1003 subindex 0x00 (only set of value 0 is possible) */
UNS32 TestMaster_valueRangeTest (UNS8 typeValue, void * value)
{
  switch (typeValue) {
    case valueRange_EMC:
      if (*(UNS8*)value != (UNS8)0) return OD_VALUE_RANGE_EXCEEDED;
      break;
  }
  return 0;
}

/**************************************************************************/
/* The node id                                                            */
/**************************************************************************/
/* node_id default value.*/
UNS8 TestMaster_bDeviceNodeId = 0x03;

/**************************************************************************/
/* Array of message processing information */

const UNS8 TestMaster_iam_a_slave = 0;

TIMER_HANDLE TestMaster_heartBeatTimers[1];

void TestMaster_post_sync(CO_Data* d)
{
    ;
}

void TestMaster_post_TPDO(CO_Data* d)
{
	;
}

/*
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                               OBJECT DICTIONARY

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
*/

/* index 0x1000 :   Device Type. */
                    subindex TestMaster_Index1000[] =
                     {
                       { RO, uint_32, sizeof (UNS64), (void*)&Func.obj1000 }
                     };
/* index 0x1001 :   Error Register. */
                    subindex TestMaster_Index1001[] =
                     {
                       { RO, uint_8, sizeof (UNS8), (void*)&Func.obj1001 }
                     };
/* index 0x1003 :   Pre-defined Error Field. */
                    ODCallback_t TestMaster_Index1003_callbacks[] =
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex TestMaster_Index1003[] =
                     {
                       { RW, valueRange_EMC, sizeof (UNS8), (void*)&Func.highestSubIndex_obj1003 },
                       { RO, uint_32, sizeof (UNS64), (void*)&Func.obj1003[0] },
                       { RO, uint_32, sizeof (UNS64), (void*)&Func.obj1003[1] },
                       { RO, uint_32, sizeof (UNS64), (void*)&Func.obj1003[2] },
                       { RO, uint_32, sizeof (UNS64), (void*)&Func.obj1003[3] }
                     };
/* index 0x1005 :   SYNC COB ID. */
                    ODCallback_t TestMaster_Index1005_callbacks[] =
                     {
                       NULL,
                     };
                    subindex TestMaster_Index1005[] =
                     {
                       { RW, uint_32, sizeof (UNS64), (void*)&Func.obj1005 }
                     };
/* index 0x1006 :   Communication / Cycle Period. */
                    ODCallback_t TestMaster_Index1006_callbacks[] =
                     {
                       NULL,
                     };
                    subindex TestMaster_Index1006[] =
                     {
                       { RW, uint_32, sizeof (UNS64), (void*)&Func.obj1006 }
                     };
/* index 0x1009 :   hardware version */
                    subindex TestMaster_Index1009[] =
                     {
                       { RO, uint_16, sizeof (UNS16), (void*)&Func.obj1009 }
                     };
/* index 0x100A :   software version */
                    subindex TestMaster_Index100A[] =
                     {
                       { RO, uint_16, sizeof (UNS16), (void*)&Func.obj100A }
                     };
/* index 0x1014 :   Emergency COB ID. */
                    subindex TestMaster_Index1014[] =
                     {
                       { RW, uint_32, sizeof (UNS64), (void*)&Func.obj1014 }
                     };
/* index 0x1016 :   Consumer Heartbeat Time */
                    UNS32 TestMaster_obj1016[]={0};

/* index 0x1017 :   Producer Heartbeat Time. */
                    ODCallback_t TestMaster_Index1017_callbacks[] =
                    {
                    		NULL,
                    };
                    subindex TestMaster_Index1017[] =
                    {
                    		{ RW, uint_16, sizeof (UNS32), (void*)&Func.obj1017 }
                    };
/* index 0x1200 :   Client SDO1 Parameter. */
                    subindex TestMaster_Index1200[] =
                    {
                    		{ RO, uint_8, sizeof (UNS8), (void*)&Func.highestSubIndex_obj1200 },
                    		{ RW, uint_32, sizeof (UNS32), (void*)&Func.obj1200_COB_ID_Client_to_Server_Transmit_SDO },
                    		{ RW, uint_32, sizeof (UNS32), (void*)&Func.obj1200_COB_ID_Server_to_Client_Receive_SDO },
                    };
/* index 0x1201 :   Client SDO2 Parameter. */
                    subindex TestMaster_Index1201[] =
                    {
                    		{ RO, uint_8, sizeof (UNS8), (void*)&Func.highestSubIndex_obj1201 },
                    		{ RW, uint_32, sizeof (UNS32), (void*)&Func.obj1201_COB_ID_Client_to_Server_Transmit_SDO },
                    		{ RW, uint_32, sizeof (UNS32), (void*)&Func.obj1201_COB_ID_Server_to_Client_Receive_SDO },
                    };
/* index 0x1202 :   Client SDO3 Parameter. */
                    subindex TestMaster_Index1202[] =
                    {
                    		{ RO, uint_8, sizeof (UNS8), (void*)&Func.highestSubIndex_obj1202 },
                    		{ RW, uint_32, sizeof (UNS32), (void*)&Func.obj1202_COB_ID_Client_to_Server_Transmit_SDO },
                    		{ RW, uint_32, sizeof (UNS32), (void*)&Func.obj1202_COB_ID_Server_to_Client_Receive_SDO },
                    };
/* index 0x1203 :   Client SDO4 Parameter. */
                    subindex TestMaster_Index1203[] =
                    {
                    		{ RO, uint_8, sizeof (UNS8), (void*)&Func.highestSubIndex_obj1203 },
                    		{ RW, uint_32, sizeof (UNS32), (void*)&Func.obj1203_COB_ID_Client_to_Server_Transmit_SDO },
                    		{ RW, uint_32, sizeof (UNS32), (void*)&Func.obj1203_COB_ID_Server_to_Client_Receive_SDO },
                    };

/****************************************************************************

								 FUNCODE

*****************************************************************************/

/******************************************************************************/

const indextable TestMaster_objdict[] =
{
	{ (subindex*)TestMaster_Index1000,sizeof(TestMaster_Index1000)/sizeof(TestMaster_Index1000[0]), 0x1000},
	{ (subindex*)TestMaster_Index1001,sizeof(TestMaster_Index1001)/sizeof(TestMaster_Index1001[0]), 0x1001},
	{ (subindex*)TestMaster_Index1003,sizeof(TestMaster_Index1003)/sizeof(TestMaster_Index1003[0]), 0x1003},
	{ (subindex*)TestMaster_Index1005,sizeof(TestMaster_Index1005)/sizeof(TestMaster_Index1005[0]), 0x1005},
	{ (subindex*)TestMaster_Index1006,sizeof(TestMaster_Index1006)/sizeof(TestMaster_Index1006[0]), 0x1006},
	{ (subindex*)TestMaster_Index1009,sizeof(TestMaster_Index1009)/sizeof(TestMaster_Index1006[0]), 0x1009},
	{ (subindex*)TestMaster_Index100A,sizeof(TestMaster_Index100A)/sizeof(TestMaster_Index1006[0]), 0x100A},
	{ (subindex*)TestMaster_Index1014,sizeof(TestMaster_Index1014)/sizeof(TestMaster_Index1014[0]), 0x1014},
	{ (subindex*)TestMaster_Index1017,sizeof(TestMaster_Index1017)/sizeof(TestMaster_Index1017[0]), 0x1017},
	{ (subindex*)TestMaster_Index1200,sizeof(TestMaster_Index1200)/sizeof(TestMaster_Index1200[0]), 0x1200},
	{ (subindex*)TestMaster_Index1201,sizeof(TestMaster_Index1201)/sizeof(TestMaster_Index1201[0]), 0x1201},
	{ (subindex*)TestMaster_Index1202,sizeof(TestMaster_Index1202)/sizeof(TestMaster_Index1202[0]), 0x1202},
	{ (subindex*)TestMaster_Index1203,sizeof(TestMaster_Index1203)/sizeof(TestMaster_Index1203[0]), 0x1203}
};

const indextable * TestMaster_scanIndexOD (
		UNS16 wIndex,
		UNS32 * errorCode,
		ODCallback_t **callbacks)
{
	int i;
	*callbacks = NULL;
	switch(wIndex){
		case 0x1000: i = 0;break;
		case 0x1001: i = 1;break;
		case 0x1003: i = 2;*callbacks = TestMaster_Index1003_callbacks; break;
		case 0x1005: i = 3;*callbacks = TestMaster_Index1005_callbacks; break;
		case 0x1006: i = 4;*callbacks = TestMaster_Index1006_callbacks; break;
		case 0x1009: i = 5;break;
		case 0x100A: i = 6;break;
		case 0x1014: i = 7;break;
		case 0x1017: i = 8;*callbacks = TestMaster_Index1017_callbacks; break;
		case 0x1200: i = 9;break;
		case 0x1201: i = 10;break;
		case 0x1202: i = 11;break;
		case 0x1203: i = 12;break;

		default:
			*errorCode = OD_NO_SUCH_OBJECT;
			return NULL;
	}
	*errorCode = OD_SUCCESSFUL;
	return &TestMaster_objdict[i];
}

//s_PDO_status TestMaster_PDO_status[4] = {
//		s_PDO_status_Initializer,
//		s_PDO_status_Initializer,
//		s_PDO_status_Initializer,
//		s_PDO_status_Initializer};

quick_index TestMaster_firstIndex = {
  0, 	/* SDO_SVR */
  9, 	/* SDO_CLT */
  13, 	/* PDO_RCV */
  17, 	/* PDO_RCV_MAP */
  21, 	/* PDO_TRS */
  25 	/* PDO_TRS_MAP */
};

quick_index TestMaster_lastIndex = {
  0, 	/* SDO_SVR */
  12, 	/* SDO_CLT */
  16, 	/* PDO_RCV */
  20, 	/* PDO_RCV_MAP */
  24, 	/* PDO_TRS */
  28 	/* PDO_TRS_MAP */
};

UNS16 TestMaster_ObjdictSize = sizeof(TestMaster_objdict)/sizeof(TestMaster_objdict[0]);

//CO_Data TestMaster_Data;
CO_Data TestMaster_Data = CANOPEN_NODE_DATA_INITIALIZER(TestMaster);
/**
 *	函数说明：	貌似结构体直接赋值在 DSP 中总容易出问题，
 *				所以采用指针进行赋值
 */

