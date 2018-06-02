/*
 * dataParamDefine.h
 *
 *  Created on: 2016-10-24
 *      Author: e701
 */

#ifndef DATAPARAMDEFINE_H_
#define DATAPARAMDEFINE_H_

/******************************************************* 别名(参数)定义 *********************************************************/

#define LEFT_LEG_MOTOR1_CANID	1
#define LEFT_LEG_MOTOR2_CANID	2
#define RIGHT_LEG_MOTOR1_CANID	3
#define RIGHT_LEG_MOTOR2_CANID	4

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Data Type Define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// Integers
#define INTEGER8 signed char
#define INTEGER16 int
#define INTEGER24 long
#define INTEGER32 long
#define INTEGER40 long long
#define INTEGER48 long long
#define INTEGER56 long long
#define INTEGER64 long long

// Unsigned integers
#define UNS8   unsigned char
#define UNS16  unsigned int			//unsigned short
#define UNS32  unsigned long
#define UNS24  unsigned long
#define UNS40  unsigned long long
#define UNS48  unsigned long long
#define UNS56  unsigned long long
#define UNS64  unsigned long long

// Reals
#define REAL32 float
#define REAL64 double

// Reals
#define REAL32	float
#define REAL64 double

#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

/********************Big endian or small endian******************/
#define UNS16_LE(v)  (v)
#define UNS32_LE(v)  (v)

/********************** Can Message *********************/
#define REQUEST 		1
#define NOT_A_REQUEST 	0

/************************* CANOPEN EMCY *************************/
#define EMCY_MAX_ERRORS 8

typedef enum enum_errorState {
  Error_free		= 0x00,
  Error_occurred	= 0x01
} e_errorState;

/************************* CANOPEN Timer ************************/
#define MAX_NB_TIMER 				5
#define TIMEVAL 					UNS32
#define TIMER_HANDLE 				INTEGER16
#define TIMEVAL_MAX 				0xFFFF
#define MS_TO_TIMEVAL(ms) 			((ms) * 1000)  //change @bruce
#define US_TO_TIMEVAL(us) 			((us) * 1)     //change @bruce

#define TIMER_FREE 			0		/* 空闲线程 */
#define TIMER_ARMED 		1		/* 准备状态的线程 */
#define TIMER_TRIG 			2		/* 已触发的线程 */
#define TIMER_TRIG_PERIOD 	3
#define TIMER_NONE 			-1

/************************* CANOPEN State ************************/
/*  Function Codes defined in the canopen DS301 */
#define NMT		   0x0	// 网络节点状态管理
#define SYNC       0x1	// 同步信号
#define TIME_STAMP 0x2	// 时间戳
#define PDO1tx     0x3
#define PDO1rx     0x4
#define PDO2tx     0x5
#define PDO2rx     0x6
#define PDO3tx     0x7
#define PDO3rx     0x8
#define PDO4tx     0x9
#define PDO4rx     0xA
#define SDOtx      0xB
#define SDOrx      0xC
#define NODE_GUARD 0xE
#define LSS 	   0xF֡

typedef enum enum_nodeState {
  Initialisation  = 0x00,
  Disconnected    = 0x01,
  Connecting      = 0x02,
  Preparing       = 0x02,
  Stopped         = 0x04,
  Operational     = 0x05,
  Pre_operational = 0x7F,
  Unknown_state   = 0x0F
} e_nodeState;

/************************* CANOPEN NMT ************************/
#define NMT_MAX_NODE_ID 	128 // max 128

#define NMT_Start_Node              0x01
#define NMT_Stop_Node               0x02
#define NMT_Enter_PreOperational    0x80
#define NMT_Reset_Node              0x81
#define NMT_Reset_Comunication      0x82

/************************* CANOPEN PDO ************************/
/* constantes used in the different state machines */
#define state1  0x01
#define state2  0x02
#define state3  0x03
#define state4  0x04
#define state5  0x05
#define state6  0x06
#define state7  0x07
#define state8  0x08
#define state9  0x09
#define state10 0x0A
#define state11 0x0B

