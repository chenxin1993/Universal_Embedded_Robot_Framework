/*
 * RobotVisionSensorStairDetectionModel.h
 *
 *  Created on: 2018年1月23日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_SENSORS_VISIONSENSOR_STAIRDETECTION_ROBOTVISIONSENSORSTAIRDETECTIONMODEL_H_
#define USERFILES_MODEL_SENSORS_VISIONSENSOR_STAIRDETECTION_ROBOTVISIONSENSORSTAIRDETECTIONMODEL_H_

#include "../../../../RobotSystemFiles/SensorLevel/visionSensor/stairDetection/VisionSensorStairDetectionModel.h"

struct RobotVisionSensorStairDetectionModel {

	struct VisionSensorStairDetectionModel visionSensorStairDetectionModel;
};

void RobotVisionSensorStairDetectionModel_init(
		struct RobotVisionSensorStairDetectionModel * robotVisionSensorStairDetectionModel);

void RobotVisionSensorStairDetectionModel_update(
		struct RobotVisionSensorStairDetectionModel * robotVisionSensorStairDetectionModel);

#endif /* USERFILES_MODEL_SENSORS_VISIONSENSOR_STAIRDETECTION_ROBOTVISIONSENSORSTAIRDETECTIONMODEL_H_ */
