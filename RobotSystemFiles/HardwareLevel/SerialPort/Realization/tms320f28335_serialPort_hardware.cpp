/*
 * tms320f28335_serialPort_hardware.cpp
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#include <RobotSystemFiles/HardwareLevel/SerialPort/Realization/tms320f28335_serialPort_hardware.h>

#ifdef TMS320F28335

#include "DSP2833x_Device.h"    // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h" 	// DSP2833x Examples Include File


void TMS320F28335_SerialPort::serialPort_init(void) {

	SciaRegs.SCICCR.all = 0x0007;   			// 1 stop bit,  No loopback
												// No parity,8 char bits,
												// async mode, idle-line protocol
	SciaRegs.SCICTL1.all = 0x0003;				// enable TX, RX, internal SCICLK,
												// Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.all =  0x0003;
	SciaRegs.SCICTL2.bit.TXINTENA = 1;			// ���÷����жϣ��ȴ���Ҫ�������ʱ���������ж�

	#if (CPU_FRQ_150MHZ)
		SciaRegs.SCIHBAUD = 0x0000;
		SciaRegs.SCILBAUD = 0x0027; 			// 115200 baud @LSPCLK = 37.5MHz.
	#endif
	#if (CPU_FRQ_100MHZ)
		SciaRegs.SCIHBAUD = 0x0000;  			// 115200 baud @LSPCLK = 20MHz.
		SciaRegs.SCILBAUD = 0x0014;
	#endif

	SciaRegs.SCICTL1.all = 0x0023;  			// Relinquish SCI from Reset
}


void TMS320F28335_SerialPort::serialPort_fifo_init(void) {

	int i;
	for(i = 0; i < SCIA_RCV_BUF_SIZE; i++) {
		SciaRcvBuf[i] = 0;
	}
	for (i = 0; i < SCIA_XMT_BUF_SIZE; ++i) {
		SciaXmtBuf[i] = 0;
	}

	SciaRegs.SCIFFTX.all = 0x5060;
	SciaRegs.SCIFFRX.all = 0x50E1;
	SciaRegs.SCIFFCT.all = 0x0;

	SciaRegs.SCIFFTX.bit.TXFFIENA = 0;
	SciaRegs.SCIFFTX.bit.SCIRST = 1;
	SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;

	EALLOW;  // This is needed to write to EALLOW protected registers

	// 配置传输中断
	PieVectTable.SCIRXINTA = &ISRSciaRx;
	PieVectTable.SCITXINTA = &ISRSciaTx;
	EDIS;    // This is needed to disable write to EALLOW protected registers

    // SCIRXINTA ��Ӧ INT9.1
	// SCITXINTA ��Ӧ INT9.2
    IER |= M_INT9;
	PieCtrlRegs.PIEIER9.bit.INTx1 = 1;
	PieCtrlRegs.PIEIER9.bit.INTx2 = 1;
}

#endif
