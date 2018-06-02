/*
 * gpio_hardware_interface.h
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#ifndef ROBOTSYSTEMFILES_HARDWARELEVEL_GPIO_INTERFACE_GPIO_HARDWARE_INTERFACE_H_
#define ROBOTSYSTEMFILES_HARDWARELEVEL_GPIO_INTERFACE_GPIO_HARDWARE_INTERFACE_H_

class GpioHardwareInterface {

public:
	virtual int gpio_init() = 0;
	virtual int gpio_set() = 0;
	virtual int gpio_clear() = 0;
	virtual int gpio_read() = 0;
};



#endif /* ROBOTSYSTEMFILES_HARDWARELEVEL_GPIO_INTERFACE_GPIO_HARDWARE_INTERFACE_H_ */
