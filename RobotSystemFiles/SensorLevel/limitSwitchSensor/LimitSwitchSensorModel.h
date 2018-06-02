/*
 * LimitSwitchSensorModel.h
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_SENSORS_LIMITSWITCHSENSOR_LIMITSWITCHSENSORMODEL_H_
#define USERFILES_MODEL_SENSORS_LIMITSWITCHSENSOR_LIMITSWITCHSENSORMODEL_H_

#include "../sensorInterface/SensorInterfaceModel.h"

struct LimitSwitchSensorModel {

	struct SensorInterfaceModel sensorInterfaceModel;

	int value;
};



#endif /* USERFILES_MODEL_SENSORS_LIMITSWITCHSENSOR_LIMITSWITCHSENSORMODEL_H_ */