/* Status of the TPDO : */
#define PDO_INHIBITED 		0x01
#define PDO_RTR_SYNC_READY 	0x01

/** definitions of the different types of PDOs' transmission */
#define TRANS_EVERY_N_SYNC(n) (n) /*n = 1 to 240 */
#define TRANS_SYNC_ACYCLIC    0    /* Trans after reception of n SYNC. n = 1 to 240 */
#define TRANS_SYNC_MIN        1    /* Trans after reception of n SYNC. n = 1 to 240 */
#define TRANS_SYNC_MAX        240  /* Trans after reception of n SYNC. n = 1 to 240 */
#define TRANS_RTR_SYNC        252  /* Transmission on request */
#define TRANS_RTR             253  /* Transmission on request */
#define TRANS_EVENT_SPECIFIC  254  /* Transmission on event */
#define TRANS_EVENT_PROFILE   255  /* Transmission on event */

/************************* CANOPEN SDO ************************/
#define SDO_MAX_LENGTH_TRANSFERT 				8
#define SDO_MAX_SIMULTANEOUS_TRANSFERTS 		1			// 这里暂时设置为1, 不允许并行处理
#define SDO_TIMEOUT_MS 							3000U

/** definitions used for object dictionary access. ie SDO Abort codes.*/
#define OD_SUCCESSFUL 	             0x00000000
#define OD_READ_NOT_ALLOWED          0x06010001
#define OD_WRITE_NOT_ALLOWED         0x06010002
#define OD_NO_SUCH_OBJECT            0x06020000
#define OD_NOT_MAPPABLE              0x06040041
#define OD_LENGTH_DATA_INVALID       0x06070010
#define OD_NO_SUCH_SUBINDEX 	     0x06090011
#define OD_VALUE_RANGE_EXCEEDED      0x06090030 /* Value range test result */
#define OD_VALUE_TOO_LOW             0x06090031 /* Value range test result */
#define OD_VALUE_TOO_HIGH            0x06090032 /* Value range test result */
/* Others SDO abort codes */
#define SDOABT_TOGGLE_NOT_ALTERNED   0x05030000
#define SDOABT_TIMED_OUT             0x05040000
#define SDOABT_OUT_OF_MEMORY         0x05040005 /* Size data exceed SDO_MAX_LENGTH_TRANSFERT */
#define SDOABT_GENERAL_ERROR         0x08000000 /* Error size of SDO message */
#define SDOABT_LOCAL_CTRL_ERROR      0x08000021

/** Status of the SDO transmission*/
#define SDO_RESET                		0x0      /* Transmission not started. Init state. */
#define SDO_FINISHED             		0x1      /* data are available */
#define	SDO_ABORTED_RCV          		0x80     /* Received an abort message. Data not available */
#define	SDO_ABORTED_INTERNAL     		0x85     /* Aborted but not because of an abort message. */
#define	SDO_DOWNLOAD_IN_PROGRESS 		0x2
#define	SDO_UPLOAD_IN_PROGRESS   		0x3
#define	SDO_BLOCK_DOWNLOAD_IN_PROGRESS 	0x4
#define	SDO_BLOCK_UPLOAD_IN_PROGRESS   	0x5

/* Status of the node during the SDO transfert : */
#define SDO_SERVER  0x1
#define SDO_CLIENT  0x2
#define SDO_UNKNOWN 0x3

/* SDO expedited initial upload command */
#define SDO_EXPEDITED_UPLOAD_ONE_BYTE_REQUEST		0x4F
#define SDO_EXPEDITED_UPLOAD_TWO_BYTE_REQUEST		0x4B
#define SDO_EXPEDITED_UPLOAD_THREE_BYTE_REQUEST		0x47
#define SDO_EXPEDITED_UPLOAD_FOUR_BYTE_REQUEST		0x43

