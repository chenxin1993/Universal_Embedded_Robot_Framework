/*
 * SensorInterfaceModel.cpp
 *
 *  Created on: 2016-5-23
 *      Author: 康复组
 */

#include <RobotSystemFiles/HardwareLevel/Bus/Realization/TMS320F28335/sensor_interface_model.h>

/********************************************
 *
 * 	函数说明：传感器接口数据模型初始化
 *
 ********************************************/
void SensorInterfaceModel::init(
		int boardIndex,
		int portIndex,
		int initValue) {

	this->boardIndex 	= boardIndex;
	this->portIndex 	= portIndex;
	this->value 		= initValue;
}

/********************************************
 *
 * 	函数说明：传感器接口数据模型参数拷贝
 *
 ********************************************/
void SensorInterfaceModel::copy(
		class SensorInterfaceModel * sensorInterfaceModelFrom) {

	this->boardIndex 	= sensorInterfaceModelFrom->boardIndex;
	this->portIndex 	= sensorInterfaceModelFrom->portIndex;
	this->value 		= sensorInterfaceModelFrom->value;
}

/********************************************
 *
 * 	函数说明：传感器接口数据模型读取数据(更新数据)
 *
 ********************************************/
void SensorInterfaceModel::update() {

}



