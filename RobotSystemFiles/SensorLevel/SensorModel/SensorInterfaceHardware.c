/*
 * SensorInterfaceHardware.c
 *
 *  Created on: 2017年3月8日
 *      Author: xin
 */

#include <RobotSystemFiles/SensorLevel/SensorModel/SensorInterfaceHardware.h>
sorModel/SensorInterfaceHardware.h>
#include "DSP2833x_Device.h"

/*******************************************
 *
 * 	函数说明：	初始化传感器数据接收端口
 *
 *******************************************/
static void SensorInterfaceHardware_sensorDataGPIOInit() {

	EALLOW;

	GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;

	GpioCtrlRegs.GPBDIR.bit.GPIO49	= 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO50	= 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO51	= 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO52	= 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO53	= 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO54	= 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO55	= 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO56	= 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO57	= 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO58	= 0;

	EDIS;
}

/********************************************
 *
 * 	函数说明：初始化传感器板子选取的端口
 *
 ********************************************/
static void SensorInterfaceHardware_sensorBoardSelectGPIOInit() {

	EALLOW;

	GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;		// GPIO0 is board address 0
	GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;		// GPIO1 is board address 1
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;		// GPIO1 is board address 2

	EDIS;
}

/********************************************
 *
 * 	函数说明：初始化传感器选取的端口
 *
 * 	注意：	对于输入口必须要再次设置为输入模式，
 * 			否则貌似不一定能够作为输入口使用，会出现逻辑错误
 *
 ********************************************/
static void SensorInterfaceHardware_sensorObjectSelectGPIOInit() {

	EALLOW;

	GpioCtrlRegs.GPADIR.bit.GPIO11 	= 1;
	GpioCtrlRegs.GPADIR.bit.GPIO10 	= 1;
	GpioCtrlRegs.GPADIR.bit.GPIO9 	= 1;
	GpioCtrlRegs.GPADIR.bit.GPIO8 	= 1;

	GpioCtrlRegs.GPADIR.bit.GPIO6 	= 1;
	GpioCtrlRegs.GPADIR.bit.GPIO7 	= 0;

	EDIS;
}

/********************************************
 *
 * 	函数说明：传感器接口电路初始化
 *
 ********************************************/
void SensorInterfaceHardware_sensorInterfaceGPIOInit() {

	SensorInterfaceHardware_sensorDataGPIOInit();
	SensorInterfaceHardware_sensorBoardSelectGPIOInit();
	SensorInterfaceHardware_sensorObjectSelectGPIOInit();
}

/********************************************
 *
 * 	函数说明：选择指定编号的传感器板子
 *
 ********************************************/
static void SensorInterfaceHardware__sensorBoardSelect(int index1, int index0) {

	SENSOR_BOARD_SELECT_INDEX1 = index1;
	SENSOR_BOARD_SELECT_INDEX0 = index0;
}

static void SensorInterfaceHardware_sensorBoardSelect(int boardIndex) {

	GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO2	= 1;

	if (boardIndex == 0) {
		SensorInterfaceHardware__sensorBoardSelect(0, 0);
	}
	else if (boardIndex == 1) {
		SensorInterfaceHardware__sensorBoardSelect(0, 1);
	}
	else if (boardIndex == 2) {
		SensorInterfaceHardware__sensorBoardSelect(1, 0);
	}
	else if (boardIndex == 3) {
		SensorInterfaceHardware__sensorBoardSelect(1, 1);
	}
	else {
	}
}

/********************************************
 *
 * 	函数说明：选择指定编号的传感器板子的传感器
 *
 ********************************************/
static void SensorInterfaceHardware__sensorPortSelect(int index3, int index2, int index1, int index0) {

	SENSOR_OBJECT_SELECT_INDEX3 = index3;
	SENSOR_OBJECT_SELECT_INDEX2 = index2;
	SENSOR_OBJECT_SELECT_INDEX1 = index1;
	SENSOR_OBJECT_SELECT_INDEX0 = index0;
}

