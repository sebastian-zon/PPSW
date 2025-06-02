#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"
#include <LPC21xx.H>

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


int main(){	
	unsigned int iMainLoopCtr;
	
	LedInit();
	KeyboardInit();
	DetectorInit();
	
	Timer0Interrupts_Init(20000,&Automat);

	while(1){
		switch (eKeyboardRead()){
			case BUTTON_0:
				sServo.eState = CALLIB;
				break;
			case BUTTON_1:
				sServo.uiDesiredPosition = 12;
				break;
			case BUTTON_2:
				sServo.uiDesiredPosition = 24;
				break;
			case BUTTON_3:
				sServo.uiDesiredPosition = 36;
				break;
			default:
				break;
		}
	 	iMainLoopCtr++;
	}
}
