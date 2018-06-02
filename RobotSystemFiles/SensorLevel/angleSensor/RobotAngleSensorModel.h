/*
 * RobotAngleSensorModel.h
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_SENSORS_ANGLESENSOR_ROBOTANGLESENSORMODEL_H_
#define USERFILES_MODEL_SENSORS_ANGLESENSOR_ROBOTANGLESENSORMODEL_H_

#include "../../../RobotSystemFiles/SensorLevel/angleSensor/AngleSensorModel.h"

struct RobotAngleSensorModel {

	struct AngleSensorModel leftLegAngleSensor1;
	struct AngleSensorModel leftLegAngleSensor2;
	struct AngleSensorModel rightLegAngleSensor1;
	struct AngleSensorModel rightLegAngleSensor2;
};

void RobotAngleSensorModel_init(
		struct RobotAngleSensorModel * robotAngleSensorModel);

void RobotAngleSensorModel_updateValue(
		struct RobotAngleSensorModel * robotAngleSensorModel);

#endif /* USERFILES_MODEL_SENSORS_ANGLESENSOR_ROBOTANGLESENSORMODEL_H_ */
