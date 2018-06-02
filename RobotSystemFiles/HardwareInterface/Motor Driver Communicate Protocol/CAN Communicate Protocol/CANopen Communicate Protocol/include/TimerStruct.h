/*
 * TimerStruct.h
 *
 *  Created on: 2016-10-24
 *      Author: e701
 */

#ifndef TIMERSTRUCT_H_
#define TIMERSTRUCT_H_

#include "../../../../../../RobotSystemFiles/HardwareInterface/Motor Driver Communicate Protocol/CAN Communicate Protocol/CANopen Communicate Protocol/include/CO_DataModel.h"

typedef void (*TimerCallback_t)(CO_Data* d, UNS32 id);

struct struct_s_timer_entry {
	UNS8 state;
	CO_Data* d;
	TimerCallback_t callback; 	/* The callback func. */
	UNS32 id;	 				/* The callback func. */
	TIMEVAL val;
	TIMEVAL interval; 			/* Periodicity */
};

typedef struct struct_s_timer_entry s_timer_entry;

#endif /* TIMERSTRUCT_H_ */
