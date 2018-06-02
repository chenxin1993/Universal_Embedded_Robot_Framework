/*
 * tms320f28335_exram_interface.h
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#ifndef USERFILES_HARDWARELEVEL_EXRAM_REALIZATION_TMS320F28335_EXRAM_INTERFACE_H_
#define USERFILES_HARDWARELEVEL_EXRAM_REALIZATION_TMS320F28335_EXRAM_INTERFACE_H_

#ifdef TMS320F28335

class TMS320F28335_ExRam : ExRamHardwareInterface {

public:
	int	ram_init(unsigned long Start);
	int	ram_erase(unsigned long	Start);
	int	ram_read(unsigned long	Start);
};

#endif

#endif /* USERFILES_HARDWARELEVEL_EXRAM_REALIZATION_TMS320F28335_EXRAM_INTERFACE_H_ */
