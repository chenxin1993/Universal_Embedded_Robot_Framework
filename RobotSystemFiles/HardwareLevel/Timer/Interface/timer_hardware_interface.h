/*
 * timer_hardware_interface.h
 *
 *  Created on: 2018年5月31日
 *      Author: xin-FFTAI
 */

#ifndef ROBOTSYSTEMFILES_HARDWARELEVEL_TIMER_INTERFACE_TIMER_HARDWARE_INTERFACE_H_
#define ROBOTSYSTEMFILES_HARDWARELEVEL_TIMER_INTERFACE_TIMER_HARDWARE_INTERFACE_H_

class TimerHardwareInterface {

public:
	virtual int timer_init(unsigned long ms) = 0;
	virtual int timer_init(unsigned long ms, void * handle) = 0;
	virtual int timer_set_handle(void * handle) = 0;
	virtual int timer_set_period(unsigned long ms) = 0;
	virtual int timer_start() = 0;
	virtual int timer_stop() = 0;
};



#endif /* ROBOTSYSTEMFILES_HARDWARELEVEL_TIMER_INTERFACE_TIMER_HARDWARE_INTERFACE_H_ */
