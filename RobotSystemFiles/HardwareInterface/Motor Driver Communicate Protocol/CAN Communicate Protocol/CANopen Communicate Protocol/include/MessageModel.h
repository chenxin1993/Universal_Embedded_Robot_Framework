/*
 * CANStruct.h
 *
 *  Created on: 2016-10-24
 *      Author: e701
 */

#ifndef CANSTRUCT_H_
#define CANSTRUCT_H_

struct MessageModel;
typedef struct MessageModel Message;

struct MessageModel {
  unsigned int 	cob_id;	/**< message's ID */
  unsigned char rtr;		/**< remote transmission request. (0 if not rtr message, 1 if rtr message) */
  unsigned char len;		/**< message's length (0 to 8) */
  unsigned char data[8]; /**< message's datas */
};


#endif /* CANSTRUCT_H_ */
