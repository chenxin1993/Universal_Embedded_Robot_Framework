/*
 * CustomizedBusSensorCommunicateProtocol.h
 *
 *  Created on: 2018年6月4日
 *      Author: xin-FFTAI
 */

#ifndef ROBOTSYSTEMFILES_HARDWAREINTERFACE_SENSOR_COMMUNICATE_PROTOCOL_BUS_SENSOR_COMMUNICATE_PROTOCOL_CUSTOMIZED_BUS_SENSOR_COMMUNICATE_PROTOCOL_CUSTOMIZED_BUS_SENSOR_COMMUNICATE_PROTOCOL_H_
#define ROBOTSYSTEMFILES_HARDWAREINTERFACE_SENSOR_COMMUNICATE_PROTOCOL_BUS_SENSOR_COMMUNICATE_PROTOCOL_CUSTOMIZED_BUS_SENSOR_COMMUNICATE_PROTOCOL_CUSTOMIZED_BUS_SENSOR_COMMUNICATE_PROTOCOL_H_

class CustomizedBusSensorCommunicateProtocol : BusSensorCommunicateProtocol {

public:
	int bus_init();
	int bus_update();
	int bus_read(void * data);
};



#endif /* ROBOTSYSTEMFILES_HARDWAREINTERFACE_SENSOR_COMMUNICATE_PROTOCOL_BUS_SENSOR_COMMUNICATE_PROTOCOL_CUSTOMIZED_BUS_SENSOR_COMMUNICATE_PROTOCOL_CUSTOMIZED_BUS_SENSOR_COMMUNICATE_PROTOCOL_H_ */