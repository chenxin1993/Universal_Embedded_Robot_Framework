/*
 * StateStruct.h
 *
 *  Created on: 2016-10-24
 *      Author: e701
 */

#ifndef STATESTRUCT_H_
#define STATESTRUCT_H_

typedef struct
{
	INTEGER8 csBoot_Up;
	INTEGER8 csSDO;
	INTEGER8 csEmergency;
	INTEGER8 csSYNC;
	INTEGER8 csHeartbeat;
	INTEGER8 csPDO;
	INTEGER8 csLSS;
} s_state_communication;

#endif /* STATESTRUCT_H_ */
