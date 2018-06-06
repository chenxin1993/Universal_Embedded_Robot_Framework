/*
 * forceSensorModel.h
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_FORCESENSOR_FORCESENSORMODEL_H_
#define USERFILES_MODEL_FORCESENSOR_FORCESENSORMODEL_H_

#include "../../HardwareInterface/Sensor Communicate Protocol/sensor_communicate_protocol.h"
#include "../sensor_model.h"

class ForceSensorModel : public SensorModel {

public:
	class SensorCommunicateProtocol * sensorCommunicateProtocol;

	float gValue;

	int init();
	int read(void * data);
	int write(void * data);
	int update();
};

#endif /* USERFILES_MODEL_FORCESENSOR_FORCESENSORMODEL_H_ */
