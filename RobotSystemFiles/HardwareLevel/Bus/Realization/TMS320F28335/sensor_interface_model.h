/*
 * SensorInterfaceModel.h
 *
 *  Created on: 2016-5-23
 *      Author: 康复组
 */

#ifndef SENSORINTERFACEMODEL_H_
#define SENSORINTERFACEMODEL_H_

class SensorInterfaceModel {

public:
	unsigned int boardIndex;
	unsigned int portIndex;
	unsigned int value;

	void init(int boardIndex, int portIndex, int initValue);
	void copy(class SensorInterfaceModel * sensorInterfaceModelFrom);
	void update();
};

#endif /* SENSORINTERFACEMODEL_H_ */
