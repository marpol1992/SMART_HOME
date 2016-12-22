/*
 * SMART_HOME.c
 *
 * Created: 2015-11-03 21:31:36
 *  Author: marek
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <string.h>
#include <stdio.h>
#include "Oscylator_init.h"
#include "usart.h"
#include "processing_frame.h"
#include "ID_devices.h"
#include "Input_Output.h"

#define BUF_SIZE	10
#define SZPILKA_MS	1
#define MAX_FAZE_STEP	200

volatile uint8_t FAZE_STEP;
volatile uint8_t SYPIALNIA_MAIN_LIGHT_INTENSITY;
volatile uint8_t SYPIALNIA_NIGHT_LIGHT_INTENSITY;
volatile uint8_t SALON_MAIN_LIGHT_INTENSITY;

volatile uint8_t SYPIALNIA_MAIN_LIGHT_SET = 0;
volatile uint8_t SYPIALNIA_NIGHT_LIGHT_SET = 0;
volatile uint8_t SALON_MAIN_LIGHT_SET = 0;

volatile uint16_t DATA;
uint8_t buffer[BUF_SIZE];

static uint8_t convert_percent_to_step(uint8_t pr) {
	return (pr * (MAX_FAZE_STEP-1))/100;
}

void USART_init()
{
	PORTF_OUTSET=PIN2_bm;
	PORTF_DIRSET=PIN2_bm;
	
	PORTF_OUTCLR = PIN3_bm;
	PORTF_DIRCLR = PIN3_bm; //PC6 as RX
	

	// wlacz odbiornik oraz nadajnik USART
	USARTF0.CTRLB=USART_RXEN_bm | USART_TXEN_bm;
	// ramka 8 bitów, bez parzystoœci, 1 bit stopu
	USARTF0.CTRLC=USART_CHSIZE_8BIT_gc;
	usart_set_baudrate(&USARTF0, 115200, 32000000);
	// odblokuj przerwania odbiornika
	USARTF0.CTRLA=USART_RXCINTLVL_HI_gc;
	// zainicjuj DMA dla nadajnika USARTF0
}
ISR(USARTF0_RXC_vect)
{
	char znak[6] = { "kwiat" };
	USART_send(&USARTF0,znak);
	PORTD_OUTTGL = PIN0_bm;
	//PORTE_OUTTGL = PIN7_bm;
	if(copy_data_to_buf(buffer,USARTF0_DATA)){
		if(CalcCRC16(buffer,buffer_count-CRC_LENGHT) == parse_CRC(buffer[3],buffer[4])){
			switch(buffer[1]){
/*----------->*/case SYPIALNIA_MAIN_LIGHT:
						SYPIALNIA_MAIN_LIGHT_SET = convert_percent_to_step(buffer[2]);
				break;
/*----------->*/case SYPIALNIA_NIGHT_LIGHT:
						SYPIALNIA_NIGHT_LIGHT_SET = convert_percent_to_step(buffer[2]);
				break;
/*----------->*/case SYPIALNIA_BLINDS:
					if(buffer[2] == 100){
						SYPIALNIA_BLINDS_ON;
					}else
						SYPIALNIA_BLINDS_OFF;
				break;
/*----------->*/case SYPIALNIA_DEVICE_1:
					if(buffer[2] == 100){
						SYPIALNIA_DEVICE_1_ON;
					}else
						SYPIALNIA_DEVICE_1_OFF;
				break;
/*----------->*/case SYPIALNIA_DEVICE_2:
					if(buffer[2] == 100){
						SYPIALNIA_DEVICE_2_ON;
					}else
						SYPIALNIA_DEVICE_2_OFF;
				break;
/*----------->*/case SYPIALNIA_DEVICE_3:
					if(buffer[2] == 100){
						SYPIALNIA_DEVICE_3_ON;
					}else
						SYPIALNIA_DEVICE_3_OFF;
				break;
/*----------->*/case SALON_MAIN_LIGHT:
						SALON_MAIN_LIGHT_SET = convert_percent_to_step(buffer[2]);			
				break;
/*----------->*/case SALON_FAN:
					if(buffer[2] == 100){
						SALON_FAN_ON;
					}else
						SALON_FAN_OFF;
				break;
/*----------->*/case SALON_BLINDS:
					if(buffer[2] == 100){
						SALON_BLINDS_ON;
					}else
						SALON_BLINDS_OFF;
				break;
/*----------->*/case SALON_DEVICE_1:
					if(buffer[2] == 100){
					SALON_DEVICE_1_ON;
					}else
					SALON_DEVICE_1_OFF;
					break;
/*----------->*/case SALON_DEVICE_2:
					if(buffer[2] == 100){
						SALON_DEVICE_2_ON;
					}else
						SALON_DEVICE_2_OFF;
				break;
/*----------->*/case KUCHNIA_MAIN_LIGHT:
					if(buffer[2] == 100){
						KUCHNIA_MAIN_LIGHT_ON;
					}else
						KUCHNIA_MAIN_LIGHT_OFF;
				break;
