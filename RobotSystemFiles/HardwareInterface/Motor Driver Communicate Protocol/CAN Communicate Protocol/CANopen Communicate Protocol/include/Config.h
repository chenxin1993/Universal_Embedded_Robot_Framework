#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "Includes.h"
//#include <string.h>
//#include <stdio.h>


/********************** CONSTANT AND STRUCT *********************/
#define Message_Initializer {0,0,0,{0,0,0,0,0,0,0,0}}


/************************* CANOPEN PDO ************************/
/** The PDO structure */
#define s_PDO_status_Initializer {0, TIMER_NONE, TIMER_NONE, Message_Initializer}


#endif /* _CONFIG_H_ */
