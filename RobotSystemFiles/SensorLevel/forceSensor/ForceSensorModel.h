/*
 * forceSensorModel.h
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_FORCESENSOR_FORCESENSORMODEL_H_
#define USERFILES_MODEL_FORCESENSOR_FORCESENSORMODEL_H_

#include "../sensorInterface/SensorInterfaceModel.h"

struct ForceSensorModel {
	struct SensorInterfaceModel sensorInterfaceModel;
	float gValue;
};

void ForceSensorModel_init(
		struct ForceSensorModel * forceSensorModel,
		int boardIndex,
		int portIndex);

void ForceSensorModel_copy(
		struct ForceSensorModel * forceSensorModelTo,
		struct ForceSensorModel * forceSensorModelFrom);

void ForceSensorModel_updateValue(
		struct ForceSensorModel * forceSensorModel);


#endif /* USERFILES_MODEL_FORCESENSOR_FORCESENSORMODEL_H_ */
