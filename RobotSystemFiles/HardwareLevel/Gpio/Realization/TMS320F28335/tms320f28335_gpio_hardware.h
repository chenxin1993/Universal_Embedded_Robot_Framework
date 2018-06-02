/*
 * tms320f28335_gpio_hardware.h
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#ifndef USERFILES_HARDWARELEVEL_GPIO_REALIZATION_TMS320F28335_GPIO_HARDWARE_H_
#define USERFILES_HARDWARELEVEL_GPIO_REALIZATION_TMS320F28335_GPIO_HARDWARE_H_

#ifdef TMS320F28335

class TMS320F28335_Gpio : GpioHardwareInterface {

public:
	int gpio_init();
	int gpio_set();
	int gpio_clear();
	int gpio_read();
};

#endif

#endif /* USERFILES_HARDWARELEVEL_GPIO_REALIZATION_TMS320F28335_GPIO_HARDWARE_H_ */
