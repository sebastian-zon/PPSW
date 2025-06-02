#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"

enum LedState{LED_LEFT, STOPPED, LED_RIGHT};
enum LedState eLedState = STOPPED;

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
	}
}



int main (){	
	unsigned int iMainLoopCtr;
	
	LedInit();
	KeyboardInit();
	
	Timer0Interrupts_Init(20000,&Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}
