/*
 * SensorInterfaceModel.h
 *
 *  Created on: 2016-5-23
 *      Author: 康复组
 */

#ifndef SENSORINTERFACEMODEL_H_
#define SENSORINTERFACEMODEL_H_

#include "HARDWARE/HARDWARE.h"

struct SensorInterfaceModel {

	unsigned int boardIndex;
	unsigned int portIndex;
	unsigned int value;
};

void SensorInterfaceModel_init(
		struct SensorInterfaceModel * sensorInterfaceModel,
		int boardIndex,
		int portIndex,
		int initValue);

void SensorInterfaceModel_copy(
		struct SensorInterfaceModel * sensorInterfaceModelTo,
		struct SensorInterfaceModel * sensorInterfaceModelFrom);

void SensorInterfaceModel_updateValue(
		struct SensorInterfaceModel * sensorInterfaceModel);

#endif /* SENSORINTERFACEMODEL_H_ */
