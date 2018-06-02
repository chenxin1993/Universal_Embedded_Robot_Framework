
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/CO_DataModel.h>
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/DataParamPreDefine.h>
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/FuncDeclaration.h>
#include <RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/MessageModel.h>
#include "../../Includes/DSP2833x_Device.h"

/************************************
 *
 *	变量说明：	来自 CANopen_FuncCode.c
 *
 ***********************************/
extern struct FUNCCODE Func;
extern struct FUNCCODE FuncInit;

/************************************
 *
 *	变量说明：	来自 CANopen_TestMaster.c
 *
 ***********************************/
extern CO_Data TestMaster_Data;

void InitFuncFactory(void);
interrupt void CanReceiveInterrupt(void);
interrupt void cpu_timer1_isr(void);

Uint16 tempcount=0;
Uint16 timersetcount=0;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CANOpen 在 28335 初始化 ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void CANopenDriver_InitCanOpen(void) {

	// 初始化字典参数
	InitFuncFactory();

	// 初始化 1ms 定时中断
	//	InitTimer1(1000);
	//	StartTimer1();

	// 初始化 CAN 外设 和 CAN 中断
	CANInit();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FuncFactory 部分 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 *	函数说明：	初始化字典参数
 */
void InitFuncFactory(void)
{
	int i;
	Uint16 ParaLength;
	unsigned int *TempAdrr1;
	unsigned int *TempAdrr2;
	Uint16 E2WrData=0;

	//	ParaLength = 166;
	ParaLength = sizeof(Func);

	TempAdrr2 = &Func.obj0000;
	TempAdrr1 = &FuncInit.obj0000;

	for (i = 0; i <= ParaLength; i++)
	{
		E2WrData = *TempAdrr1;
		*TempAdrr2 = E2WrData;

		TempAdrr2++;
		TempAdrr1++;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CAN 操作部分 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define USE_CAN_INTERRUPT 	0		// 是否开启中断

void InitCanopenMaster(void);
void StartCanopenMaster(void);

void CANInit(void)
{
	InitCanopenMaster();

	InitECanaGpio_1();
	InitECana_1();
	canMailboxInit();

#if USE_CAN_INTERRUPT
	InitCanInterrupt();
#endif

	StartCanopenMaster();
}

/**
 *	函数说明：	初始化作为主机的变量配置
 */
void InitCanopenMaster(void) {

	setState(&TestMaster_Data, Initialisation);
}

/**
 *	函数说明：	初始化作为主机的变量配置
 */
void StartCanopenMaster(void) {

	setState(&TestMaster_Data, Operational);
}

/**
 *	函数说明：	初始化 CAN GPIO 端口
 */
void InitECanaGpio_1(void)
{
	EALLOW;

	/* Enable internal pull-up for the selected CAN pins */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.

	//	GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;	  // Enable pull-up for GPIO8  (CANTXB)
	//  GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;   // Enable pull-up for GPIO12 (CANTXB)
	//  GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up for GPIO16 (CANTXB)
	GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pull-up for GPIO20 (CANTXB)

	//	GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;	  // Enable pull-up for GPIO10 (CANRXB)
	//  GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;   // Enable pull-up for GPIO13 (CANRXB)
	//  GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up for GPIO17 (CANRXB)
	GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pull-up for GPIO21 (CANRXB)

	/* Set qualification for selected CAN pins to asynch only */
	// Inputs are synchronized to SYSCLKOUT by default.
	// This will select asynch (no qualification) for the selected pins.
	// Comment out other unwanted lines.

	//    GpioCtrlRegs.GPAQSEL1.bit.GPIO10 = 3; // Asynch qual for GPIO10 (CANRXB)
	//  GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // Asynch qual for GPIO13 (CANRXB)
	//  GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch qual for GPIO17 (CANRXB)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 3; // Asynch qual for GPIO21 (CANRXB)

	/* Configure eCAN-B pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be eCAN functional pins.

	//	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 2;   // Configure GPIO8 for CANTXB operation
	//  GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;  // Configure GPIO12 for CANTXB operation
	//  GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 2;  // Configure GPIO16 for CANTXB operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 3;  // Configure GPIO20 for CANTXB operation

	//	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 2;  // Configure GPIO10 for CANRXB operation
	//  GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 2;  // Configure GPIO13 for CANRXB operation
	//  GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 2;  // Configure GPIO17 for CANRXB operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 3;  // Configure GPIO21 for CANRXB operation

	EDIS;
}

/**
 *	函数说明：	初始化 CAN 邮箱
 */
void InitECana_1(void)        // Initialize eCAN-B module
{
	struct ECAN_REGS ECanbShadow;

	EALLOW;

	/* Configure eCAN RX and TX pins for CAN operation using eCAN regs 使能CAN引脚功能 */
	ECanbShadow.CANTIOC.all = ECanbRegs.CANTIOC.all;
	ECanbShadow.CANTIOC.bit.TXFUNC = 1;
	ECanbRegs.CANTIOC.all = ECanbShadow.CANTIOC.all;

	ECanbShadow.CANRIOC.all = ECanbRegs.CANRIOC.all;
	ECanbShadow.CANRIOC.bit.RXFUNC = 1;
	ECanbRegs.CANRIOC.all = ECanbShadow.CANRIOC.all;

	/* Configure eCAN for HECC mode - (reqd to access mailboxes 16 thru 31) */
	ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
	ECanbShadow.CANMC.bit.SCB = 1;             	//P35  Select eCAN mode. 32个邮箱都可用
	ECanbShadow.CANMC.bit.WUBA = 1;				// 检测到任何活动，该模块离开断电模式
	ECanbShadow.CANMC.bit.ABO = 1;				// 自动总线打开
	ECanbShadow.CANMC.bit.SUSP = 1;
	ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;

	/* Initialize all bits of 'Message Control Register' to zero */
	// Some bits of MSGCTRL register come up in an unknown state. For proper operation,
	// all bits (including reserved bits) of MSGCTRL must be initialized to zero
	// 初始化/清空邮箱
	ECanbMboxes.MBOX0.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX1.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX2.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX3.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX4.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX5.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX6.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX7.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX8.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX9.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX10.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX11.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX12.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX13.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX14.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX15.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX16.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX17.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX18.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX19.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX20.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX21.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX22.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX23.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX24.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX25.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX26.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX27.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX28.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX29.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX30.MSGCTRL.all = 0x00000000;
	ECanbMboxes.MBOX31.MSGCTRL.all = 0x00000000;

	// TAn, RMPn, GIFn bits are all zero upon reset and are cleared again
	//  as a matter of precaution.
	ECanbRegs.CANTA.all = 0xFFFFFFFF;   /* Clear all TAn bits 消息发送成功标志位 */
	ECanbRegs.CANRMP.all = 0xFFFFFFFF;  /* Clear all RMPn bits 消息接收到标志位 */
	ECanbRegs.CANGIF0.all = 0xFFFFFFFF; /* Clear all interrupt flag bits 全局中断标志位 */
	ECanbRegs.CANGIF1.all = 0xFFFFFFFF;

	/* Configure bit timing parameters for eCANB */
	ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
	ECanbShadow.CANMC.bit.CCR = 1;            		// Set CCR = 1
	ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;

	// Wait until the CPU has been granted permission to change the configuration registers
	do
	{
		ECanbShadow.CANES.all = ECanbRegs.CANES.all;
	} while(ECanbShadow.CANES.bit.CCE != 1 );       // Wait for CCE bit to be set..

	ECanbShadow.CANBTC.all = 0;

	/* The following block is only for 150 MHz SYSCLKOUT.
       See Note at end of file. */
	/**
	 *	说明：	CAN 口接收频率设置
	 *			CANBTC	Bit-Timing Configuration Register
	 *
	 *			BRP = BRPreg + 1
	 *			TSEG1 = TSEG1reg + 1
	 *			TSEG2 = TSEG2reg + 1
	 *			BaudRate = (SYSCLKOUT / 2) / (BRP * (TSEG1 + TSEG2 + 1))
	 */
	ECanbShadow.CANBTC.bit.BRPREG 	= 4;	//9
	ECanbShadow.CANBTC.bit.TSEG2REG = 2;	//2
	ECanbShadow.CANBTC.bit.TSEG1REG = 10;	//10
	ECanbShadow.CANBTC.bit.SAM 		= 1;	// sample three times
	ECanbRegs.CANBTC.all = ECanbShadow.CANBTC.all;

	ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
	ECanbShadow.CANMC.bit.CCR = 0;            // Set CCR = 0
	ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;

	// Wait until the CPU no longer has permission to change the configuration registers
	do
	{
		ECanbShadow.CANES.all = ECanbRegs.CANES.all;
	} while(ECanbShadow.CANES.bit.CCE != 0 );       // Wait for CCE bit to be  cleared..

	/* Disable all Mailboxes  */
	ECanbRegs.CANME.all = 0;        // Required before writing the MSGIDs

	EDIS;
}

/**
 *	函数说明：	配置邮箱，使只接收特定帧的数据
 */
void canMailboxInit(void)
{
	struct ECAN_REGS ECanbShadow;

	EALLOW;
	// Standard and extended frames can be received.
	ECanbShadow.CANGAM.all = ECanbRegs.CANGAM.all;
	ECanbShadow.CANGAM.bit.AMI=1;
	ECanbRegs.CANGAM.all = ECanbShadow.CANGAM.all;
	EDIS;

	EALLOW;

	/**
	 *	MSGID 寄存器参数说明：
	 *		IDE:	标识符扩展位。IDE 位的特征根据 AMI 的位值变化
	 *				====> AMI 来自 CANGAM 全局接受屏蔽寄存器:
	 *						1. 可以接收标准帧和扩展帧；
	 *						0. 存储在邮箱中的标识符扩展位确定了哪些消息应该被收到。接收邮箱的 IDE 位确定了要进行比较的位数。
	 *		AME:	接受屏蔽使能位。AME 只用于接收邮箱。
	 *				1. 没有相应的接受屏蔽。
	 *				0. 没有使用接受屏蔽，所有标识符必须与接收消息相匹配。
	 *		AAM:	自动应答模式位。AAM 只用于发送邮箱。
	 *				1. 自动应答模式。如果接收到匹配的远程请求，CAN 模块通过发送邮箱内容来应答远程请求。
	 *				0. 正常传输模式。邮箱不会回复远程请求。远程请求帧对消息邮箱没有影响。
	 *		ID:		消息标识符。
	 *				1. 在标准模式中，如果 IDE = 0，消息标识符存储在 ID.28:18 中。ID.17:0 没有作用。
	 *				0. 在扩展标识符模式中，如果 IDE = 1，消息标识符存储在 ID.28:0 中。
	 */

	//MBOX0
	ECanbMboxes.MBOX0.MSGID.bit.AME = 1;	// 1：使用屏蔽位
	ECanbMboxes.MBOX0.MSGID.bit.AAM = 0;	// 0：正常传输模式。邮箱不会自动回复远程请求
	ECanbMboxes.MBOX0.MSGID.bit.IDE = 0;	// 0：接收标准帧
	//MBOX1
	ECanbMboxes.MBOX1.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX1.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX1.MSGID.bit.IDE = 0;
	//MBOX2
	ECanbMboxes.MBOX2.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX2.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX2.MSGID.bit.IDE = 0;
	//MBOX3
	ECanbMboxes.MBOX3.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX3.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX3.MSGID.bit.IDE = 0;
	//MBOX4
	ECanbMboxes.MBOX4.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX4.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX4.MSGID.bit.IDE = 0;
	//MBOX5
	ECanbMboxes.MBOX5.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX5.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX5.MSGID.bit.IDE = 0;
	//MBOX6
	ECanbMboxes.MBOX6.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX6.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX6.MSGID.bit.IDE = 0;
	//MBOX7
	ECanbMboxes.MBOX7.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX7.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX7.MSGID.bit.IDE = 0;
	//MBOX8
	ECanbMboxes.MBOX8.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX8.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX8.MSGID.bit.IDE = 0;
	//MBOX9
	ECanbMboxes.MBOX9.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX9.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX9.MSGID.bit.IDE = 0;
	//MBOX10
	ECanbMboxes.MBOX10.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX10.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX10.MSGID.bit.IDE = 0;
	//MBOX11
	ECanbMboxes.MBOX11.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX11.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX11.MSGID.bit.IDE = 0;
	//MBOX12
	ECanbMboxes.MBOX12.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX12.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX12.MSGID.bit.IDE = 0;
	//MBOX13
	ECanbMboxes.MBOX13.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX13.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX13.MSGID.bit.IDE = 0;
	//MBOX14
	ECanbMboxes.MBOX14.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX14.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX14.MSGID.bit.IDE = 0;
	//MBOX15
	ECanbMboxes.MBOX15.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX15.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX15.MSGID.bit.IDE = 0;

	//-------------- receive mailbox --------------

	/**
	 *	说明：	STDMSGID 用于配置接收数据的帧 ID，
	 *			也就是说如果想配置本 DSP 为 CAN 0x00 地址主机，
	 *			就写 0x600，如果配置为编号为 n 的从机，就配置为 0x60n 这样。
	 *
	 *			有疑问请咨询陈鑫师兄
	 */

	//MBOX16 receive 0x0 NMT 
	ECanbMboxes.MBOX16.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX16.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX16.MSGID.bit.IDE = 0;
	ECanbMboxes.MBOX16.MSGID.bit.STDMSGID = 0x00;	// 标准帧的 ID = 0x00
	/*
	 * 	STDMSGID:	Message Identificatifier 信息 ID 头
	 *
	 *	LAMn：	本地接受屏蔽寄存器
	 *			LAMI：	1：可以接收标准和扩展帧，对于标准帧，标识符的11位被存储在邮箱中，本地接受屏蔽寄存器的所有11位被过滤器使用。
	 *					0：存储在邮箱中的标识符扩展位决定了哪些消息应该被接收到。
	 *			LAM：	屏蔽值的设定。
	 *					一个"1"表示"无关"，即不影响屏蔽效果
	 *					一个"0"表示“相关”，意味着进入的值必须与消息标识符的相应位完全相匹配。
	 */
	ECanbLAMRegs.LAM16.bit.LAMI = 1;
	ECanbLAMRegs.LAM16.bit.LAM_H = (0x0)<<2;  //   LAM_H:13;     // 16:28, 只接收符合要求的报文

	//MBOX17 receive 0x80 EMCY
	ECanbMboxes.MBOX17.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX17.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX17.MSGID.bit.IDE = 0;
	ECanbMboxes.MBOX17.MSGID.bit.STDMSGID = 0x80;
	ECanbLAMRegs.LAM17.bit.LAMI = 1;
	ECanbLAMRegs.LAM17.bit.LAM_H = (0x00)<<2;

	//MBOX18 receive 0x581 SDO1
	ECanbMboxes.MBOX18.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX18.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX18.MSGID.bit.IDE = 0;
	ECanbMboxes.MBOX18.MSGID.bit.STDMSGID = 0x580 + LEFT_LEG_MOTOR1_CANID;
	ECanbLAMRegs.LAM18.bit.LAMI = 1;
	ECanbLAMRegs.LAM18.bit.LAM_H = (0x000)<<2;

	//MBOX19 receive 0x582 SDO2
	ECanbMboxes.MBOX19.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX19.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX19.MSGID.bit.IDE = 0;
	ECanbMboxes.MBOX19.MSGID.bit.STDMSGID = 0x580 + LEFT_LEG_MOTOR2_CANID;
	ECanbLAMRegs.LAM19.bit.LAMI = 1;
	ECanbLAMRegs.LAM19.bit.LAM_H = (0x000)<<2;

	//MBOX20 receive 0x583 SDO3
	ECanbMboxes.MBOX20.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX20.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX20.MSGID.bit.IDE = 0;
	ECanbMboxes.MBOX20.MSGID.bit.STDMSGID = 0x580 + RIGHT_LEG_MOTOR1_CANID;
	ECanbLAMRegs.LAM20.bit.LAMI = 1;
	ECanbLAMRegs.LAM20.bit.LAM_H = (0x000)<<2;

	//MBOX21 receive 0x584 SDO4
	ECanbMboxes.MBOX21.MSGID.bit.AME = 1;
	ECanbMboxes.MBOX21.MSGID.bit.AAM = 0;
	ECanbMboxes.MBOX21.MSGID.bit.IDE = 0;
	ECanbMboxes.MBOX21.MSGID.bit.STDMSGID = 0x580 + RIGHT_LEG_MOTOR2_CANID;
	ECanbLAMRegs.LAM21.bit.LAMI = 1;
	ECanbLAMRegs.LAM21.bit.LAM_H = (0x000)<<2;

	//	//MBOX22 receive 0x583 SDO
	//	ECanbMboxes.MBOX22.MSGID.bit.AME = 1;
	//	ECanbMboxes.MBOX22.MSGID.bit.AAM = 0;
	//	ECanbMboxes.MBOX22.MSGID.bit.IDE = 0;
	//    ECanbMboxes.MBOX22.MSGID.bit.STDMSGID = 0x583;
	//	ECanbLAMRegs.LAM22.bit.LAMI = 1;
	//	ECanbLAMRegs.LAM22.bit.LAM_H= (0x000)<<2;
	//
	//	//MBOX23 receive 0x700 heartbeat
	//	ECanbMboxes.MBOX23.MSGID.bit.AME = 1;
	//	ECanbMboxes.MBOX23.MSGID.bit.AAM = 0;
	//	ECanbMboxes.MBOX23.MSGID.bit.IDE = 0;
	//    ECanbMboxes.MBOX23.MSGID.bit.STDMSGID = 0x700;
	//	ECanbLAMRegs.LAM23.bit.LAMI = 1;
	//	ECanbLAMRegs.LAM23.bit.LAM_H= (0x07F)<<2;
	//
	//	//MBOX24 receive 0x7FF test
	//	ECanbMboxes.MBOX23.MSGID.bit.AME = 1;
	//	ECanbMboxes.MBOX23.MSGID.bit.AAM = 0;
	//	ECanbMboxes.MBOX23.MSGID.bit.IDE = 0;
	//    ECanbMboxes.MBOX23.MSGID.bit.STDMSGID = 0x7ff;
	//	ECanbLAMRegs.LAM23.bit.LAMI = 1;
	//	ECanbLAMRegs.LAM23.bit.LAM_H= (0x000)<<2;

	/*
	 *	CANMC	主控制寄存器：
	 *			DBO：	数据字节顺序。
	 *					1. 首先接收或传输数据的低位
	 *					0. 首先接收或传输数据的高位
	 *			SCB：	SCC 兼容性位
	 *					1. eCan 模式
	 *			ABO：	自动总线打开
	 *					1. 自动总线打开
	 *			STM：	自检测模式
	 *					0. 该模块处于正常模式
	 *
	 *	CANMD	邮箱方向寄存器：
	 *			CANMD:
	 *					1. 接收
	 *					0. 发送
	 *
	 *	CANME	邮箱使能寄存器：
	 *			CANME：
	 *					1. 使能
	 *					0. 关闭
	 */
	ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
	ECanbShadow.CANMC.bit.DBO = 0;
	ECanbShadow.CANMC.bit.SCB = 1;//Select eCAN mode
	ECanbShadow.CANMC.bit.ABO = 1;
	ECanbShadow.CANMC.bit.STM = 0;
	ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;
	// Configure  Mailbox Direction: MBOX0-15 as Tx, MBOX16-31 as Rx
	ECanbRegs.CANMD.all = 0xFFFF0000;
	// Enable all Mailboxes */
	ECanbRegs.CANME.all = 0x01FFFFFF;
	EDIS;
}

/**
 *	函数说明：	CAN 中断初始化
 *
 *	函数描述：	该函数只使能了 CAN 邮箱的接收中断，没有使能发送中断。
 *				如果要使能发哦是那个中断：
 *					1. 设置 CANMIL 寄存器，设置中断的配置线路 0 or 1
 *					2. 设置 CANMIM 寄存器，使能中断
 */
void InitCanInterrupt(void)
{
	struct ECAN_REGS ECanbShadow;

	EALLOW;
	PieVectTable.ECAN1INTB = &CanReceiveInterrupt;
	EDIS;

	EALLOW;     // EALLOW enables access to protected bits
	ECanbRegs.CANMIL.all = 0xFFFF0000;  	// mailbox receive interrupts to line 1
	ECanbRegs.CANMIM.all = 0xFFFF0000; 		// Mailbox receive interrupt is enabled.

	ECanbShadow.CANGIM.all = ECanbRegs.CANGIM.all;
	ECanbShadow.CANGIM.bit.GIL=1;
	ECanbShadow.CANGIM.bit.I1EN=1;
	ECanbRegs.CANGIM.all = ECanbShadow.CANGIM.all;

	ECanbRegs.CANTA.all = 0xFFFFFFFF;   /* Clear all TAn bits */
	ECanbRegs.CANRMP.all = 0xFFFFFFFF;  /* Clear all RMPn bits */
	ECanbRegs.CANGIF0.all = 0xFFFFFFFF; /* Clear all interrupt flag bits */
	ECanbRegs.CANGIF1.all = 0xFFFFFFFF;

	PieCtrlRegs.PIEIER9.bit.INTx8 = 1;      // Enable INT 9.8 in the PIE : line1
	IER |= M_INT9;                          // Enable CPU Interrupt 9

	EDIS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CAN 中断函数 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Uint16 NowMailBox=0;
Uint16 NextMailBox=0;

/*********************************
 *
 *	函数说明：	CAN 发送消息函数
 *
 *	说明：		需要注意这里的发送是逆序的，
 *				比如：如果需要同时给多个目标ID发送数据，
 *				会先将数据存储到 MailBox 中，
 *				当要发送的时候，会依次逆序发送出去
 *
 *********************************/
UNS8 canSend(Message *m)
{
	Uint32 CANTaFlag;
	volatile struct MBOX *Mailbox;
	struct ECAN_REGS ECanbShadow;

	CANTaFlag	= (1 << NowMailBox) & 0xFFFF;
	Mailbox 	= &ECanbMboxes.MBOX0 + NowMailBox;
	NextMailBox	= NowMailBox+1;
	if(NextMailBox == 16) {
		NextMailBox = 0;
	}
	NowMailBox++;
	if(NowMailBox == 16) {
		NowMailBox = 0;
	}

	// 指定接收邮箱 ID，先关闭 ME，再配置 ID
	EALLOW;
	//---------------------------- 配置接收 ID 开始 --------------------------------------
	ECanbShadow.CANME.all = ECanbRegs.CANME.all;
	ECanbShadow.CANME.all &= ~CANTaFlag;
	ECanbRegs.CANME.all = ECanbShadow.CANME.all;

	Mailbox->MSGID.bit.STDMSGID = m->cob_id;
	Mailbox->MSGCTRL.bit.DLC = m->len;
	Mailbox->MSGCTRL.bit.RTR = m->rtr;

	ECanbShadow.CANME.all = ECanbRegs.CANME.all;
	ECanbShadow.CANME.all |= CANTaFlag;
	ECanbRegs.CANME.all = ECanbShadow.CANME.all;
	//---------------------------- 配置接收 ID 结束 --------------------------------------

	// 装入数据
	Mailbox->MDL.byte.BYTE0=m->data[0];
	Mailbox->MDL.byte.BYTE1=m->data[1];
	Mailbox->MDL.byte.BYTE2=m->data[2];
	Mailbox->MDL.byte.BYTE3=m->data[3];
	Mailbox->MDH.byte.BYTE4=m->data[4];
	Mailbox->MDH.byte.BYTE5=m->data[5];
	Mailbox->MDH.byte.BYTE6=m->data[6];
	Mailbox->MDH.byte.BYTE7=m->data[7];

	// 使能发送
	ECanbShadow.CANTRS.all=ECanbRegs.CANTRS.all;
	ECanbShadow.CANTRS.all |=CANTaFlag;
	ECanbRegs.CANTRS.all=ECanbShadow.CANTRS.all;

	// NextMailBox 邮箱清空
	ECanbShadow.CANTA.all 	= 	0;
	ECanbShadow.CANTA.all 	|= 	(Uint32)((1<<NextMailBox) & 0xFFFF);
	ECanbRegs.CANTA.all 	= 	ECanbShadow.CANTA.all;
	EDIS;

	return 0x00;
}

/**
 *	函数说明：	测试 CAN 发送功能
 *
 *	函数描述：	在 Timer1Tick 中使用该方法进行发送功能测试，
 *				测试人：		陈鑫
 *				测试时间：	2016-10-25
 *				测试情况：	发送成功
 */
#define CAN_SEND_TEST	0
void testCanSend(void) {

#if CAN_SEND_TEST
	Message message;
	message.cob_id = 0x0;
	message.data[0] = 0x02;
	message.data[1] = 0x00;
	message.data[2] = 0x00;
	message.data[3] = 0x00;
	message.data[4] = 0x00;
	message.data[5] = 0x00;
	message.data[6] = 0x00;
	message.data[7] = 0x00;
	message.len = 2;
	message.rtr = 0;

	canSend(&message);
#endif
}

/*********************************
 *
 *	函数说明：	CAN 接收消息函数
 *
 *	函数描述：	在 CANfestival 中默认是使用结构体直接传值，
 *				但是经过查看内存测试发现，CAN 外设收到了数据，
 *				并将数据存储在了 CANMailBox 中，传值却传不过来，
 *				改用指针方式后，该问题解决
 *
 *********************************/
UNS8 canReceive(Message *m)
{
	int i;
	//	struct MBOX tempMBOXES;
	//
	//	if(ECanbRegs.CANRMP.bit.RMP16)
	//		{tempMBOXES=ECanbMboxes.MBOX16;ECanbRegs.CANRMP.bit.RMP16=1;}
	//	else if(ECanbRegs.CANRMP.bit.RMP17)
	//		{tempMBOXES=ECanbMboxes.MBOX17;ECanbRegs.CANRMP.bit.RMP17=1;}
	//	else if(ECanbRegs.CANRMP.bit.RMP18)
	//		{tempMBOXES=ECanbMboxes.MBOX18;ECanbRegs.CANRMP.bit.RMP18=1;}
	//	else if(ECanbRegs.CANRMP.bit.RMP19)
	//		{tempMBOXES=ECanbMboxes.MBOX19;ECanbRegs.CANRMP.bit.RMP19=1;}
	//	else if(ECanbRegs.CANRMP.bit.RMP20)
	//		{tempMBOXES=ECanbMboxes.MBOX20;ECanbRegs.CANRMP.bit.RMP20=1;}
	//	else if(ECanbRegs.CANRMP.bit.RMP21)
	//		{tempMBOXES=ECanbMboxes.MBOX21;ECanbRegs.CANRMP.bit.RMP21=1;}
	//	else if(ECanbRegs.CANRMP.bit.RMP22)
	//		{tempMBOXES=ECanbMboxes.MBOX22;ECanbRegs.CANRMP.bit.RMP22=1;}
	//	else if(ECanbRegs.CANRMP.bit.RMP23)
	//		{tempMBOXES=ECanbMboxes.MBOX23;ECanbRegs.CANRMP.bit.RMP23=1;}
	//	else if(ECanbRegs.CANRMP.bit.RMP24)
	//		{tempMBOXES=ECanbMboxes.MBOX24;ECanbRegs.CANRMP.bit.RMP24=1;}
	//
	//	m->rtr=tempMBOXES.MSGCTRL.bit.RTR;
	//	m->len=tempMBOXES.MSGCTRL.bit.DLC;
	//	m->cob_id=tempMBOXES.MSGID.bit.STDMSGID;
	//	m->data[0]=tempMBOXES.MDL.byte.BYTE0;
	//	m->data[1]=tempMBOXES.MDL.byte.BYTE1;
	//	m->data[2]=tempMBOXES.MDL.byte.BYTE2;
	//	m->data[3]=tempMBOXES.MDL.byte.BYTE3;
	//	m->data[4]=tempMBOXES.MDH.byte.BYTE4;
	//	m->data[5]=tempMBOXES.MDH.byte.BYTE5;
	//	m->data[6]=tempMBOXES.MDH.byte.BYTE6;
	//	m->data[7]=tempMBOXES.MDH.byte.BYTE7;

	volatile struct MBOX * tempMBOXES;

	if(ECanbRegs.CANRMP.bit.RMP16)
	{tempMBOXES=&ECanbMboxes.MBOX16;ECanbRegs.CANRMP.bit.RMP16=1;}
	else if(ECanbRegs.CANRMP.bit.RMP17)
	{tempMBOXES=&ECanbMboxes.MBOX17;ECanbRegs.CANRMP.bit.RMP17=1;}
	else if(ECanbRegs.CANRMP.bit.RMP18)
	{tempMBOXES=&ECanbMboxes.MBOX18;ECanbRegs.CANRMP.bit.RMP18=1;}
	else if(ECanbRegs.CANRMP.bit.RMP19)
	{tempMBOXES=&ECanbMboxes.MBOX19;ECanbRegs.CANRMP.bit.RMP19=1;}
	else if(ECanbRegs.CANRMP.bit.RMP20)
	{tempMBOXES=&ECanbMboxes.MBOX20;ECanbRegs.CANRMP.bit.RMP20=1;}
	else if(ECanbRegs.CANRMP.bit.RMP21)
	{tempMBOXES=&ECanbMboxes.MBOX21;ECanbRegs.CANRMP.bit.RMP21=1;}

	m->rtr=tempMBOXES->MSGCTRL.bit.RTR;
	m->len=tempMBOXES->MSGCTRL.bit.DLC;
	m->cob_id=tempMBOXES->MSGID.bit.STDMSGID;
	m->data[0]=tempMBOXES->MDL.byte.BYTE0;
	m->data[1]=tempMBOXES->MDL.byte.BYTE1;
	m->data[2]=tempMBOXES->MDL.byte.BYTE2;
	m->data[3]=tempMBOXES->MDL.byte.BYTE3;
	m->data[4]=tempMBOXES->MDH.byte.BYTE4;
	m->data[5]=tempMBOXES->MDH.byte.BYTE5;
	m->data[6]=tempMBOXES->MDH.byte.BYTE6;
	m->data[7]=tempMBOXES->MDH.byte.BYTE7;

	i = m->len;
	for(;i<8;i++) {
		m->data[i]=0;
	}

	return TRUE;
}

/**
 *	函数说明：	等待接收指定 id 的 SDO 消息
 *
 *	@return 	TRUE 	接收消息成功
 *				FALSE	接收消息失败
 */
static unsigned int MaxWaitCount = 1000;

UNS8 canReceiveSDO(int canID, Message *m) {

	int i = 0;
	int waitCount = 0;
	volatile struct MBOX * tempMBOXES;

	switch(canID) {
	case LEFT_LEG_MOTOR1_CANID:
		while(!ECanbRegs.CANRMP.bit.RMP18) {
			waitCount++;
			if (waitCount >= MaxWaitCount)
				return FALSE;
		}
		tempMBOXES=&ECanbMboxes.MBOX18;
		ECanbRegs.CANRMP.bit.RMP18=1;
		break;
	case LEFT_LEG_MOTOR2_CANID:
		while(!ECanbRegs.CANRMP.bit.RMP19) {
			waitCount++;
			if (waitCount >= MaxWaitCount)
				return FALSE;
		}
		tempMBOXES=&ECanbMboxes.MBOX19;
		ECanbRegs.CANRMP.bit.RMP19=1;
		break;
	case RIGHT_LEG_MOTOR1_CANID:
		while(!ECanbRegs.CANRMP.bit.RMP20) {
			waitCount++;
			if (waitCount >= MaxWaitCount)
				return FALSE;
		}
		tempMBOXES=&ECanbMboxes.MBOX20;
		ECanbRegs.CANRMP.bit.RMP20=1;
		break;
	case RIGHT_LEG_MOTOR2_CANID:
		while(!ECanbRegs.CANRMP.bit.RMP21) {
			waitCount++;
			if (waitCount >= MaxWaitCount)
				return FALSE;
		}
		tempMBOXES=&ECanbMboxes.MBOX21;
		ECanbRegs.CANRMP.bit.RMP21=1;
		break;
	default:
		return FALSE;
	}

	m->rtr=tempMBOXES->MSGCTRL.bit.RTR;
	m->len=tempMBOXES->MSGCTRL.bit.DLC;
	m->cob_id=tempMBOXES->MSGID.bit.STDMSGID;
	m->data[0]=tempMBOXES->MDL.byte.BYTE0;
	m->data[1]=tempMBOXES->MDL.byte.BYTE1;
	m->data[2]=tempMBOXES->MDL.byte.BYTE2;
	m->data[3]=tempMBOXES->MDL.byte.BYTE3;
	m->data[4]=tempMBOXES->MDH.byte.BYTE4;
	m->data[5]=tempMBOXES->MDH.byte.BYTE5;
	m->data[6]=tempMBOXES->MDH.byte.BYTE6;
	m->data[7]=tempMBOXES->MDH.byte.BYTE7;

	i = m->len;
	for(;i<8;i++) {
		m->data[i]=0;
	}

	return TRUE;
}

/*********************************
 *
 *	函数说明：	CAN 接收中断处理函数
 *
 *********************************/
interrupt void CanReceiveInterrupt(void)
{
	struct ECAN_REGS ECanbShadow;

	/**
	 *	PIEIFRn		PIE Interrupt Flag Registers 中断标志寄存器
	 *				INTn.8, INTn.7 ... INTn.1
	 *				中断是否激活状态，通过调用中断服务程序或写0来清楚当前状态
	 *
	 *	PIEIERn		PIE Interrupt Enable Register 中断使能标志位
	 *				INTn.8, INTn.7 ... INTn.1
	 *
	 *	IFR			Interrupt Flag Register		中断标志寄存器
	 *				INT14, INT13, ... INT1
	 *				如果为 1 表示至少有一个触发中断在等待处理
	 *
	 *	IER			Interrupt Enable Register	中断使能寄存器
	 *				INT14, INT13, ... INT1
	 *				中断是否被使能
	 */
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

	EALLOW;
	ECanbShadow.CANGIF1.all = ECanbRegs.CANGIF1.all;
	EDIS;

	// 如果是错误或警告消息
	if((ECanbShadow.CANGIF1.all & 0x00037f00) != 0) {
		// 错误处理代码
		ECanbRegs.CANGIF1.all =	ECanbShadow.CANGIF1.all  & 0x00013700;
		ECanbRegs.CANTOS.all = 0x0000FFFF; //bits17, MTOF
		ECanbRegs.CANAA.all =  0x0000FFFF; //P29 Bit14 AAIF ,If the transmission of the message in mailbox n was aborted, the bit AA[n] is set and the AAIF (GIF.14) bit
		ECanbRegs.CANRMP.all=  0xFFFF0000; //
	}
	// 如果发送成功或接收到一个消息(发送中断未使能, 只能是成功接收到消息)
	else if(ECanbShadow.CANGIF1.bit.GMIF1 == 1) {
		Message m;
		// 接收数据(传入帧指针，执行完毕，帧数据改变)
		if(canReceive(&m)) {
			// CAN 分支处理程序
			canReceiveDispatch(&TestMaster_Data, &m);
		}
	}
}

//void InitNodes(CO_Data* d, UNS32 id)
//{
//	/* init */
//	setState(&TestMaster_Data, Initialisation);
//}
//
//static void StartTimerLoop(TimerCallback_t _init_callback)
//{
//	init_callback = _init_callback;
//	SetAlarm(NULL, 0, init_callback, 0, 0);
//	StartTimer1();
//}

//int test_slave(void)
//{
//	TestSlave_Data.post_sync = TestSlave_post_sync;
//	TestSlave_Data.post_TPDO = TestSlave_post_TPDO;
//
//	// Start timer thread
//
//	DriverState=SwitchedOn;
//	controlword.all|=0x07;
//	StartTimerLoop(&InitNodes);
//	DirverState();
//
//	return 0;
//}

