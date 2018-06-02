/*
 * exRam_hardware_interface.h
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#ifndef ROBOTSYSTEMFILES_HARDWARELEVEL_EXRAM_INTERFACE_EXRAM_HARDWARE_INTERFACE_H_
#define ROBOTSYSTEMFILES_HARDWARELEVEL_EXRAM_INTERFACE_EXRAM_HARDWARE_INTERFACE_H_

class ExRamHardwareInterface {

public:
	virtual int	ram_init(unsigned long Start);
	virtual int	ram_erase(unsigned long	Start);
	virtual int	ram_read(unsigned long	Start);
};

#endif /* ROBOTSYSTEMFILES_HARDWARELEVEL_EXRAM_INTERFACE_EXRAM_HARDWARE_INTERFACE_H_ */
