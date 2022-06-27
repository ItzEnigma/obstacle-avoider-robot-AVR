/*
 * UltraSonic_Driver.h
 *
 * Created: 6/18/2022 2:14:42 PM
 *  Author: John/Hosam
 *	Contributors: Taqi
 */ 


#ifndef ULTRASONIC_DRIVER_H_
#define ULTRASONIC_DRIVER_H_

#include "..\MACROS.h"

				// ----- Ultrasonic Drivers ----- //
void Ultrasonic_init();
u64 ReadUS(u08 x);


				// ----- Ultrasonic Definitions ----- //
#define  _ULTRASONIC_LEFT_TRIGGER 0
#define  _ULTRASONIC_MIDDLE_TRIGGER 1
#define  _ULTRASONIC_RIGHT_TRIGGER 2
#define Left_Ultrasonic 0
#define Middle_Ultrasonic 1
#define Right_Ultrasonic 2


#endif /* ULTRASONIC_DRIVER_H_ */