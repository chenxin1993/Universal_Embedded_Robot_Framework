/*
 * RobotVisionSensorStairDetectionModel.c
 *
 *  Created on: 2018年1月23日
 *      Author: xin
 */

#include <RobotSystemFiles/SensorLevel/visionSensor/stairDetection/RobotVisionSensorStairDetectionModel.h>

void RobotVisionSensorStairDetectionModel_init(
		struct RobotVisionSensorStairDetectionModel * robotVisionSensorStairDetectionModel) {

}

void RobotVisionSensorStairDetectionModel_update(
		struct RobotVisionSensorStairDetectionModel * robotVisionSensorStairDetectionModel) {

	VisionSensorModel_updateValue(&robotVisionSensorStairDetectionModel->visionSensorStairDetectionModel);
}

