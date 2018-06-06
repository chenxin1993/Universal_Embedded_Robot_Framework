/*
 * FuncPointerModel.h
 *
 *  Created on: 2017-3-14
 *      Author: e701
 */

#ifndef FUNCPOINTERMODEL_H_
#define FUNCPOINTERMODEL_H_

#include "CO_DataModel.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SYNC ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef void (*post_sync_t)(CO_Data * d);
typedef void (*post_TPDO_t)(CO_Data * d);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ OD ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Prototypes of function provided by object dictionnary */
typedef UNS32 (*ODCallback_t)(CO_Data * d, const indextable* index, UNS8 bSubindex);
typedef const indextable * (*scanIndexOD_t)(UNS16 wIndex, UNS32 * errorCode, ODCallback_t **Callback);
//typedef UNS32 (*valueRangeTest_t)(UNS8 typeValue, void *Value);
typedef void (* storeODSubIndex_t)(CO_Data * d, UNS16 wIndex, UNS8 bSubindex);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SDO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef void (*SDOCallback_t)(CO_Data * d, UNS8 nodeId, UNS8 line);


#endif /* FUNCPOINTERMODEL_H_ */
