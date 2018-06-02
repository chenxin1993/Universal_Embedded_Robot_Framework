/*
 * RobotFootForceSensorModel.h
 *
 *  Created on: 2017年4月22日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_SENSORS_FORCESENSOR_ROBOTFOOTFORCESENSORMODEL_H_
#define USERFILES_MODEL_SENSORS_FORCESENSOR_ROBOTFOOTFORCESENSORMODEL_H_

#include "../../../RobotSystemFiles/SensorLevel/forceSensor/ForceSensorModel.h"

struct RobotFootForceSensorModel {

	struct ForceSensorModel leftLegFootForceSensorModel1;

	struct ForceSensorModel rightLegFootForceSensorModel1;
};

void RobotFootForceSensorModel_init(
		struct RobotFootForceSensorModel * robotFootForceSensorModel);

void RobotFootForceSensorModel_update(
		struct RobotFootForceSensorModel * robotFootForceSensorModel);



#endif /* USERFILES_MODEL_SENSORS_FORCESENSOR_ROBOTFOOTFORCESENSORMODEL_H_ */
