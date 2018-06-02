/*
 * GeneralIOSensorModel.c
 *
 *  Created on: 2017年4月7日
 *      Author: xin
 */

#include <RobotSystemFiles/SensorLevel/generalIO/GeneralIOSensorModel.h>
#include "math.h"

/********************************************
 *
 * 	函数说明：力传感器数据模型初始化
 *
 ********************************************/
void GeneralIOSensorModel_init(
		struct GeneralIOSensorModel * generalIOSensorModel,
		int boardIndex,
		int portIndex) {

	generalIOSensorModel->sensorInterfaceModel.boardIndex 	= boardIndex;
	generalIOSensorModel->sensorInterfaceModel.portIndex 	= boardIndex;
}

/********************************************
 *
 * 	函数说明：力传感器数据模型参数拷贝
 *
 ********************************************/
void GeneralIOSensorModel_copy(
		struct GeneralIOSensorModel * generalIOSensorModelTo,
		struct GeneralIOSensorModel * generalIOSensorModelFrom) {

	SensorInterfaceModel_copy(
			&generalIOSensorModelTo->sensorInterfaceModel,
			&generalIOSensorModelFrom->sensorInterfaceModel);
}

/********************************************
 *
 * 	函数说明：力传感器数据模型值更新
 *
 ********************************************/
void GeneralIOSensorModel_updateValue(
		struct GeneralIOSensorModel * generalIOSensorModel) {

	SensorInterfaceModel_updateValue(&generalIOSensorModel->sensorInterfaceModel);

	// for shake
	if (generalIOSensorModel->middleCount > 10) {
		generalIOSensorModel->secondReadValue = generalIOSensorModel->firstReadValue;
		generalIOSensorModel->firstReadValue = generalIOSensorModel->sensorInterfaceModel.value;
		generalIOSensorModel->middleCount = 0;
	}
	else {
		generalIOSensorModel->middleCount++;
	}

	if (generalIOSensorModel->firstReadValue == 1
			&& generalIOSensorModel->secondReadValue == 1) {
		generalIOSensorModel->ioValue = 1;
	}
	else {
		generalIOSensorModel->ioValue = 0;
	}
}

