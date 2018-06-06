/*
 * GpioSensorModel.h
 *
 *  Created on: 2017年4月7日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_SENSORS_GENERALIO_GENERALIOSENSORMODEL_H_
#define USERFILES_MODEL_SENSORS_GENERALIO_GENERALIOSENSORMODEL_H_

#include "../../HardwareInterface/Sensor Communicate Protocol/sensor_communicate_protocol.h"
#include "../sensor_model.h"

class GpioSensorModel : public SensorModel {

public:
	class SensorCommunicateProtocol * sensorCommunicateProtocol;

	unsigned int ioValue;

	// 防抖处理
	unsigned int middleCount;
	unsigned int firstReadValue;
	unsigned int secondReadValue;

	int init();
	int read(void * data);
	int write(void * data);
	int update();
};


#endif /* USERFILES_MODEL_SENSORS_GENERALIO_GENERALIOSENSORMODEL_H_ */
