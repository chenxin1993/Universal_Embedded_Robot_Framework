/*
 * RobotAngleSensorModel.c
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#include <RobotSystemFiles/SensorLevel/angleSensor/RobotAngleSensorModel.h>

/********************************************
 *
 * 	函数说明: 机器人角度传感器模型初始化
 *
 ********************************************/
void RobotAngleSensorModel_init(
		struct RobotAngleSensorModel * robotAngleSensorModel) {

}

/********************************************
 *
 * 	函数说明: 机器人角度传感器读取值
 *
 ********************************************/
void RobotAngleSensorModel_updateValue(
		struct RobotAngleSensorModel * robotAngleSensorModel) {

	AngleSensorModel_updateValue(&robotAngleSensorModel->leftLegAngleSensor1);
	AngleSensorModel_updateValue(&robotAngleSensorModel->leftLegAngleSensor2);
	AngleSensorModel_updateValue(&robotAngleSensorModel->rightLegAngleSensor1);
	AngleSensorModel_updateValue(&robotAngleSensorModel->rightLegAngleSensor2);
}

