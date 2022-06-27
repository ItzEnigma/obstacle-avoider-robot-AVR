/*
 * QAlgorithm_Driver.h
 *
 * Created: 6/18/2022 6:32:57 PM
 *  Author: Taqi/Helal
 *	Contributors: Hosam/John/Ziad
 */ 


#ifndef QALGORITHM_DRIVER_H_
#define QALGORITHM_DRIVER_H_


#include "UltraSonic_Driver.h"
#include "Motors_Driver.h"

#include <avr/io.h>
#include <stdlib.h>


				// ----- QLearning Definitions ----- //
#define ACTIONS 4 // forward, left, right, rotate
#define STATES2 8 // the readings of the three ultrasonics 000 (no obstacles) to 111 (obstacles in each ultrasonic)
#define ALPHA 0.1f // the learning rate
#define GAMMA 0.5f // discount factor




				// ----- QLearning Functions ----- //
float Q_random();
float decay(float value);

struct max_val{
	float _max;
	float _max_ind;
};

float Q_max(float n1,float n2);



int getState();

void update2(int state, int next_s, int action, int state_reward);

void train2();
void train3();

void test2();
//void test();



#endif /* QALGORITHM_DRIVER_H_ */

