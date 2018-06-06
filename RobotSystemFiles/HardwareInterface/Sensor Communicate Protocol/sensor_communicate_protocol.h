/*
 * SensorCommunicateProtocol.h
 *
 *  Created on: 2018年6月2日
 *      Author: xin-FFTAI
 */

#ifndef ROBOTSYSTEMFILES_HARDWAREINTERFACE_SENSOR_COMMUNICATE_PROTOCOL_SENSOR_COMMUNICATE_PROTOCOL_H_
#define ROBOTSYSTEMFILES_HARDWAREINTERFACE_SENSOR_COMMUNICATE_PROTOCOL_SENSOR_COMMUNICATE_PROTOCOL_H_

class SensorCommunicateProtocol {

public:
	virtual int sensor_init() = 0;
	virtual int sensor_update() = 0;
	virtual int sensor_read(void * data) = 0;
};

#endif /* ROBOTSYSTEMFILES_HARDWAREINTERFACE_SENSOR_COMMUNICATE_PROTOCOL_SENSOR_COMMUNICATE_PROTOCOL_H_ */
