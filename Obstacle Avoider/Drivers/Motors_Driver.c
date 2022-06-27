/*
 * Motors_Driver.c
 *
 * Created: 6/17/2022 1:03:31 PM
 *  Author: hosam
 */ 

// CPU Clock Speed
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include "util/delay.h"
#include "Motors_Driver.h"
#include "Motor_Types.h"


				// ----- Motor PWM Function ----- //
void motor_PWM(u08 duty_cycle)
{

// *** In Inverting Mode ... The Less the Duty Cycle ==> More the speed.
// -------------------- Configuration -------------------- //
	TCCR0A |= _TIMR_MODE_FASTPWM;
	TCCR0A |= _TIMR_OC0A_NONINVERTING_FASTPWM;
	TCCR0A |= _TIMR_OC0B_NONINVERTING_FASTPWM;
	TCCR0B |= _TIMR_CS_PRSC1024;

	// Port Direction
	DDRD |= (1<<5) | (1<<6) | (1<<0) | (1<<1);
	
	// Duty_Cycle = (val/255)*100.0
	
	OCR0A = ((duty_cycle*256)/100.0 - 1) +3; //left
	OCR0B = ((duty_cycle*256)/100.0 - 1); //right
/************************************************************************/
}

				// ----- Motor Forward Movement ----- //
void Forward(){
	motor_PWM(18);
	PORTD |= (1 << _MOTOR_DIRECTION_IN1) | (1 << _MOTOR_DIRECTION_IN3);
	PORTD &= ~((1 << _MOTOR_DIRECTION_IN2) | (1 << _MOTOR_DIRECTION_IN4));
}
				// ----- Motor Backward Movement ----- //
void Backward()
{
	PORTD &= ~((1 << _MOTOR_DIRECTION_IN1) | (1 << _MOTOR_DIRECTION_IN3));
	PORTD |= (1 << _MOTOR_DIRECTION_IN2) | (1 << _MOTOR_DIRECTION_IN4);
	
}
				// ----- Motor Right Movement ----- //
void Right()
{	
	motor_PWM(15);
	PORTD |= (1 << _MOTOR_DIRECTION_IN1) | (1 << _MOTOR_DIRECTION_IN4);
	PORTD &= ~((1 << _MOTOR_DIRECTION_IN2) | (1 << _MOTOR_DIRECTION_IN3));
	_delay_ms(250);
	Stop();
}
				// ----- Motor Left Movement ----- //
void Left()
{
	motor_PWM(15);
	PORTD |= (1 << _MOTOR_DIRECTION_IN2) | (1 << _MOTOR_DIRECTION_IN3);
	PORTD &= ~((1 << _MOTOR_DIRECTION_IN1) | (1 << _MOTOR_DIRECTION_IN4));
	_delay_ms(250);
	Stop();
}
				// ----- Motor Stop Movement ----- //
void Stop()
{
	PORTD &= ~((1 << _MOTOR_DIRECTION_IN2) | (1 << _MOTOR_DIRECTION_IN3));
	PORTD &= ~((1 << _MOTOR_DIRECTION_IN1) | (1 << _MOTOR_DIRECTION_IN4));
}

				// ----- Motor Rotate Movement ----- //
void Rotate()
{
	motor_PWM(15);
	// Backward
	PORTD &= ~((1 << _MOTOR_DIRECTION_IN1) | (1 << _MOTOR_DIRECTION_IN3));
	PORTD |= (1 << _MOTOR_DIRECTION_IN2) | (1 << _MOTOR_DIRECTION_IN4);
	_delay_ms(500);
	Stop();
	
	// Rotate
	PORTD |= (1 << _MOTOR_DIRECTION_IN1) | (1 << _MOTOR_DIRECTION_IN4);
	PORTD &= ~((1 << _MOTOR_DIRECTION_IN2) | (1 << _MOTOR_DIRECTION_IN3));
	_delay_ms(650);
	Stop();
}