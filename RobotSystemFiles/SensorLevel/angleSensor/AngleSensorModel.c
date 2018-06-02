/*
 * AngleSensorModel.c
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#include <RobotSystemFiles/SensorLevel/angleSensor/AngleSensorModel.h>

/********************************************
 *
 * 	函数说明: 角度传感器模型初始化
 *
 ********************************************/
void AngleSensorModel_init(
		struct AngleSensorModel * angleSensorModel,
		int boardIndex,
		int portIndex,
		float direction,
		float bias,
		float init) {

	angleSensorModel->sensorInterfaceModel.boardIndex 	= boardIndex;
	angleSensorModel->sensorInterfaceModel.portIndex	= portIndex;

	angleSensorModel->direction = direction;
	angleSensorModel->bias = bias;
	angleSensorModel->init = init;
}

/********************************************
 *
 * 	函数说明: 角度传感器模型参数拷贝
 *
 ********************************************/
void AngleSensorModel_copy(
		struct AngleSensorModel * angleSensorModelTo,
		struct AngleSensorModel * angleSensorModelFrom) {

	SensorInterfaceModel_copy(
			&angleSensorModelTo->sensorInterfaceModel,
			&angleSensorModelFrom->sensorInterfaceModel);

	angleSensorModelTo->direction 	= angleSensorModelFrom->direction;
	angleSensorModelTo->bias 		= angleSensorModelFrom->bias;
	angleSensorModelTo->init 		= angleSensorModelFrom->init;
}

/********************************************
 *
 * 	函数说明: 角度传感器模型读取值
 *
 ********************************************/
void AngleSensorModel_updateValue(
		struct AngleSensorModel * angleSensorModel) {

	SensorInterfaceModel_updateValue(&angleSensorModel->sensorInterfaceModel);

	angleSensorModel->rawValue = angleSensorModel->sensorInterfaceModel.value;

	angleSensorModel->angleValue =
			angleSensorModel->direction * 360 * ((float)angleSensorModel->rawValue - angleSensorModel->bias) / ENCODER_FULL_CIRCLE_COUNT + angleSensorModel->init;

	angleSensorModel->radianValue =
			angleSensorModel->direction * 2 * PI * ((float)angleSensorModel->rawValue - angleSensorModel->bias) / ENCODER_FULL_CIRCLE_COUNT + angleSensorModel->init;
}

