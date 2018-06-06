/*
 * AngleSensorModel.cpp
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#include <RobotSystemFiles/SensorLevel/AngleSensor/angle_sensor_model.h>

/********************************************
 *
 * 	函数说明: 角度传感器模型初始化
 *
 ********************************************/
int AngleSensorModel::init() {

}

/********************************************
 *
 * 	函数说明: 角度传感器模型读取值
 *
 ********************************************/
int AngleSensorModel::update() {

	this->angleValue =
			this->direction * 360 * ((float)this->rawValue - this->biasValue) / 65535.0 + this->initValue;

	this->radianValue =
			this->direction * 2 * 3.1415926 * ((float)this->rawValue - this->biasValue) / 65535.0 + this->initValue;
}

/********************************************
 *
 * 	函数说明: 读取 角度传感器模型
 *
 ********************************************/
int AngleSensorModel::read(void * data) {

}

/********************************************
 *
 * 	函数说明: 写入 角度传感器模型
 *
 ********************************************/
int AngleSensorModel::write(void * data) {

}
