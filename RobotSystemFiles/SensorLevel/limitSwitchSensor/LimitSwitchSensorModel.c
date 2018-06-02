/*
 * LimitSwitchSensorModel.c
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#include <RobotSystemFiles/SensorLevel/limitSwitchSensor/LimitSwitchSensorModel.h>

/********************************************
 *
 * 	函数说明: 限位开关模型初始化
 *
 ********************************************/
void LimitSwitchSensorModel_init(
		struct LimitSwitchSensorModel * limitSwitchSensorModel,
		int boardIndex,
		int portIndex) {

	limitSwitchSensorModel->sensorInterfaceModel.boardIndex = boardIndex;
	limitSwitchSensorModel->sensorInterfaceModel.portIndex 	= portIndex;
}

/********************************************
 *
 * 	函数说明: 获取限位开关的值
 *
 ********************************************/
void LimitSwitchSensorModel_updateValue(
		struct LimitSwitchSensorModel * limitSwitchSensorModel) {

	SensorInterfaceModel_updateValue(&limitSwitchSensorModel->sensorInterfaceModel);
}
