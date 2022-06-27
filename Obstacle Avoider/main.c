/*
 * Obstacle Avoider.c
 *
 * Created: 6/17/2022 12:49:48 PM
 * Author : hosam
 */ 


// CPU Clock Speed
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Drivers/Motors_Driver.h"
#include "Drivers/UltraSonic_Driver.h"
#include "Drivers/QAlgorithm_Driver.h"
#include "MACROS.h"


int main(void)
{
	Ultrasonic_init();	// initialize the ultrasonics
	train2();			// train the robot
	DDRB |= 1 << 5;     //starting the green LED
	PORTB |= 1 << 5;
	test2();			// infinite loop anyway
	_delay_ms(1000);
	while(1)
	{	
		
	}
}
