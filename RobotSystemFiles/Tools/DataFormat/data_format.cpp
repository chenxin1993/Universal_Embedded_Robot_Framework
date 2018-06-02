/*
 * data_format.cpp
 *
 *  Created on: 2018年5月31日
 *      Author: xin-FFTAI
 */

#include <RobotSystemFiles/Tools/DataFormat/data_format.h>

/*********************************************
 *
 *	Function Statement:：
 *			From unsigned char To char
 *
 *********************************************/
unsigned char DataFormat::get_uint8_from_int8(char val) {

	unsigned char result;

	result = (unsigned char)val;

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From unsigned char To char
 *
 *********************************************/
unsigned char DataFormat::get_uint8_from_int8(char * val) {

	unsigned char result;

	result = *(unsigned char *)val;

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From char To unsigned char
 *
 *********************************************/
char DataFormat::get_int8_from_uint8(unsigned char val) {

	char result;

	result = (char)val;

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From char To unsigned char
 *
 *********************************************/
char DataFormat::get_int8_from_uint8(unsigned char * val) {

	char result;

	result = *(char *)val;

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From unsigned char To int
 *
 *********************************************/
int DataFormat::get_int16_from_uint8(unsigned char lowVal, unsigned char highVal) {

	int result;

	result = ((int)(lowVal) + ((int)(highVal) << 8));

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From char To int
 *
 *********************************************/
int DataFormat::get_int16_from_int8(char lowVal, char highVal) {

	int result;

	result = ((int)(lowVal) + ((int)(highVal) << 8));

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From unsigned char To int
 *
 *********************************************/
int DataFormat::get_uint16_from_uint8(unsigned char lowVal, unsigned char highVal) {

	unsigned int result;

	result = ((unsigned int)(lowVal) + ((unsigned int)(highVal) << 8));

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From char To int
 *
 *********************************************/
int DataFormat::get_uint16_from_int8(char lowVal, char highVal) {

	int result;

	result = ((int)(lowVal) + ((int)(highVal) << 8));

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From char To int
 *
 *********************************************/
int DataFormat::get_int16_from_uint16(unsigned int val) {

	int result;

	result = (int)(val);

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From char To int
 *
 *********************************************/
unsigned int DataFormat::get_uint16_from_int16(int val) {

	unsigned int result;

	result = (unsigned int)(val);

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From char To int
 *
 *********************************************/
int DataFormat::get_int16_from_uint8(unsigned char * lowVal, unsigned char * highVal) {

	int result;

	result = (*(int *)(lowVal) + (*(int *)(highVal) << 8));

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From char To int
 *
 *********************************************/
int DataFormat::get_int16_from_int8(char * lowVal, char * highVal) {

	int result;

	result = (*(int *)(lowVal) + (*(int *)(highVal) << 8));

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From char To int
 *
 *********************************************/
int DataFormat::get_uint16_from_uint8(unsigned char * lowVal, unsigned char * highVal) {

	int result;

	result = (*(int *)(lowVal) + (*(int *)(highVal) << 8));

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From char To int
 *
 *********************************************/
int DataFormat::get_uint16_from_int8(char * lowVal, char * highVal) {

	int result;

	result = (*(int *)(lowVal) + (*(int *)(highVal) << 8));

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From char To int
 *
 *********************************************/
int DataFormat::get_int16_from_uint16(unsigned int * val) {

	int result;

	result = *(int *)(val);

	return result;
}

/*********************************************
 *
 *	Function Statement:：
 *			From char To int
 *
 *********************************************/
unsigned int DataFormat::get_uint16_from_int16(int * val) {

	unsigned int result;

	result = *(unsigned int *)(val);

	return result;
}



