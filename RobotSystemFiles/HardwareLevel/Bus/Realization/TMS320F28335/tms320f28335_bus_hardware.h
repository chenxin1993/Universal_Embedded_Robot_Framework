/*
 * tms320f28335_bus_hardware.h
 *
 *  Created on: 2018年6月2日
 *      Author: xin-FFTAI
 */

#ifndef ROBOTSYSTEMFILES_HARDWARELEVEL_BUS_REALIZATION_TMS320F28335_TMS320F28335_BUS_HARDWARE_H_
#define ROBOTSYSTEMFILES_HARDWARELEVEL_BUS_REALIZATION_TMS320F28335_TMS320F28335_BUS_HARDWARE_H_

#ifdef TMS320F28335

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

class TMS320F28335Hardware_Bus : BusHardwareInterface {

public:
	int bus_init(void);
	int bus_send(unsigned char data);
	int bus_read(int boardIndex, int sensorIndex);

	void sensorDataGPIOInit();
	void sensorBoardSelectGPIOInit();
	void sensorObjectSelectGPIOInit();
	void sensorInterfaceGPIOInit();
	void sensorBoardSelect(int index1, int index0);
	void sensorBoardSelect(int boardIndex);
	void sensorPortSelect(int index3, int index2, int index1, int index0);
	void sensorPortSelect(int sensorIndex);
	void requestSensorValue();
	void answerForSensorACK();
	unsigned int readSensorValue();
	unsigned int waitForSensorACK();
	unsigned int getSensorValueAt(int boardIndex, int portIndex);
};

#endif

#endif /* ROBOTSYSTEMFILES_HARDWARELEVEL_BUS_REALIZATION_TMS320F28335_TMS320F28335_BUS_HARDWARE_H_ */
