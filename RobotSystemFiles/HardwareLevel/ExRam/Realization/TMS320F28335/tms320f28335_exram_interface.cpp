/*
 * tms320f28335_exram_interface.cpp
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#include <RobotSystemFiles/HardwareLevel/ExRam/Realization/TMS320F28335/tms320f28335_exram_interface.h>

#ifdef TMS320F28335

unsigned int *DSPRamStart = (unsigned  int *)0x00F000;  	//RAML7前半部分
unsigned int *DSPRamStart2 = (unsigned  int *)0x00F800;  	//RAML7的后半部分
unsigned int *ExRamStart = (unsigned int *)0x100000;		// ExRam

void 	TMS320F28335_ExRam::ram_init(unsigned long Start) {
	unsigned int i;
	for	(i=0;i<0x400;i++) {
		*(ExRamStart + Start + i) = i;
	}
}

void 	TMS320F28335_ExRam::ram_erase(unsigned long	Start) {
	unsigned int i;
	for	(i=0;i<0x400;i++) {
		*(ExRamStart + Start + i) = 0;
	}
}

void	TMS320F28335_ExRam::ram_read(unsigned long Start) {
	unsigned int i;
	for	(i=0;i<0x400;i++) {
		*(DSPRamStart + Start + i) = *(DSPRamStart +i);
	}
}

#endif

