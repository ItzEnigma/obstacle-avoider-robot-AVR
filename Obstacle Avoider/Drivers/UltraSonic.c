/*
 * UltraSonic.c
 *
 * Created: 6/18/2022 2:14:02 PM
 *  Author: John/Hosam
 *	Contributors: Taqi
 */ 


// CPU Clock Speed
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "UltraSonic_Driver.h"
#include "Motor_Types.h"


				// ----- Ultrasonic Initialization Configuration ----- //
void Ultrasonic_init()
{
	// Pins Direction
	DDRC |= (1 << _ULTRASONIC_LEFT_TRIGGER) | (1 << _ULTRASONIC_MIDDLE_TRIGGER) |(1 << _ULTRASONIC_RIGHT_TRIGGER);
		// x = 0 for left sensor  (trigger pin on PORTC0)
		// x = 1 for mid sensor   (trigger pin on PORTC1)
		// x = 2 for right sensor (trigger pin on PORTC2)
}


				// ----- Ultrasonic Distance Measurement ----- //
u64 ReadUS(u08 x)
{
	u64 count = 0;					// Time Counts Variable
	u64 distance = 0;				// Distance Between Ultrasonic & Obstacle
	//choose which Us who will receive  the trigger   
	if(x == 0){
		PORTC |= (1<<0); //trigger pin 0 port c for 10 us for LUS
		_delay_us(10);
		PORTC &= ~(1<<0);
	}
	else if(x == 1){
		PORTC |= (1<<1); //trigger pin 1 port c for 10 us for MUS
		_delay_us(10);
		PORTC &= ~(1<<1);
	}
	else if (x ==2){
		PORTC |= (1<<2); //trigger pin 2 port c for 10 us for RUS
		_delay_us(10);
		PORTC &= ~(1<<2);
	}
	//wait till the one of ECHO arrived
	while((PINB & (1<<x)) >> x == 0);
	//calculate the ECHO time
	while((PINB & (1<<x)) >>x == 1){
		// Converting The Counts To Microseconds Variable
		_delay_us(1);
		count++;
	}
	distance = count/9;					// Distance Equation.
	return distance;
}
