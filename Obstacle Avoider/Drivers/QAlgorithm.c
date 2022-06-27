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

int episodes = 200, currentState = 0, nextState = 0, actionID = 0;
float reward;
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

int getState() // read the three ultrasonics 
{
	int R = ReadUS(_ULTRASONIC_RIGHT_TRIGGER);
	_delay_ms(1);
	int L = ReadUS(_ULTRASONIC_LEFT_TRIGGER);
	_delay_ms(1);
	int M = ReadUS(_ULTRASONIC_MIDDLE_TRIGGER);

	if ((L>15) && (M>20) && (R>15)) //000
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
	else if ((L<=15) && (M<=20) && (R<=15)) //111
		return 7;
	else 
		return -1;
}

void update2(int state, int next_s, int action, int state_reward){
	Old_Q = Q2[state][action];
	max_Q = getMax(next_s)._max;
	new_Q = ((1.0f - ALPHA)*Old_Q + ALPHA*(state_reward + GAMMA*max_Q));
	Q2[state][action] = new_Q;
}

void train2(){
	int ultra;
	DDRB |= 1 << 4;
	PORTB |= 1 << 4;
	for (int i = 0; i < episodes; i++) {
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

void train3(){ //interacting with the actual environment given to the robot
	
	DDRB |= 1 << 4;
	PORTB |= 1 << 4; //enable the blue LED (training phase)
	
	for (int i = 0; i < episodes; i++) {
		Forward();// make the robot move forward for each episode
		do{
			currentState = getState(); // read the current state
		} while (currentState == 0); //move till an obstacle is detected
		
		float prob = Q_random(); //getting a probability for the explore/exploit action
		
		if(prob <= epsilon) //explore
			actionID = rand() % ACTIONS;
		else //exploit
			actionID = getMax(currentState)._max_ind;
		
		switch (actionID) //take the action
		{
			case 0 : Forward(); break;
			case 1 : Left(); break;
			case 2 : Right(); break;
			case 3 : Rotate(); break;
		}
		
		nextState = getState(); // reading the new state
		_delay_ms(200); //delay to make sure the action is taken successfully
		Stop();//stop the robot
		reward = rewards2[currentState][actionID]; //getting the reward
		update2(currentState, nextState, actionID, reward); //updating q table
		epsilon = decay(epsilon); // decay the epsilon (more toward exploiting)
		_delay_ms(500);
	}
	PORTB &= ~(1<<4); //close the blue LED
	DDRB |= 1 << 5;	  // enable the GREEN LED
	PORTB |= 1 << 5;  // enable the GREEN LED
}


void test2()
	{
		while(1)
		{
			//while(getState() == 0) Forward(); can be used with train 3
			
			actionID = getMax(getState())._max_ind;
			
			if(actionID == 0){ //forward
				Forward(); 
			}
			else if(actionID == 1){ // left
				Left(); 
			}
			else if(actionID == 2){ // right
				Right();
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

