/*
 * VisionSensorStairDetectionModel.h
 *
 *  Created on: 2018年1月23日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_SENSORS_VISIONSENSOR_STAIRDETECTION_VISIONSENSORSTAIRDETECTIONMODEL_H_
#define USERFILES_MODEL_SENSORS_VISIONSENSOR_STAIRDETECTION_VISIONSENSORSTAIRDETECTIONMODEL_H_

#include "../../../OPERATION_dataFormat/DataFormat.h"
#include "../../sensorInterface/SensorInterfaceModel.h"

struct VisionSensorStairDetectionModel {

	struct SensorInterfaceModel stairDetectedFlagSensorInterfaceModel;
	struct SensorInterfaceModel lineHorizontalDistanceSensorInterfaceModel_low;
	struct SensorInterfaceModel lineHorizontalDistanceSensorInterfaceModel_high;
	struct SensorInterfaceModel lineVerticalDistanceSensorInterfaceModel_low;
	struct SensorInterfaceModel lineVerticalDistanceSensorInterfaceModel_high;
	struct SensorInterfaceModel stairWidthSensorInterfaceModel_low;
	struct SensorInterfaceModel stairWidthSensorInterfaceModel_high;
	struct SensorInterfaceModel stairHeightSensorInterfaceModel_low;
	struct SensorInterfaceModel stairHeightSensorInterfaceModel_high;

	unsigned int 	stairDetectedFlag;
	float			lineHorizontalDistance;
	float			lineVerticalDistance;
	float 			stairWidth;
	float			stairHeight;
};

void VisionSensorModel_init(
		struct VisionSensorStairDetectionModel * visionSensorStairDetectionModel,
		int boardIndex);

void VisionSensorModel_copy(
		struct VisionSensorStairDetectionModel * visionSensorStairDetectionModelTo,
		struct VisionSensorStairDetectionModel * visionSensorStairDetectionModelFrom);

void VisionSensorModel_updateValue(
		struct VisionSensorStairDetectionModel * visionSensorStairDetectionModel);



#endif /* USERFILES_MODEL_SENSORS_VISIONSENSOR_STAIRDETECTION_VISIONSENSORSTAIRDETECTIONMODEL_H_ */
