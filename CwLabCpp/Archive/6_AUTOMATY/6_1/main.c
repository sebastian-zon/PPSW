#include "led.h"

#include "keyboard.h"

void Delay(int iMiliseconds){
	unsigned int uiLoopCounter=0;
	
	for (uiLoopCounter=0; uiLoopCounter < (5500*iMiliseconds); uiLoopCounter++){}
}


enum LedState{LED_LEFT, LED_RIGHT};
enum LedState eLedState = LED_LEFT;

int main(){
	LedInit();
	KeyboardInit();
	while(1){
		switch (eLedState){
			case LED_LEFT:
				eLedState = LED_RIGHT;
				LedStepLeft();
				break;
			case LED_RIGHT:
				LedStepRight();
				eLedState = LED_LEFT;
				break;
			default:
				break;
		}
		Delay(250);
	}
}

