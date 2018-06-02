/*
 * VisionSensorStairDetectionModel.c
 *
 *  Created on: 2018年1月23日
 *      Author: xin
 */

#include <RobotSystemFiles/SensorLevel/visionSensor/stairDetection/VisionSensorStairDetectionModel.h>

/********************************************
 *
 * 	函数说明：视觉楼梯检测传感器（KINECT）数据模型值初始化
 *
 ********************************************/
void VisionSensorModel_init(
		struct VisionSensorStairDetectionModel * visionSensorStairDetectionModel,
		int boardIndex) {

	visionSensorStairDetectionModel->stairDetectedFlagSensorInterfaceModel.boardIndex 	= boardIndex;
	visionSensorStairDetectionModel->stairDetectedFlagSensorInterfaceModel.portIndex	= 0;

	visionSensorStairDetectionModel->lineHorizontalDistanceSensorInterfaceModel_low.boardIndex 	= boardIndex;
	visionSensorStairDetectionModel->lineHorizontalDistanceSensorInterfaceModel_low.portIndex	= 1;
	visionSensorStairDetectionModel->lineHorizontalDistanceSensorInterfaceModel_high.boardIndex	= boardIndex;
	visionSensorStairDetectionModel->lineHorizontalDistanceSensorInterfaceModel_high.portIndex	= 2;

	visionSensorStairDetectionModel->lineVerticalDistanceSensorInterfaceModel_low.boardIndex	= boardIndex;
	visionSensorStairDetectionModel->lineVerticalDistanceSensorInterfaceModel_low.portIndex		= 3;
	visionSensorStairDetectionModel->lineVerticalDistanceSensorInterfaceModel_high.boardIndex	= boardIndex;
	visionSensorStairDetectionModel->lineVerticalDistanceSensorInterfaceModel_high.portIndex	= 4;

	visionSensorStairDetectionModel->stairWidthSensorInterfaceModel_low.boardIndex				= boardIndex;
	visionSensorStairDetectionModel->stairWidthSensorInterfaceModel_low.portIndex				= 5;
	visionSensorStairDetectionModel->stairWidthSensorInterfaceModel_high.boardIndex				= boardIndex;
	visionSensorStairDetectionModel->stairWidthSensorInterfaceModel_high.portIndex				= 6;

	visionSensorStairDetectionModel->stairHeightSensorInterfaceModel_low.boardIndex				= boardIndex;
	visionSensorStairDetectionModel->stairHeightSensorInterfaceModel_low.portIndex				= 7;
	visionSensorStairDetectionModel->stairHeightSensorInterfaceModel_high.boardIndex			= boardIndex;
	visionSensorStairDetectionModel->stairHeightSensorInterfaceModel_high.portIndex				= 8;
}

/********************************************
 *
 * 	函数说明：视觉楼梯检测传感器（KINECT）数据模型值拷贝
 *
 ********************************************/
void VisionSensorModel_copy(
		struct VisionSensorStairDetectionModel * visionSensorStairDetectionModelTo,
		struct VisionSensorStairDetectionModel * visionSensorStairDetectionModelFrom) {

}

/********************************************
 *
 * 	函数说明：视觉楼梯检测传感器（KINECT）数据模型值更新
 *
 ********************************************/
void VisionSensorModel_updateValue(
		struct VisionSensorStairDetectionModel * visionSensorStairDetectionModel) {

	SensorInterfaceModel_updateValue(&visionSensorStairDetectionModel->stairDetectedFlagSensorInterfaceModel);
	SensorInterfaceModel_updateValue(&visionSensorStairDetectionModel->lineHorizontalDistanceSensorInterfaceModel_low);
	SensorInterfaceModel_updateValue(&visionSensorStairDetectionModel->lineHorizontalDistanceSensorInterfaceModel_high);
	SensorInterfaceModel_updateValue(&visionSensorStairDetectionModel->lineVerticalDistanceSensorInterfaceModel_low);
	SensorInterfaceModel_updateValue(&visionSensorStairDetectionModel->lineVerticalDistanceSensorInterfaceModel_high);
	SensorInterfaceModel_updateValue(&visionSensorStairDetectionModel->stairWidthSensorInterfaceModel_low);
	SensorInterfaceModel_updateValue(&visionSensorStairDetectionModel->stairWidthSensorInterfaceModel_high);
	SensorInterfaceModel_updateValue(&visionSensorStairDetectionModel->stairHeightSensorInterfaceModel_low);
	SensorInterfaceModel_updateValue(&visionSensorStairDetectionModel->stairHeightSensorInterfaceModel_high);

	visionSensorStairDetectionModel->stairDetectedFlag = visionSensorStairDetectionModel->stairDetectedFlagSensorInterfaceModel.value;
	visionSensorStairDetectionModel->lineHorizontalDistance =
			DataFormat_getFloatFromUInt16(
					&visionSensorStairDetectionModel->lineHorizontalDistanceSensorInterfaceModel_low.value,
					&visionSensorStairDetectionModel->lineHorizontalDistanceSensorInterfaceModel_high.value);
	visionSensorStairDetectionModel->lineVerticalDistance =
			DataFormat_getFloatFromUInt16(
					&visionSensorStairDetectionModel->lineVerticalDistanceSensorInterfaceModel_low.value,
					&visionSensorStairDetectionModel->lineVerticalDistanceSensorInterfaceModel_high.value);
	visionSensorStairDetectionModel->stairWidth =
			DataFormat_getFloatFromUInt16(
					&visionSensorStairDetectionModel->stairWidthSensorInterfaceModel_low.value,
					&visionSensorStairDetectionModel->stairWidthSensorInterfaceModel_high.value);
	visionSensorStairDetectionModel->stairHeight =
			DataFormat_getFloatFromUInt16(
					&visionSensorStairDetectionModel->stairHeightSensorInterfaceModel_low.value,
					&visionSensorStairDetectionModel->stairHeightSensorInterfaceModel_high.value);

}

