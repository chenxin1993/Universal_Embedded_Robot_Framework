/*
 * tms320f28335_exFlash_hardware.h
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#ifndef USERFILES_HARDWARELEVEL_EXFLASH_REALIZATION_TMS320F28335_EXFLASH_HARDWARE_H_
#define USERFILES_HARDWARELEVEL_EXFLASH_REALIZATION_TMS320F28335_EXFLASH_HARDWARE_H_

#ifdef TMS320F28335

// Definitions for the SST 39VF800A part

#define 	SST_ID                   	0x00BF         /* SST Manufacturer's ID code   */
#define 	SST_39VF400A             	0x2780         /* SST39VF400/SST39VF400A device code */
#define 	SST_39VF800A             	0x2781         /* SST39VF800/SST39VF800A device code */
#define		TIME_OUT_ERR				1
#define		VERIFY_ERR				 	2
#define		WRITE_OK					0
#define		ERASE_ERR				 	3
#define		ERASE_OK					0
#define		SECTOR_SIZE				 	0x800
#define		BLOCK_SIZE				 	0x8000

#define  execute_30us    delay_loop(1000)
#define  execute_150ms    delay_loop(5000000)

class TMS320F28335Hardware_ExFlash : ExFlashHardwareInterface {

public:
	int exInterrupt_init(void);
	void delay_loop(unsigned long x);
	unsigned int	ChipErase(void);
	unsigned int	FlashWrite(
			unsigned long	RamStart,
			unsigned long   RomStart,
			unsigned int	Length);
	void	FlashRead(
			unsigned long RamStart,
			unsigned long RomStart,
			unsigned int Length);
};

#endif

#endif /* USERFILES_HARDWARELEVEL_EXFLASH_REALIZATION_TMS320F28335_EXFLASH_HARDWARE_H_ */
