/*
 * Motors_Driver.h
 *
 * Created: 6/17/2022 12:50:25 PM
 *  Author: John/hosam
 */ 


// Higher Prescaler >> Lower Frequency For The PWM ... Appropiate Frequency for the motor
// DC Motor Operate Appropriately in 5 - 100 HZ
// Therefore, the PWM Generated cycle's frequency can be calculated using the following formula:
//		F[gen] = ( F[osc] / [prescaler] * [Timer's Register Size] ) ---> For Timer0 with prescaler 1024:
//		F[gen] = (16,000,000) / (1024 * 256) ~= 61 Hz


#ifndef MOTORS_DRIVER_H_
#define MOTORS_DRIVER_H_

#include "..\MACROS.h"

				// ----- MCU Timers & Prescalings Available ----- //
#define MCU_NO_COUNTERS 3
#define TIMER_PRESCALER_LIMIT 7
#define TIMER_CLK_SRC_LIMIT 5


	// function pointer ... called funcPtr
	// and it's of type void and has void arguments
typedef void (*funcPtr) (void);

	// Empty function ... when there's no
	// proper timer operation chosen.
void empty_timer_func(void);

				// ----- Motor Movements ----- //
void motor_PWM(u08);
void Forward();
void Backward();
void Right();
void Left();
void Stop();
void Rotate();



#endif /* MOTORS_DRIVER_H_ */