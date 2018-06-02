/*
 * tms320f28335_exFlash_hardware.cpp
 *
 *  Created on: 2018年6月1日
 *      Author: xin
 */

#include <RobotSystemFiles/HardwareLevel/ExFlash/Realization/TMS320F28335/tms320f28335_exFlash_hardware.h>

#ifdef TMS320F28335

/********************************************
 *
 * 	函数说明: 来自 Exflash
 *
 ********************************************/

unsigned    int 	*ExFlashStart = (unsigned  int *)0x200000;
extern unsigned  	int	*DSPRamStart;  //RAML7前半部分
extern unsigned  	int	*DSPRamStart2;  //RAML7的后半部分
extern unsigned 	int	*ExRamStart;		// ExRam

/******************************************************************************************
* 函数名称    ：delay_loop
******************************************************************************************/
void ExFlash::delay_loop(unsigned long x)
{
	unsigned long      i;
    for (i = 0; i < x; i++) {}
}

/********************************************
 *
 * 	函数说明: 擦除 Flash
 *
 ********************************************/
unsigned int	ExFlash::chip_erase(void) {
	unsigned int	i,Data;
	unsigned long	TimeOut;
	*(ExFlashStart + 0x5555) = 0xAAAA;
	*(ExFlashStart + 0x2AAA) = 0x5555;
	*(ExFlashStart + 0x5555) = 0x8080;
	*(ExFlashStart + 0x5555) = 0xAAAA;
	*(ExFlashStart + 0x2AAA) = 0x5555;
	*(ExFlashStart + 0x5555) = 0x1010;
	i = 0;
	TimeOut = 0;
	execute_150ms;
	while(i<5)
	{
		Data = *(ExFlashStart +  0x3FFFF);
		if	(Data == 0xFFFF)	i++;
		else	i=0;
		if ( ++TimeOut>0x1000000)	return (TimeOutErr);
	}
	for	(i=0;i<0x4000;i++)
	{
		Data = *(ExFlashStart + i);
		if (Data !=0xFFFF)	return (EraseErr);
	}

	return  (EraseOK);

}


/********************************************
 *
 * 	函数说明: 写入 Flash
 *
 ********************************************/
unsigned int	ExFlash::write(
		unsigned long	RamStart,
		unsigned long   RomStart,
		unsigned int	Length) {
	unsigned long	i,TimeOut;
	unsigned int	Data1,Data2,j;
	for	(i=0;i<Length;i++)
	{
		*(ExFlashStart + 0x5555)= 0xAA;
		*(ExFlashStart + 0x2AAA)= 0x55;
		*(ExFlashStart + 0x5555) = 0xA0;
		*(ExFlashStart + RomStart + i) = *(ExRamStart + RamStart + i);
		TimeOut = 0;
		j=0;
		execute_30us;
	}

	while(j<5)
	{
		Data1 = *(ExFlashStart + RomStart + i);
		Data2 = *(ExFlashStart + RomStart + i);
		if	(Data1 == Data2)	j++;
		else	j=0;
		if ( ++TimeOut>0x1000000)	return (TimeOutErr);

	}


	for (i=0;i<Length;i++)
	{
		Data1 = *(ExFlashStart + RomStart +i);
		Data2 = *(ExRamStart + RamStart +i);
		if  (Data1 != Data2)	return (VerifyErr);
	}

	return  (WriteOK);

}


/********************************************
 *
 * 	函数说明: 读取 Flash
 *
 ********************************************/
void	FlashRead(
		unsigned long	RamStart,
		unsigned long  RomStart,
		unsigned int	Length) {
	unsigned long	i;
	unsigned int Temp;
	for	(i=0;i<Length;i++)
	{
		Temp =  (*((volatile	unsigned  int  *)(ExFlashStart + RomStart + i)));
		*(DSPRamStart + RamStart +i) = Temp;
	}
}

#endif

