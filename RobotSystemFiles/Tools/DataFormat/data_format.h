/*
 * data_format.h
 *
 *  Created on: 2018年5月31日
 *      Author: xin-FFTAI
 */

#ifndef USERFILES_ALGORITHMS_DATAFORMAT_DATA_FORMAT_H_
#define USERFILES_ALGORITHMS_DATAFORMAT_DATA_FORMAT_H_

class DataFormat {

public:
	/* 8 bits operation */
	static unsigned char 	get_uint8_from_int8(char val);
	static char 			get_int8_from_uint8(unsigned char val);

	static unsigned char 	get_uint8_from_int8(char * val);
	static char 			get_int8_from_uint8(unsigned char * val);

	/* 16 bits operations */
	static int				get_int16_from_uint8(unsigned char lowVal, unsigned char highVal);
	static int				get_int16_from_int8(char lowVal, char highVal);
	static int				get_uint16_from_uint8(unsigned char lowVal, unsigned char highVal);
	static int				get_uint16_from_int8(char lowVal, char highVal);

	static int 				get_int16_from_uint16(unsigned int val);
	static unsigned int 	get_uint16_from_int16(int val);

	static int				get_int16_from_uint8(unsigned char * lowVal, unsigned char * highVal);
	static int				get_int16_from_int8(char * lowVal, char * highVal);
	static int				get_uint16_from_uint8(unsigned char * lowVal, unsigned char * highVal);
	static int				get_uint16_from_int8(char * lowVal, char * highVal);

	static int 				get_int16_from_uint16(unsigned int * val);
	static unsigned int 	get_uint16_from_int16(int * val);

	/* 16 bits and 32 bits operations */
	static long 			get_int32_from_uint16(unsigned int * lowVal, unsigned int * highVal);
	static long 			get_int32_from_int16(int * lowVal, int * highVal);
	static unsigned long 	get_uint32_from_uint16(unsigned int * lowVal, unsigned int * highVal);
	static unsigned long 	get_uint32_from_int16(int * lowVal, int * highVal);
	static float 			get_float_from_uint16(unsigned int * lowVal, unsigned int * highVal);
	static float 			get_float_from_int16(int * lowVal, int * highVal);

	/* 32 bits operations */
	static long 			get_int32_from_uint32(unsigned long * val);
	static unsigned long 	get_uint32_from_int32(long * val);
	static float 			get_float_from_uint32(unsigned long * val);
	static float 			get_float_from_int32(long * val);
	static unsigned long 	get_uint32_from_float(float * val);
	static long 			get_int32_from_float(float * val);
};

#endif /* USERFILES_ALGORITHMS_DATAFORMAT_DATA_FORMAT_H_ */
