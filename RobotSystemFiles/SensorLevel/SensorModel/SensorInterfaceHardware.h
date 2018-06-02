/*
 * SensorInterfaceHardware.h
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#ifndef USERFILES_HARDWARE_SENSORINTERFACE_SENSORINTERFACEHARDWARE_H_
#define USERFILES_HARDWARE_SENSORINTERFACE_SENSORINTERFACEHARDWARE_H_

//--------------------------------------------macro definition
#define SENSOR_VALUE_REQUEST_SET		GpioDataRegs.GPASET.bit.GPIO6 = 1
#define SENSOR_VALUE_REQUEST_CLEAR		GpioDataRegs.GPACLEAR.bit.GPIO6 = 1

#define SENSOR_VALUE_GET_SIGNAL			GpioDataRegs.GPADAT.bit.GPIO7

#define SENSOR_BOARD_SELECT_INDEX1		GpioDataRegs.GPASET.bit.GPIO1
#define SENSOR_BOARD_SELECT_INDEX0		GpioDataRegs.GPASET.bit.GPIO0

#define SENSOR_OBJECT_SELECT_INDEX3		GpioDataRegs.GPASET.bit.GPIO8
#define SENSOR_OBJECT_SELECT_INDEX2		GpioDataRegs.GPASET.bit.GPIO9
#define SENSOR_OBJECT_SELECT_INDEX1		GpioDataRegs.GPASET.bit.GPIO10
#define SENSOR_OBJECT_SELECT_INDEX0		GpioDataRegs.GPASET.bit.GPIO11

#define SENSOR_VALUE_DATA_BIT0			GpioDataRegs.GPADAT.bit.GPIO22
#define SENSOR_VALUE_DATA_BIT1			GpioDataRegs.GPADAT.bit.GPIO23
#define SENSOR_VALUE_DATA_BIT2			GpioDataRegs.GPADAT.bit.GPIO24
#define SENSOR_VALUE_DATA_BIT3			GpioDataRegs.GPADAT.bit.GPIO25
#define SENSOR_VALUE_DATA_BIT4			GpioDataRegs.GPADAT.bit.GPIO26
#define SENSOR_VALUE_DATA_BIT5			GpioDataRegs.GPADAT.bit.GPIO27
#define SENSOR_VALUE_DATA_BIT6			GpioDataRegs.GPBDAT.bit.GPIO49
#define SENSOR_VALUE_DATA_BIT7			GpioDataRegs.GPBDAT.bit.GPIO50
#define SENSOR_VALUE_DATA_BIT8			GpioDataRegs.GPBDAT.bit.GPIO51
#define SENSOR_VALUE_DATA_BIT9			GpioDataRegs.GPBDAT.bit.GPIO52
#define SENSOR_VALUE_DATA_BIT10			GpioDataRegs.GPBDAT.bit.GPIO53
#define SENSOR_VALUE_DATA_BIT11			GpioDataRegs.GPBDAT.bit.GPIO54
#define SENSOR_VALUE_DATA_BIT12			GpioDataRegs.GPBDAT.bit.GPIO55
#define SENSOR_VALUE_DATA_BIT13			GpioDataRegs.GPBDAT.bit.GPIO56
#define SENSOR_VALUE_DATA_BIT14			GpioDataRegs.GPBDAT.bit.GPIO57
#define SENSOR_VALUE_DATA_BIT15			GpioDataRegs.GPBDAT.bit.GPIO58
//--------------------------------------------macro definition

//--------------------------------------------functions
void SensorInterfaceHardware_sensorInterfaceGPIOInit();
unsigned int 	SensorInterfaceHardware_getSensorValueAt(int boardIndex, int sensorIndex);
//--------------------------------------------functions

#endif /* USERFILES_HARDWARE_SENSORINTERFACE_SENSORINTERFACEHARDWARE_H_ */
