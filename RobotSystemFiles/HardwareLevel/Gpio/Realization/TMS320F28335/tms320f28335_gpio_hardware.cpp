/*
 * tms320f28335_gpio_hardware.cpp
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#include <RobotSystemFiles/HardwareLevel/Gpio/Realization/TMS320F28335/tms320f28335_gpio_hardware.h>

#ifdef TMS320F28335

int TMS320F28335_Gpio::gpio_init() {

	EALLOW;

	GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;		// check port

	EDIS;
}

int TMS320F28335_Gpio::gpio_set() {

	GpioDataRegs.GPASET.bit.GPIO3 = 1;
}

int TMS320F28335_Gpio::gpio_clear() {

}

int TMS320F28335_Gpio::gpio_read() {

	GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
}

#endif
