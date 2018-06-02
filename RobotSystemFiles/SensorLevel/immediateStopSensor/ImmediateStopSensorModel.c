/*
 * ImmediateStopSensor.c
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#include <MODEL_sensors/immediateStopSensor/ImmediateStopSensorModel.h>

/********************************************
 *
 * 	函数说明: 急停开关模型初始化
 *
 ********************************************/
void ImmediateStopSensorModel_init(
		struct ImmediateStopSensorModel * immediateStopSensorModel,
		int boardIndex,
		int portIndex) {

	immediateStopSensorModel->sensorInterfaceModel.boardIndex 	= boardIndex;
	immediateStopSensorModel->sensorInterfaceModel.portIndex 	= portIndex;
}

/********************************************
 *
 * 	函数说明: 获取急停开挂你的值
 *
 ********************************************/
void ImmediateStopSensorModel_updateValue(
		struct ImmediateStopSensorModel * immediateStopSensorModel) {

	SensorInterfaceModel_updateValue(&immediateStopSensorModel->sensorInterfaceModel);
}
