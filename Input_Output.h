/*
 * Input_Output.h
 *
 * Created: 2015-11-06 19:02:09
 *  Author: marek
 */ 
#include <avr/io.h>

#ifndef INPUT_OUTPUT_H_
#define INPUT_OUTPUT_H_
///////////////Definicje za³¹czania i wy³¹czania//////////////////////////
#define SYPIALNIA_MAIN_LIGHT_ON			PORTA.OUTSET = PIN5_bm
#define SYPIALNIA_MAIN_LIGHT_OFF		PORTA.OUTCLR = PIN5_bm
#define SYPIALNIA_MAIN_LIGHT_TGL		PORTA.OUTTGL = PIN5_bm

#define SYPIALNIA_NIGHT_LIGHT_ON		PORTA.OUTSET = PIN4_bm
#define SYPIALNIA_NIGHT_LIGHT_OFF		PORTA.OUTCLR = PIN4_bm

#define SYPIALNIA_BLINDS_ON				PORTD.OUTSET = PIN6_bm
#define SYPIALNIA_BLINDS_OFF			PORTD.OUTCLR = PIN6_bm

#define SYPIALNIA_DEVICE_1_ON			PORTD.OUTSET = PIN5_bm
#define SYPIALNIA_DEVICE_1_OFF			PORTD.OUTCLR = PIN5_bm

#define SYPIALNIA_DEVICE_2_ON			PORTD.OUTSET = PIN4_bm
#define SYPIALNIA_DEVICE_2_OFF			PORTD.OUTCLR = PIN4_bm
/*--------------------------------------------------------------------------------*/
#define SYPIALNIA_DEVICE_3_ON			PORTD.OUTSET = PIN3_bm
#define SYPIALNIA_DEVICE_3_OFF			PORTD.OUTCLR = PIN3_bm

#define SALON_MAIN_LIGHT_ON				PORTA.OUTSET = PIN3_bm
#define SALON_MAIN_LIGHT_OFF			PORTA.OUTCLR = PIN3_bm

#define SALON_FAN_ON					PORTD.OUTSET = PIN2_bm
#define SALON_FAN_OFF					PORTD.OUTCLR = PIN2_bm

#define SALON_BLINDS_ON					PORTD.OUTSET = PIN1_bm
#define SALON_BLINDS_OFF				PORTD.OUTCLR = PIN1_bm

#define SALON_DEVICE_1_ON				PORTD.OUTSET = PIN0_bm
#define SALON_DEVICE_1_OFF				PORTD.OUTCLR = PIN0_bm

#define SALON_DEVICE_2_ON				PORTC.OUTSET = PIN7_bm
#define SALON_DEVICE_2_OFF				PORTC.OUTCLR = PIN7_bm

#define KUCHNIA_MAIN_LIGHT_ON			PORTC.OUTSET = PIN6_bm
#define KUCHNIA_MAIN_LIGHT_OFF			PORTC.OUTCLR = PIN6_bm

#define KUCHNIA_LED_ON					PORTC.OUTSET = PIN5_bm
#define KUCHNIA_LED_OFF					PORTC.OUTCLR = PIN5_bm
/*-------------------------------------------------------------------------------*/
#define KUCHNIA_FAN_ON					PORTC.OUTSET = PIN4_bm
#define KUCHNIA_FAN_OFF					PORTC.OUTCLR = PIN4_bm

#define KUCHNIA_DEVICE_1_ON				PORTC.OUTSET = PIN3_bm
#define KUCHNIA_DEVICE_1_OFF			PORTC.OUTCLR = PIN3_bm

#define KUCHNIA_DEVICE_2_ON				PORTC.OUTSET = PIN2_bm
#define KUCHNIA_DEVICE_2_OFF			PORTC.OUTCLR = PIN2_bm

#endif /* INPUT_OUTPUT_H_ */