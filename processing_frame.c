/*
 * processing.c
 *
 * Created: 2015-11-04 21:06:41
 *  Author: marek
 */ 
#include "processing_frame.h"

bool copy_data_to_buf(uint8_t* buffer,uint8_t data){
	buffer[buffer_count] = data;
	buffer_count++;
	if(buffer_count >=FRAME_LENGHT){
		return true;
	}
	return false;
}
	
	
uint16_t CalcCRC16(uint8_t* data_array[], int data_lenght)
{
	uint16_t crc = 0xFFFF;
	uint8_t data[data_lenght];
	memcpy(data,data_array,data_lenght);
	for (int i = 0; i < data_lenght; i++)
	{
		crc ^= (uint16_t)(data[i] << 8);
		for (int j = 0; j < 8; j++)
		{
			if ((crc & 0x8000) > 0)
			crc = (uint16_t)((crc << 1) ^ 0x1021);
			else
			crc <<= 1;
		}
	}
	return crc;
}


uint8_t  old_part_of_Byte(uint16_t licznik){

	
	return(licznik>>8);
}

uint8_t  young_part_of_Byte(uint16_t licznik){

	return (licznik & 0XFF);
}


uint16_t parse_CRC(uint8_t old, uint8_t young){
	uint16_t mask = 0xFFFF;
 return ((mask & old)<<8) | young;
}