#include "led.h"

#include "keyboard.h"

void Delay(int iMiliseconds){
	unsigned int uiLoopCounter=0;
	
	for (uiLoopCounter=0; uiLoopCounter < (5500*iMiliseconds); uiLoopCounter++){}
}


enum LedState{MOVING, STOPPED};
enum LedState eLedState = MOVING;

int main(){
	LedInit();
	KeyboardInit();
	while(1){
		switch (eLedState){
			case MOVING:
				if(BUTTON_0 == eKeyboardRead()){
					eLedState = STOPPED;
				} else {
					LedStepRight();
				}
				break;
			case STOPPED:
				if(BUTTON_1 == eKeyboardRead()){
					eLedState = MOVING;
					LedStepRight();
				}
				break;
		}
		Delay(250);
	}
}

