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
	virtual int sensorModel_init();
	virtual int sensorModel_read();
	virtual int sensorModel_write();
	virtual int sensorModel_update();
};


#endif /* ROBOTSYSTEMFILES_SENSORLEVEL_SENSORMODEL_SENSORMODEL_H_ */
