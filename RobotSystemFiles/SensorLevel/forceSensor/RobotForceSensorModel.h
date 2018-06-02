/*
 * RobotForceSensorModel.h
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_SENSORS_FORCESENSOR_ROBOTFORCESENSORMODEL_H_
#define USERFILES_MODEL_SENSORS_FORCESENSOR_ROBOTFORCESENSORMODEL_H_

#include "../../../RobotSystemFiles/SensorLevel/forceSensor/ForceSensorModel.h"

struct RobotForceSensorModel {

	struct ForceSensorModel leftLegForceSensorModel1;
	struct ForceSensorModel leftLegForceSensorModel2;
	struct ForceSensorModel leftLegForceSensorModel3;
	struct ForceSensorModel leftLegForceSensorModel4;
	struct ForceSensorModel leftLegForceSensorModel5;
	struct ForceSensorModel leftLegForceSensorModel6;
	struct ForceSensorModel leftLegForceSensorModel7;
	struct ForceSensorModel leftLegForceSensorModel8;
	struct ForceSensorModel leftLegForceSensorModel9;
	struct ForceSensorModel leftLegForceSensorModel10;
	struct ForceSensorModel leftLegForceSensorModel11;
	struct ForceSensorModel leftLegForceSensorModel12;

	struct ForceSensorModel rightLegForceSensorModel1;
	struct ForceSensorModel rightLegForceSensorModel2;
	struct ForceSensorModel rightLegForceSensorModel3;
	struct ForceSensorModel rightLegForceSensorModel4;
	struct ForceSensorModel rightLegForceSensorModel5;
	struct ForceSensorModel rightLegForceSensorModel6;
	struct ForceSensorModel rightLegForceSensorModel7;
	struct ForceSensorModel rightLegForceSensorModel8;
	struct ForceSensorModel rightLegForceSensorModel9;
	struct ForceSensorModel rightLegForceSensorModel10;
	struct ForceSensorModel rightLegForceSensorModel11;
	struct ForceSensorModel rightLegForceSensorModel12;
};

void RobotForceSensorModel_init(
		struct RobotForceSensorModel * robotForceSensorModel);

void RobotForceSensorModel_update(
		struct RobotForceSensorModel * robotForceSensorModel);

#endif /* USERFILES_MODEL_SENSORS_FORCESENSOR_ROBOTFORCESENSORMODEL_H_ */
