
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/TestMasterStruct.h>

struct FUNCCODE Func;
struct FUNCCODE FuncInit={
	0,
	0x00040192,	/* index 0x1000 :   Device Type. ��Ҫ���ֲ� */
	0x0,		/* index 0x1001 :   Error Register. */
	0x0,		/* index 0x1003 :   Pre-defined Error Field. */
	{0,0,0,0},
	0x80,		/* index 0x1005 :   SYNC COB ID. */	
	0x0,		/* index 0x1006 :   Communication / Cycle Period. */
	
	0x1,		/* index 0x1009 :   hardware version */
	0x1,		/* index 0x100A :   software version */

	0x80,		/* index 0x1014 :   Emergency COB ID. */
	0,			/* index 0x1016 :   Consumer Heartbeat Count */
	0,			/* index 0x1017 :   Producer Heartbeat Time.����ʱ�䣬��λms */

	/*
	 *	SDO	参数说明：
	 *		子索引			含义
	 *		00h				通道数目
	 *		01h				作为服务器，接收到的 SDO 消息的 COB-ID(即为客户端发来的 0x600)
	 *		02h				作为客户端，接收到的 SDO 消息的 COB-ID(即为服务器发来的 0x580)
	 */
	2,			/* index 0x1200 :   Server SDO 1 Parameter. */
	0x601,
	0x581,

	2,			/* index 0x1201 :   Server SDO 2 Parameter. */
	0x602,
	0x582,

	2,			/* index 0x1202 :   Server SDO 3 Parameter. */
	0x603,
	0x583,

	2,			/* index 0x1203 :   Server SDO 4 Parameter. */
	0x604,
	0x584

};

