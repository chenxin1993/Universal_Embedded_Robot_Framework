/*
 * MotorDriverCommunicateProtocol.h
 *
 *  Created on: 2018年6月5日
 *      Author: xin-FFTAI
 */

#ifndef ROBOTSYSTEMFILES_HARDWAREINTERFACE_MOTOR_DRIVER_COMMUNICATE_PROTOCOL_MOTOR_DRIVER_COMMUNICATE_PROTOCOL_H_
#define ROBOTSYSTEMFILES_HARDWAREINTERFACE_MOTOR_DRIVER_COMMUNICATE_PROTOCOL_MOTOR_DRIVER_COMMUNICATE_PROTOCOL_H_

class MotorDriverCommunicateProtocol {

public:
	virtual int motor_driver_init() = 0;
	virtual int motor_driver_update() = 0;
	virtual int motor_driver_write(void * data) = 0;
	virtual int motor_driver_read(void * data) = 0;
};



#endif /* ROBOTSYSTEMFILES_HARDWAREINTERFACE_MOTOR_DRIVER_COMMUNICATE_PROTOCOL_MOTOR_DRIVER_COMMUNICATE_PROTOCOL_H_ */
