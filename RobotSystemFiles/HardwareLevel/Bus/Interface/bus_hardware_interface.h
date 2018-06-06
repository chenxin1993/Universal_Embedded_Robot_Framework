/*
 * bus_hardware_interface.h
 *
 *  Created on: 2018年6月2日
 *      Author: xin-FFTAI
 */

#ifndef ROBOTSYSTEMFILES_HARDWARELEVEL_BUS_INTERFACE_BUS_HARDWARE_INTERFACE_H_
#define ROBOTSYSTEMFILES_HARDWARELEVEL_BUS_INTERFACE_BUS_HARDWARE_INTERFACE_H_

class BusHardwareInterface {

public:
	virtual int bus_init(void);
	virtual int bus_send(unsigned char data);
};

#endif /* ROBOTSYSTEMFILES_HARDWARELEVEL_BUS_INTERFACE_BUS_HARDWARE_INTERFACE_H_ */
