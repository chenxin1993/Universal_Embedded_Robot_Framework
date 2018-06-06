/*
 * angle_sensor_model.h
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_SENSORS_ANGLESENSOR_ANGLESENSORMODEL_H_
#define USERFILES_MODEL_SENSORS_ANGLESENSOR_ANGLESENSORMODEL_H_

#include "../../HardwareInterface/Sensor Communicate Protocol/sensor_communicate_protocol.h"
#include "../sensor_model.h"

class AngleSensorModel : public SensorModel {

public:
	class SensorCommunicateProtocol * sensorCommunicateProtocol; // notice: object of abstract class is not allowed

	float direction;

	float biasValue;
	float initValue;

	long  rawValue;
	float angleValue;
	float radianValue;

	int init();
	int read(void * data);
	int write(void * data);
	int update();

};

#endif /* USERFILES_MODEL_SENSORS_ANGLESENSOR_ANGLESENSORMODEL_H_ */
