/*
 * forceSensorModel.c
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#include <RobotSystemFiles/SensorLevel/forceSensor/ForceSensorModel.h>
#include "math.h"

/********************************************
 *
 * 	函数说明：力传感器数据模型初始化
 *
 ********************************************/
void ForceSensorModel_init(
		struct ForceSensorModel * forceSensorModel,
		int boardIndex,
		int portIndex) {

	forceSensorModel->sensorInterfaceModel.boardIndex 	= boardIndex;
	forceSensorModel->sensorInterfaceModel.portIndex 	= boardIndex;
}

/********************************************
 *
 * 	函数说明：力传感器数据模型参数拷贝
 *
 ********************************************/
void ForceSensorModel_copy(
		struct ForceSensorModel * forceSensorModelTo,
		struct ForceSensorModel * forceSensorModelFrom) {

	SensorInterfaceModel_copy(
			&forceSensorModelTo->sensorInterfaceModel,
			&forceSensorModelFrom->sensorInterfaceModel);
}

/********************************************
 *
 * 	函数说明：力传感器数据模型值更新
 *
 ********************************************/
void ForceSensorModel_updateValue(
		struct ForceSensorModel * forceSensorModel) {

	SensorInterfaceModel_updateValue(&forceSensorModel->sensorInterfaceModel);

	forceSensorModel->gValue = 67440 * exp(-0.0808 	* forceSensorModel->sensorInterfaceModel.value) + 10470 * exp(-0.01835 	* forceSensorModel->sensorInterfaceModel.value);
}
