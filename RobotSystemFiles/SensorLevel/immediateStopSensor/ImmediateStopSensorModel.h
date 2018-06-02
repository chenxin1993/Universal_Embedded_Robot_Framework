/*
 * ImmediateStopSensorModel.h
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_SENSORS_IMMEDIATESTOPSENSOR_IMMEDIATESTOPSENSORMODEL_H_
#define USERFILES_MODEL_SENSORS_IMMEDIATESTOPSENSOR_IMMEDIATESTOPSENSORMODEL_H_

#include "../sensorInterface/SensorInterfaceModel.h"

struct ImmediateStopSensorModel {

	struct SensorInterfaceModel sensorInterfaceModel;

	int value;
};


#endif /* USERFILES_MODEL_SENSORS_IMMEDIATESTOPSENSOR_IMMEDIATESTOPSENSORMODEL_H_ */
