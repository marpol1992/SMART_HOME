/*
 * processing.h
 *
 * Created: 2015-11-04 21:05:58
 *  Author: marek
 */ 


#ifndef PROCESSING_H_
#define PROCESSING_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#define CRC_LENGHT		2
#define FRAME_LENGHT	5
// #define ID				buffer[1]
// #define ID_DATA			buffer[2]
#define DEVICE_MAX_ON		100
#define DEVICE_MIN_OFF		0

uint8_t buffer_count;
uint16_t CalcCRC16(uint8_t* data_array[], int data_lenght);
bool copy_data_to_buf(uint8_t* buffer,uint8_t data);
uint8_t  old_part_of_Byte(uint16_t licznik);
uint8_t  young_part_of_Byte(uint16_t licznik);
uint16_t parse_CRC(uint8_t old, uint8_t young);


#endif /* PROCESSING_H_ */