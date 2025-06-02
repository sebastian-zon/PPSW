#include <LPC21xx.H>

#include "servo.h"
#include "timer_interrupts.h"
#include "led.h"

enum ServoState {CALLIB, IDLE, IN_PROGRESS};
struct Servo {
	enum ServoState eState;
	unsigned int	uiCurrentPosition; 
	unsigned int uiDesiredPosition;
};

struct Servo sServo;


#define DET_bm (1<<10)

void DetectorInit(){
	IO0DIR &= ~(DET_bm);
}
enum DetectorState{INACTIVE, ACTIVE};

enum DetectorState eReadDetector(){
	if(0 == (IO0PIN & DET_bm)){
		return ACTIVE;
	} else { 
		return INACTIVE;
	}

}

void Automat(){
	switch (sServo.eState){
		case IDLE:
			if(sServo.uiCurrentPosition != sServo.uiDesiredPosition) {
				sServo.eState = IN_PROGRESS;
			}			
			break;
		case IN_PROGRESS:
			if(sServo.uiCurrentPosition > sServo.uiDesiredPosition) {
				LedStepLeft();
				sServo.uiCurrentPosition--;
			} else if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
				LedStepRight();
				sServo.uiCurrentPosition++;
			} else {
				sServo.eState = IDLE;
			}
			break;
		case CALLIB:
			if (ACTIVE == eReadDetector()){
				sServo.eState = IDLE;
				sServo.uiCurrentPosition = 0;
				sServo.uiDesiredPosition = 0;
			} else {
				LedStepLeft();
			}
			break;	
	}
}
void ServoCallib(void) {
	sServo.eState = CALLIB;
}
void ServoInit(unsigned int uiServoFrequency) {
	LedInit();
	DetectorInit();
	Timer0Interrupts_Init((1000000/uiServoFrequency),&Automat);
	ServoCallib();
}

void ServoGoTo(unsigned int uiPosition) {
	sServo.uiDesiredPosition = uiPosition;
}