static void SensorInterfaceHardware_sensorPortSelect(int sensorIndex) {

	GpioDataRegs.GPACLEAR.bit.GPIO11 	= 1;
	GpioDataRegs.GPACLEAR.bit.GPIO10 	= 1;
	GpioDataRegs.GPACLEAR.bit.GPIO9 	= 1;
	GpioDataRegs.GPACLEAR.bit.GPIO8 	= 1;

	if (sensorIndex == 0) {
		SensorInterfaceHardware__sensorPortSelect(0, 0, 0, 0);
	}
	else if (sensorIndex == 1) {
		SensorInterfaceHardware__sensorPortSelect(0, 0, 0, 1);
	}
	else if (sensorIndex == 2) {
		SensorInterfaceHardware__sensorPortSelect(0, 0, 1, 0);
	}
	else if (sensorIndex == 3) {
		SensorInterfaceHardware__sensorPortSelect(0, 0, 1, 1);
	}
	else if (sensorIndex == 4) {
		SensorInterfaceHardware__sensorPortSelect(0, 1, 0, 0);
	}
	else if (sensorIndex == 5) {
		SensorInterfaceHardware__sensorPortSelect(0, 1, 0, 1);
	}
	else if (sensorIndex == 6) {
		SensorInterfaceHardware__sensorPortSelect(0, 1, 1, 0);
	}
	else if (sensorIndex == 7) {
		SensorInterfaceHardware__sensorPortSelect(0, 1, 1, 1);
	}
	else if (sensorIndex == 8) {
		SensorInterfaceHardware__sensorPortSelect(1, 0, 0, 0);
	}
	else if (sensorIndex == 9) {
		SensorInterfaceHardware__sensorPortSelect(1, 0, 0, 1);
	}
	else if (sensorIndex == 10) {
		SensorInterfaceHardware__sensorPortSelect(1, 0, 1, 0);
	}
	else if (sensorIndex == 11) {
		SensorInterfaceHardware__sensorPortSelect(1, 0, 1, 1);
	}
	else if (sensorIndex == 12) {
		SensorInterfaceHardware__sensorPortSelect(1, 1, 0, 0);
	}
	else if (sensorIndex == 13) {
		SensorInterfaceHardware__sensorPortSelect(1, 1, 0, 1);
	}
	else if (sensorIndex == 14) {
		SensorInterfaceHardware__sensorPortSelect(1, 1, 1, 0);
	}
	else if (sensorIndex == 15) {
		SensorInterfaceHardware__sensorPortSelect(1, 1, 1, 1);
	}
	else {
	}
}

/********************************************
 *
 * 	函数说明：发送请求数据指令
 *
 ********************************************/
static void SensorInterfaceHardware_requestSensorValue() {

	SENSOR_VALUE_REQUEST_SET;
}

/********************************************
 *
 * 	函数说明：回复回应指令
 *
 ********************************************/
static void SensorInterfaceHardware_answerForSensorACK() {

	SENSOR_VALUE_REQUEST_CLEAR;
}

/********************************************
 *
 * 	函数说明：读取传感器值操作
 *
 ********************************************/
static unsigned int SensorInterfaceHardware_readSensorValue() {

	unsigned int sensorValue = 0;

	if(SENSOR_VALUE_DATA_BIT0 == 1) {
		sensorValue += 1;
	}
	if(SENSOR_VALUE_DATA_BIT1 == 1) {
		sensorValue += 2;
	}
	if(SENSOR_VALUE_DATA_BIT2 == 1) {
		sensorValue += 4;
	}
	if(SENSOR_VALUE_DATA_BIT3 == 1) {
		sensorValue += 8;
	}
	if(SENSOR_VALUE_DATA_BIT4 == 1) {
		sensorValue += 16;
	}
	if(SENSOR_VALUE_DATA_BIT5 == 1) {
		sensorValue += 32;
	}
	if(SENSOR_VALUE_DATA_BIT6 == 1) {
		sensorValue += 64;
	}
	if(SENSOR_VALUE_DATA_BIT7 == 1) {
		sensorValue += 128;
	}
	if(SENSOR_VALUE_DATA_BIT8 == 1) {
		sensorValue += 256;
	}
	if(SENSOR_VALUE_DATA_BIT9 == 1) {
		sensorValue += 512;
	}
	if(SENSOR_VALUE_DATA_BIT10 == 1) {
		sensorValue += 1024;
	}
	if(SENSOR_VALUE_DATA_BIT11 == 1) {
		sensorValue += 2048;
	}
	if(SENSOR_VALUE_DATA_BIT12 == 1) {
		sensorValue += 4096;
	}
	if(SENSOR_VALUE_DATA_BIT13 == 1) {
		sensorValue += 8192;
	}
	if(SENSOR_VALUE_DATA_BIT14 == 1) {
		sensorValue += 16384;
	}
	if(SENSOR_VALUE_DATA_BIT15 == 1) {
		sensorValue += 32768;
	}

	return sensorValue;
}

/********************************************
 *
 * 	函数说明：等待回应指令
 *
 ********************************************/
static unsigned int SensorInterfaceHardware_waitForSensorACK() {

	int count = 0;

	while(SENSOR_VALUE_GET_SIGNAL == 0) {

		count++;
		if (count > (150 * 10)) {
			SENSOR_VALUE_REQUEST_CLEAR;
			return 0;
		}
	}

	return SensorInterfaceHardware_readSensorValue();
}

/********************************************
 *
 * 	函数说明：获取指定的传感器的值
 *
 ********************************************/
unsigned int SensorInterfaceHardware_getSensorValueAt(int boardIndex, int portIndex) {

	volatile unsigned int sensorValue = 0;

	SensorInterfaceHardware_sensorBoardSelect(boardIndex);
	SensorInterfaceHardware_sensorPortSelect(portIndex);

	SensorInterfaceHardware_requestSensorValue();
	sensorValue = SensorInterfaceHardware_waitForSensorACK();
	SensorInterfaceHardware_answerForSensorACK();

	return sensorValue;
}


