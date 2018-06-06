/*
 * BusSensorCommunicateProtocol.h
 *
 *  Created on: 2018年6月4日
 *      Author: xin-FFTAI
 */

#ifndef ROBOTSYSTEMFILES_HARDWAREINTERFACE_SENSOR_COMMUNICATE_PROTOCOL_BUS_SENSOR_COMMUNICATE_PROTOCOL_BUS_SENSOR_COMMUNICATE_PROTOCOL_H_
#define ROBOTSYSTEMFILES_HARDWAREINTERFACE_SENSOR_COMMUNICATE_PROTOCOL_BUS_SENSOR_COMMUNICATE_PROTOCOL_BUS_SENSOR_COMMUNICATE_PROTOCOL_H_

#include "../sensor_communicate_protocol.h"

class BusSensorCommunicateProtocol : public SensorCommunicateProtocol {

public:

	// from SensorCommunicateProtocol
	int sensor_init();
	int sensor_update();
	int sensor_read(void * data);

	// from Self
	virtual int bus_init() = 0;
	virtual int bus_update() = 0;
	virtual int bus_read(void * data) = 0;

};


#endif /* ROBOTSYSTEMFILES_HARDWAREINTERFACE_SENSOR_COMMUNICATE_PROTOCOL_BUS_SENSOR_COMMUNICATE_PROTOCOL_BUS_SENSOR_COMMUNICATE_PROTOCOL_H_ */