/*----------->*/case KUCHNIA_LED:
					if(buffer[2] == 100){
						KUCHNIA_LED_ON;
					}else
						KUCHNIA_LED_OFF;
				break;
/*----------->*/case KUCHNIA_FAN:
					if(buffer[2] == 100){
						KUCHNIA_FAN_ON;
					}else
						KUCHNIA_FAN_OFF;
				break;
/*----------->*/case KUCHNIA_DEVICE_1:
					if(buffer[2] == 100){
						KUCHNIA_DEVICE_1_ON;
					}else
						KUCHNIA_DEVICE_1_OFF;
				break;
/*----------->*/case KUCHNIA_DEVICE_2:
					if(buffer[2] == 100){
						KUCHNIA_DEVICE_2_ON;
					}else
						KUCHNIA_DEVICE_2_OFF;
				break;
			}
		}
		buffer_count = 0;		
	}		
}

int main(void)
{
	
	PORTD.DIR			=  PIN0_bm ;
	/*------------------KONFIGURACJA WYJŒÆ-------------*/
	PORTA.DIR		=	PIN3_bm|PIN4_bm|PIN5_bm;
	/*PORTB.DIR		=	PIN0_bm|PIN1_bm|PIN2_bm|PIN3_bm|PIN4_bm|PIN5_bm|PIN6_bm|PIN7_bm;*/
	PORTC.DIR		=	PIN1_bm|PIN2_bm|PIN3_bm|PIN4_bm|PIN5_bm|PIN6_bm|PIN7_bm;
	PORTD.DIR		=	PIN0_bm|PIN1_bm|PIN2_bm|PIN3_bm|PIN4_bm|PIN5_bm|PIN6_bm|PIN7_bm;
	/*PORTE.DIR		=	PIN0_bm|PIN1_bm|PIN2_bm;*/
	/*PORTB.OUTSET	=   0;*/
	/*------------------------------------------------*/
	/*---------TIMER DO REGULACJI FAZOWEJ------------*/  
	TCC0.INTCTRLA   =   TC_OVFINTLVL_LO_gc;                                          
	TCC0.CTRLB      =	TC_WGMODE_NORMAL_gc;     // tryb normalny
	/*TCC0.CTRLA      =	TC_CLKSEL_DIV64_gc;   */   // ustawienie preskalera i uruchomienie timera
	#define TIMER_START TCC0.CTRLA		=   TC_CLKSEL_DIV1_gc;			//by³o 64
	#define TIMER_STOP  TCC0.CTRLA		=   TC_CLKSEL_OFF_gc;
	TCC0.PER	    =	1518;												//by³o 22//21066,491Hz b³¹d na poziomie 0,07% powinno byæ 21052,632
	/*------------------------------------------------*/
	/*---------PRZERWANIE ZEWNETRZNE-----------------*/
	PORTF.DIRCLR	=	PIN7_bm;
	PORTF.PIN7CTRL	=	PORT_OPC_PULLUP_gc|PORT_ISC_RISING_gc;
	PORTF.INT0MASK  =   PIN7_bm;               // pin F1 ma generowaæ przerwania INT0
	PORTF.INTCTRL   =   PORT_INT0LVL_LO_gc;    //// poziom HI dla przerwania INT0
	/*------------------------------------------------*/
	PMIC.CTRL		=   PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	sei();
	
	
	
	PORTE_DIR |= 0xFF;			// port D jako wyjœcia mikrokontrolera
	PORTE_OUTSET = 0xFF;		// port D - usatwienie stanu wysokiego
	init_osc32();
	USART_init();
	TIMER_START;
    while(1)
    {
		
    }
}

ISR(PORTF_INT0_vect) {// procedura przerwania INT0 portu F
	TIMER_STOP;
	SYPIALNIA_MAIN_LIGHT_OFF;
	SYPIALNIA_NIGHT_LIGHT_OFF;
	SALON_MAIN_LIGHT_OFF;
	FAZE_STEP						= MAX_FAZE_STEP;
	SYPIALNIA_MAIN_LIGHT_INTENSITY	= SYPIALNIA_MAIN_LIGHT_SET;
	SYPIALNIA_NIGHT_LIGHT_INTENSITY	= SYPIALNIA_NIGHT_LIGHT_SET;
	SALON_MAIN_LIGHT_INTENSITY		= SALON_MAIN_LIGHT_SET;
	TCC0.CNT = 0;
	TIMER_START;
}

ISR(TCC0_OVF_vect){
	if(SYPIALNIA_MAIN_LIGHT_INTENSITY  && FAZE_STEP == SYPIALNIA_MAIN_LIGHT_INTENSITY) SYPIALNIA_MAIN_LIGHT_ON;
	if(SYPIALNIA_NIGHT_LIGHT_INTENSITY && FAZE_STEP == SYPIALNIA_NIGHT_LIGHT_INTENSITY) SYPIALNIA_NIGHT_LIGHT_ON;
	if(SALON_MAIN_LIGHT_INTENSITY	   && FAZE_STEP == SALON_MAIN_LIGHT_INTENSITY) SALON_MAIN_LIGHT_ON;
	FAZE_STEP--;
}

