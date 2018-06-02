/*
 * tms320f28335_serialPort_hardware.h
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#ifndef ROBOTSYSTEMFILES_HARDWARELEVEL_SERIALPORT_REALIZATION_TMS320F28335_SERIALPORT_HARDWARE_H_
#define ROBOTSYSTEMFILES_HARDWARELEVEL_SERIALPORT_REALIZATION_TMS320F28335_SERIALPORT_HARDWARE_H_

#ifdef TMS320F28335

class TMS320F28335_SerialPort : SerialPortHardwareInterface {

	unsigned int SciaXmtBuf[1024];
	unsigned int SciaRcvBuf[1024];

public:
	void serialPort_init(void);
	void serialPort_fifo_init(void);
};

#endif

#endif /* ROBOTSYSTEMFILES_HARDWARELEVEL_SERIALPORT_REALIZATION_TMS320F28335_SERIALPORT_HARDWARE_H_ */
