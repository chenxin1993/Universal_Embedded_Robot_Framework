/*
 * tms320f28335_timer_hardware.h
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#ifndef USERFILES_HARDWARELEVEL_TIMER_REALIZATION_TMS320F28335_TIMER_HARDWARE_H_
#define USERFILES_HARDWARELEVEL_TIMER_REALIZATION_TMS320F28335_TIMER_HARDWARE_H_

#ifdef TMS320F28335

class TMS320F28335_Timer : TimerHardwareInterface {

public:
	int timer_init(unsigned long ms);
	int timer_init(unsigned long ms, void * handle);
	int timer_set_handle(void * handle);
	int timer_set_period(unsigned long ms);
	int timer_start(void);
	int timer_stop(void);
};

#endif

#endif /* USERFILES_HARDWARELEVEL_TIMER_REALIZATION_TMS320F28335_TIMER_HARDWARE_H_ */
