/*
 * RobotFootForceSensorModel.c
 *
 *  Created on: 2017年4月22日
 *      Author: xin
 */

#include <RobotSystemFiles/SensorLevel/forceSensor/RobotFootForceSensorModel.h>

/********************************************
 *
 * 	函数说明：力传感器数据模型初始化
 *
 ********************************************/
void RobotFootForceSensorModel_init(
		struct RobotFootForceSensorModel * robotFootForceSensorModel) {

}

/********************************************
 *
 * 	函数说明：力传感器数据模型更新
 *
 ********************************************/
void RobotFootForceSensorModel_update(
		struct RobotFootForceSensorModel * robotFootForceSensorModel) {

	ForceSensorModel_updateValue(&robotFootForceSensorModel->leftLegFootForceSensorModel1);

	ForceSensorModel_updateValue(&robotFootForceSensorModel->rightLegFootForceSensorModel1);
}


