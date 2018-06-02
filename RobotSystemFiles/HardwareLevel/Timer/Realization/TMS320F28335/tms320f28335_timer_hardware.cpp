/*
 * tms320f28335_timer_hardware.cpp
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#ifdef TMS320F28335

#include "tms320f28335_timer_hardware.h"

#include "DSP2833x_Device.h"    // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h" 	// DSP2833x Examples Include File
#include "DSP2833x_CpuTimers.h"

int TMS320F28335_Timer::timer_init(unsigned long ms) {

    // Initialize timer0 period:
    CpuTimer0Regs.PRD.all = (long) (150.0 * 1000.0 * ms);

    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    CpuTimer0Regs.TPR.all  = 0;
    CpuTimer0Regs.TPRH.all  = 0;

    // Initialize timer control register:
    CpuTimer0Regs.TCR.bit.TSS = 1;      // 1 = Stop timer, 0 = Start/Restart Timer
    CpuTimer0Regs.TCR.bit.TRB = 1;      // 1 = reload timer
    CpuTimer0Regs.TCR.bit.SOFT = 1;
    CpuTimer0Regs.TCR.bit.FREE = 1;     // Timer Free Run
    CpuTimer0Regs.TCR.bit.TIE = 1;      // 0 = Disable/ 1 = Enable Timer Interrupt

    CpuTimer0.InterruptCount = 0;

    // Enable INT1 interrupt
	IER |= M_INT1;

	// Enable TINT0 interrupt in group 1
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

}

int TMS320F28335_Timer::timer_init(unsigned long ms, void * handle) {

    // Initialize timer0 period:
    CpuTimer0Regs.PRD.all = (long) (150.0 * 1000.0 * ms);

    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    CpuTimer0Regs.TPR.all  = 0;
    CpuTimer0Regs.TPRH.all  = 0;

    // Initialize timer control register:
    CpuTimer0Regs.TCR.bit.TSS = 1;      // 1 = Stop timer, 0 = Start/Restart Timer
    CpuTimer0Regs.TCR.bit.TRB = 1;      // 1 = reload timer
    CpuTimer0Regs.TCR.bit.SOFT = 1;
    CpuTimer0Regs.TCR.bit.FREE = 1;     // Timer Free Run
    CpuTimer0Regs.TCR.bit.TIE = 1;      // 0 = Disable/ 1 = Enable Timer Interrupt

    CpuTimer0.InterruptCount = 0;

    // Enable INT1 interrupt
	IER |= M_INT1;

	// Enable TINT0 interrupt in group 1
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

	// Set handle
	EALLOW;
	PieVectTable.TINT0 = &handle;
	EDIS;
}

int TMS320F28335_Timer::timer_set_handle(void * handle) {

}

int TMS320F28335_Timer::timer_set_period(unsigned long ms) {

}

int TMS320F28335_Timer::timer_start(void) {

	CpuTimer0Regs.TCR.bit.TRB = 1;      // 1 = reload timer
	CpuTimer0Regs.TCR.bit.TSS = 0;
}

int TMS320F28335_Timer::timer_stop(void) {

	CpuTimer0Regs.TCR.bit.TSS = 1;
}

#endif
