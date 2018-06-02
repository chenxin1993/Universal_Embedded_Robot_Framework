/*
 * tms320f28335_can_hardware.h
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#ifndef USERFILES_HARDWARELEVEL_CAN_REALIZATION_TMS320F28335_CAN_HARDWARE_H_
#define USERFILES_HARDWARELEVEL_CAN_REALIZATION_TMS320F28335_CAN_HARDWARE_H_

#ifdef TMS320F28335

class TMS320F28335Hardware_Can : CanHardwareInterface {

public:
	int can_init(void);
	int can_send(unsigned char data);
};

#endif

#endif /* USERFILES_HARDWARELEVEL_CAN_REALIZATION_TMS320F28335_CAN_HARDWARE_H_ */
