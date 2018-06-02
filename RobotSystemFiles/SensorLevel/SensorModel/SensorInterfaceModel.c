/*
 * SensorInterfaceModel.c
 *
 *  Created on: 2016-5-23
 *      Author: 康复组
 */

#include <RobotSystemFiles/SensorLevel/SensorModel/SensorInterfaceModel.h>

/********************************************
 *
 * 	函数说明：传感器接口数据模型初始化
 *
 ********************************************/
void SensorInterfaceModel_init(
		struct SensorInterfaceModel * sensorInterfaceModel,
		int boardIndex,
		int portIndex,
		int initValue) {

	sensorInterfaceModel->boardIndex 	= boardIndex;
	sensorInterfaceModel->portIndex 	= portIndex;
	sensorInterfaceModel->value 		= initValue;
}

/********************************************
 *
 * 	函数说明：传感器接口数据模型参数拷贝
 *
 ********************************************/
void SensorInterfaceModel_copy(
		struct SensorInterfaceModel * sensorInterfaceModelTo,
		struct SensorInterfaceModel * sensorInterfaceModelFrom) {

	sensorInterfaceModelTo->boardIndex 	= sensorInterfaceModelFrom->boardIndex;
	sensorInterfaceModelTo->portIndex 	= sensorInterfaceModelFrom->portIndex;
	sensorInterfaceModelTo->value 		= sensorInterfaceModelFrom->value;
}

/********************************************
 *
 * 	函数说明：传感器接口数据模型读取数据(更新数据)
 *
 ********************************************/
void SensorInterfaceModel_updateValue(
		struct SensorInterfaceModel * sensorInterfaceModel) {

	sensorInterfaceModel->value =
			SensorInterfaceHardware_getSensorValueAt(
					sensorInterfaceModel->boardIndex,
					sensorInterfaceModel->portIndex);
}



