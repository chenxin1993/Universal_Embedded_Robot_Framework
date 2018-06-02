/*
 * can_hardware_interface.h
 *
 *  Created on: 2018年5月31日
 *      Author: xin-FFTAI
 */

#ifndef ROBOTSYSTEMFILES_HARDWARELEVEL_CAN_INTERFACE_CAN_HARDWARE_INTERFACE_H_
#define ROBOTSYSTEMFILES_HARDWARELEVEL_CAN_INTERFACE_CAN_HARDWARE_INTERFACE_H_

class CanHardwareInterface {

public:
	virtual int can_init(void);
	virtual int can_send(unsigned char data);
};


#endif /* ROBOTSYSTEMFILES_HARDWARELEVEL_CAN_INTERFACE_CAN_HARDWARE_INTERFACE_H_ */
