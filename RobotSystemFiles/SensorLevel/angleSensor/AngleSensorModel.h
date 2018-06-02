/*
 * AngleSensorModel.h
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_SENSORS_ANGLESENSOR_ANGLESENSORMODEL_H_
#define USERFILES_MODEL_SENSORS_ANGLESENSOR_ANGLESENSORMODEL_H_

#include "CONSTANTS.h"
#include "../sensorInterface/SensorInterfaceModel.h"

struct AngleSensorModel {

	struct SensorInterfaceModel sensorInterfaceModel;

	float direction;
	float bias;
	float init;

	long  rawValue;
	float angleValue;
	float radianValue;
};


void AngleSensorModel_init(
		struct AngleSensorModel * angleSensorModel,
		int boardIndex,
		int portIndex,
		float direction,
		float bias,
		float init);

void AngleSensorModel_copy(
		struct AngleSensorModel * angleSensorModelTo,
		struct AngleSensorModel * angleSensorModelFrom);

void AngleSensorModel_updateValue(
		struct AngleSensorModel * angleSensorModel);

#endif /* USERFILES_MODEL_SENSORS_ANGLESENSOR_ANGLESENSORMODEL_H_ */
