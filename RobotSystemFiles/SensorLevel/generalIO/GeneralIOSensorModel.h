/*
 * GeneralIOSensorModel.h
 *
 *  Created on: 2017年4月7日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_SENSORS_GENERALIO_GENERALIOSENSORMODEL_H_
#define USERFILES_MODEL_SENSORS_GENERALIO_GENERALIOSENSORMODEL_H_

#include "../sensorInterface/SensorInterfaceModel.h"

struct GeneralIOSensorModel {
	struct SensorInterfaceModel sensorInterfaceModel;
	unsigned int ioValue;

	// 防抖处理
	unsigned int middleCount;
	unsigned int firstReadValue;
	unsigned int secondReadValue;
};

void GeneralIOSensorModel_init(
		struct GeneralIOSensorModel * forceSensorModel,
		int boardIndex,
		int portIndex);

void GeneralIOSensorModel_copy(
		struct GeneralIOSensorModel * forceSensorModelTo,
		struct GeneralIOSensorModel * forceSensorModelFrom);

void GeneralIOSensorModel_updateValue(
		struct GeneralIOSensorModel * forceSensorModel);




#endif /* USERFILES_MODEL_SENSORS_GENERALIO_GENERALIOSENSORMODEL_H_ */