/* SDO expedited initial download command */
#define SDO_EXPEDITED_DOWNLOAD_ONE_BYTE_REQUEST		0x2F
#define SDO_EXPEDITED_DOWNLOAD_TWO_BYTE_REQUEST		0x2B
#define SDO_EXPEDITED_DOWNLOAD_THREE_BYTE_REQUEST	0x27
#define SDO_EXPEDITED_DOWNLOAD_FOUR_BYTE_REQUEST	0x23

/* SDO block upload client subcommand */
#define SDO_BCS_INITIATE_UPLOAD_REQUEST 0
#define SDO_BCS_END_UPLOAD_REQUEST      1
#define SDO_BCS_UPLOAD_RESPONSE         2
#define SDO_BCS_START_UPLOAD            3

/* SDO block upload server subcommand */
#define SDO_BSS_INITIATE_UPLOAD_RESPONSE 0
#define SDO_BSS_END_UPLOAD_RESPONSE      1

/* SDO block download client subcommand */
#define SDO_BCS_INITIATE_DOWNLOAD_REQUEST 0
#define SDO_BCS_END_DOWNLOAD_REQUEST      1

/* SDO block download server subcommand */
#define SDO_BSS_INITIATE_DOWNLOAD_RESPONSE 0
#define SDO_BSS_END_DOWNLOAD_RESPONSE      1
#define SDO_BSS_DOWNLOAD_RESPONSE          2

typedef enum {RXSTEP_INIT, RXSTEP_STARTED, RXSTEP_END } rxStep_t;


/************************* TEST MASTER ************************/

#define boolean         0x01
#define int_8          	0x02
#define int_16          0x03
#define int_32          0x04
#define uint_8          0x05
#define uint_16         0x06
#define uint_32         0x07
#define real_32         0x08
#define visible_string  0x09
#define octet_string    0x0A
#define unicode_string  0x0B
#define time_of_day     0x0C
#define time_difference 0x0D

#define domain          0x0F
#define int_24           0x10
#define real_64          0x11
#define int_40           0x12
#define int_48           0x13
#define int_56           0x14
#define int_64           0x15
#define uint_24          0x16

#define uint_40          0x18
#define uint_48          0x19
#define uint_56          0x1A
#define uint_64          0x1B


#define pdo_communication_parameter 0x20
#define pdo_mapping                 0x21
#define sdo_parameter               0x22
#define identity                    0x23


/** Each entry of the object dictionary can be
 * 		READONLY (RO),
 * 		READ/WRITE (RW),
 *  	WRITE-ONLY (WO)*/
#define RW     0x00
#define WO     0x01
#define RO     0x02

#define TO_BE_SAVE  0x04
#define DCF_TO_SEND 0x08

#define StateHandle(a,b,c,d,e) (((a!=0xFF)?(controlword.bit.SwitchOn==a?1:0):1) && \
								((b!=0xFF)?(controlword.bit.EnableVol==b?1:0):1) && \
								((c!=0xFF)?(controlword.bit.QuickStop==c?1:0):1) && \
								((d!=0xFF)?(controlword.bit.EnableOper==d?1:0):1) && \
								((e!=0xFF)?(controlword.bit.ResetFault==e?1:0):1))

enum DirverStates {
  	NotReadySwitchon 		= 0x00,
  	SwitchOnDisabled    	= 0x01,
  	ReadySwitchOn      		= 0x02,
  	SwitchedOn       		= 0x03,
  	OperationEnabled    	= 0x04,
  	QuickStopActive     	= 0x05,
  	FaultReactionActive 	= 0x06,
  	Fault   				= 0x07
};
enum DriverOperMode {
	ProfileEmgStop			=-3,
	ProfileStop				=-2,
	ProfileMultiPosMode		=-1,
	NullMode				=0,
	ProfilePosMode			=1,
	ProfileVelMode			=3,
	ProfileHomMode			=6
};

#endif /* DATAPARAMDEFINE_H_ */
