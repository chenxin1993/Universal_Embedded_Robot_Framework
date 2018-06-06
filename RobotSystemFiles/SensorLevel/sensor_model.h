/*
 * SensorModel.h
 *
 *  Created on: 2018年6月1日
 *      Author: xin-FFTAI
 */

#ifndef ROBOTSYSTEMFILES_SENSORLEVEL_SENSORMODEL_SENSORMODEL_H_
#define ROBOTSYSTEMFILES_SENSORLEVEL_SENSORMODEL_SENSORMODEL_H_

class SensorModel {

public:
	virtual int init();
	virtual int read(void * data);
	virtual int write(void * data);
	virtual int update();
};


#endif /* ROBOTSYSTEMFILES_SENSORLEVEL_SENSORMODEL_SENSORMODEL_H_ */
