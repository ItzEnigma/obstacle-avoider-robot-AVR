/*
 * QAlgorithm.c
 *
 * Created: 6/18/2022 6:35:27 PM
 *  Author: Taqi/Helal
 *	Contributors: Hosam/John/Ziad
 */ 


// CPU Clock Speed
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "QAlgorithm_Driver.h"
#include <util/delay.h>

int episodes = 100, currentState = 0, nextState = 0, actionID = 0;
float reward;
bool action_taken = false;
float epsilon = 1.0;
float new_Q, Old_Q, max_Q;


float Q2[STATES2][ACTIONS] = {
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0}
};
float rewards2[STATES2][ACTIONS]={
	{10.0, 2.0, 2.0, -10},
	{-2.0, 10.0,-10.0, -10.0},
	{-10.0, 10.0, 10.0, -2.0},
	{-10.0, 10.0, -10.0, -2.0},
	{2.0, -10.0, 10.0, -10.0},
	{10.0, -10.0, -10.0, -2.0},
	{-10.0, -10.0, 10.0, -2.0},
	{-10.0, -10.0, -10.0, 10.0}
};

// By Helal

float Q_random(){
	return (float)(((rand()%100))/100.0);
}

float decay(float value){
	return (value*0.99);
}

float Q_max(float n1,float n2){
	if(n1 >= n2)
		return n1;
	return n2;
}

// By Helal
struct max_val getMax(int next_s){
	struct max_val x={-10000,-1};
	for (int i = 0; i < ACTIONS; ++i) {
		x._max = Q_max(x._max, Q2[next_s][i]);
		if(x._max == Q2[next_s][i])
		x._max_ind=i;
	}
	return x;
}

int getState()
{
	int R = ReadUS(_ULTRASONIC_RIGHT_TRIGGER);
	_delay_ms(1);
	int L = ReadUS(_ULTRASONIC_LEFT_TRIGGER);
	_delay_ms(1);
	int M = ReadUS(_ULTRASONIC_MIDDLE_TRIGGER);

	if ((L>15) && (M>20) && (R>15))
		return 0;
	else if ((L>15) && (M>20) && (R<=15))
		return 1;
	else if ((L>15) && (M<=20) && (R>15))
		return 2;
	else if ((L>15) && (M<=20) && (R<=15))
		return 3;
	else if ((L<=15) && (M>20) && (R>15))
		return 4;
	else if ((L<=15) && (M>20) && (R<=15))
		return 5;
	else if ((L<=15) && (M<=20) && (R>15))
		return 6;
	else if ((L<=15) && (M<=20) && (R<=15))
		return 7;
	else 
		return -1;
}

void update2(int state, int next_s, int action, int state_reward){
	Old_Q = Q2[state][action];
	max_Q = getMax(next_s)._max;
	new_Q = ((1.0f - ALPHA)*Old_Q + ALPHA*(state_reward + GAMMA*max_Q));
	Q2[state][action] = new_Q;
	// printf("%f\t%f\t%f\n",Old_Q, max_Q, new_Q);
}

void train2(){
	int ultra;
	DDRB |= 1 << 4;
	PORTB |= 1 << 4;
	for (int i = 0; i < 200; i++) {
		action_taken = false;
		ultra = 1000;
		while(1)
		{
			Forward();
			ultra = ReadUS(_ULTRASONIC_MIDDLE_TRIGGER);
			if( ultra <= 20)
			{
				Stop();
				nextState = (currentState + 1) % STATES2 ;
				break;
			}
		}
		
		float prob = Q_random();
		if(prob <= epsilon){
			actionID = rand() % ACTIONS;
		}
		else
			actionID = getMax(currentState)._max_ind;
		reward = rewards2[currentState][actionID];
		update2(currentState, nextState, actionID, reward);
		currentState = nextState;
		epsilon = decay(epsilon);
		_delay_ms(100);
	}
	PORTB &= ~(1<<4); //close the LED
}

void train3(){
	int F,L,R;
	DDRB |= 1 << 4;
	PORTB |= 1 << 4;
	for (int i = 0; i < 200; i++) {
		action_taken = false;
		while(1)
		{
			Forward();
			F = ReadUS(_ULTRASONIC_MIDDLE_TRIGGER);
			L = ReadUS(_ULTRASONIC_LEFT_TRIGGER);
			R = ReadUS(_ULTRASONIC_RIGHT_TRIGGER);
			if( F <= 20 || L<=15 || R<=15)
			{
				Stop();
				nextState = getState();
				break;
			}
		}

		float prob = Q_random();
		if(prob <= epsilon){
			actionID = rand() % ACTIONS;
		}
		else
		actionID = getMax(currentState)._max_ind;
		switch (actionID)
		{
			case 0 : Forward(); break;
			case 1 : Left(); break;
			case 2 : Right(); break;
			case 3 : Rotate(); break;
		}
		_delay_ms(1000);
		nextState = getState();
		reward = rewards2[currentState][actionID];
		update2(currentState, nextState, actionID, reward);
		epsilon = decay(epsilon);
		_delay_ms(100);
	}
	PORTB &= ~(1<<4);
}


void test2()
	{
		while(true)
		{
			actionID = getMax(getState())._max_ind;
			if(actionID == 0){ //forward
				Forward(); 
			}
			else if(actionID == 1){ // left
				Left(); 
				//_delay_ms(1000);
			}
			else if(actionID == 2){ // right
				Right();
				//_delay_ms(3000);
			}
			else if(actionID == 3) // rotate
			{
				Rotate();
			}
			else  { //not a case
				Stop();
				_delay_ms(3000);
			}
		}	
}

