#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"
#include <LPC21xx.H>

enum LedState{LED_LEFT, STOPPED, LED_RIGHT, CALLIB};
enum LedState eLedState = CALLIB;

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
	switch (eLedState){
		case LED_LEFT:
			if(BUTTON_1 == eKeyboardRead()){
				eLedState = STOPPED;
			} else {
				LedStepLeft();
			}
			break;
		case STOPPED:
			if(BUTTON_0 == eKeyboardRead()){
				eLedState = LED_LEFT;
				LedStepLeft();
			} else if(BUTTON_2 == eKeyboardRead()){
				eLedState = LED_RIGHT;
				LedStepRight();
			}
			break;
		case LED_RIGHT:
			if(BUTTON_1 == eKeyboardRead()){
				eLedState = STOPPED;
			} else {
				LedStepRight();
			}
			break;
		case CALLIB:
			if (ACTIVE == eReadDetector()){
				eLedState = STOPPED;
			} else {
				LedStepLeft();
			}
			break;
			
	}
}


int main(){	
	
	LedInit();
	KeyboardInit();
	DetectorInit();
	
	Timer0Interrupts_Init(20000,&Automat);

	while(1){
	}
}
