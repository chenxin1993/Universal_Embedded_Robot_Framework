/*
 * RobotForceSensorModel.c
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#include <RobotSystemFiles/SensorLevel/forceSensor/RobotForceSensorModel.h>

/********************************************
 *
 * 	函数说明：力传感器数据模型初始化
 *
 ********************************************/
void RobotForceSensorModel_init(
		struct RobotForceSensorModel * robotForceSensorModel) {

}

/********************************************
 *
 * 	函数说明：力传感器数据模型更新
 *
 ********************************************/
void RobotForceSensorModel_update(
		struct RobotForceSensorModel * robotForceSensorModel) {

	ForceSensorModel_updateValue(&robotForceSensorModel->leftLegForceSensorModel1);
	ForceSensorModel_updateValue(&robotForceSensorModel->leftLegForceSensorModel2);
	ForceSensorModel_updateValue(&robotForceSensorModel->leftLegForceSensorModel3);
	ForceSensorModel_updateValue(&robotForceSensorModel->leftLegForceSensorModel4);
	ForceSensorModel_updateValue(&robotForceSensorModel->leftLegForceSensorModel5);
	ForceSensorModel_updateValue(&robotForceSensorModel->leftLegForceSensorModel6);
//	ForceSensorModel_updateValue(&robotForceSensorModel->leftLegForceSensorModel7);
//	ForceSensorModel_updateValue(&robotForceSensorModel->leftLegForceSensorModel8);
//	ForceSensorModel_updateValue(&robotForceSensorModel->leftLegForceSensorModel9);
//	ForceSensorModel_updateValue(&robotForceSensorModel->leftLegForceSensorModel10);
//	ForceSensorModel_updateValue(&robotForceSensorModel->leftLegForceSensorModel11);
//	ForceSensorModel_updateValue(&robotForceSensorModel->leftLegForceSensorModel12);
//
//	ForceSensorModel_updateValue(&robotForceSensorModel->rightLegForceSensorModel1);
//	ForceSensorModel_updateValue(&robotForceSensorModel->rightLegForceSensorModel2);
//	ForceSensorModel_updateValue(&robotForceSensorModel->rightLegForceSensorModel3);
//	ForceSensorModel_updateValue(&robotForceSensorModel->rightLegForceSensorModel4);
//	ForceSensorModel_updateValue(&robotForceSensorModel->rightLegForceSensorModel5);
//	ForceSensorModel_updateValue(&robotForceSensorModel->rightLegForceSensorModel6);
//	ForceSensorModel_updateValue(&robotForceSensorModel->rightLegForceSensorModel7);
//	ForceSensorModel_updateValue(&robotForceSensorModel->rightLegForceSensorModel8);
//	ForceSensorModel_updateValue(&robotForceSensorModel->rightLegForceSensorModel9);
//	ForceSensorModel_updateValue(&robotForceSensorModel->rightLegForceSensorModel10);
//	ForceSensorModel_updateValue(&robotForceSensorModel->rightLegForceSensorModel11);
//	ForceSensorModel_updateValue(&robotForceSensorModel->rightLegForceSensorModel12);
}
