#include "led.h"

#include "keyboard.h"

void Delay(int iMiliseconds){
	unsigned int uiLoopCounter=0;
	
	for (uiLoopCounter=0; uiLoopCounter < (5500*iMiliseconds); uiLoopCounter++){}
}


enum LedState{LED_LEFT, STOPPED, LED_RIGHT};
enum LedState eLedState = STOPPED;

int main(){
	LedInit();
	KeyboardInit();
	while(1){
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
		Delay(100);
	}
}

