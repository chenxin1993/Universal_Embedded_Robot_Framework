/*
 * RobotGeneralIOSensorModel.c
 *
 *  Created on: 2017年4月7日
 *      Author: xin
 */

#include <RobotSystemFiles/SensorLevel/generalIO/RobotGeneralIOSensorModel.h>

/********************************************
 *
 * 	函数说明：力传感器数据模型初始化
 *
 ********************************************/
void RobotGeneralIOSensorModel_init(
		struct RobotGeneralIOSensorModel * robotGeneralIOSensorModel) {

}

/********************************************
 *
 * 	函数说明：robot general io update
 *
 ********************************************/
void RobotGeneralIOSensorModel_updateValue(
		struct RobotGeneralIOSensorModel * robotGeneralIOSensorModel) {

	GeneralIOSensorModel_updateValue(&robotGeneralIOSensorModel->leftSideSitButton);
	GeneralIOSensorModel_updateValue(&robotGeneralIOSensorModel->leftSideStandButton);
	GeneralIOSensorModel_updateValue(&robotGeneralIOSensorModel->leftSideWalkButton);
	GeneralIOSensorModel_updateValue(&robotGeneralIOSensorModel->leftSideStopButton);

	GeneralIOSensorModel_updateValue(&robotGeneralIOSensorModel->rightSideSitButton);
	GeneralIOSensorModel_updateValue(&robotGeneralIOSensorModel->rightSideStandButton);
	GeneralIOSensorModel_updateValue(&robotGeneralIOSensorModel->rightSideWalkButton);
	GeneralIOSensorModel_updateValue(&robotGeneralIOSensorModel->rightSideStopButton);

}
