#include "led.h"

#include "keyboard.h"

void Delay(int iMiliseconds){
	unsigned int uiLoopCounter=0;
	
	for (uiLoopCounter=0; uiLoopCounter < (5500*iMiliseconds); uiLoopCounter++){}
}


enum LedState{STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};
enum LedState eLedState = STATE0;

int main(){
	LedInit();
	KeyboardInit();
	while(1){
		switch (eLedState){
			case STATE0:
				eLedState = STATE1;
				LedStepLeft();
				break;
			case STATE1:
				eLedState = STATE2;
				LedStepLeft();
				break;
			case STATE2:
				eLedState = STATE3;
				LedStepLeft();
				break;
			case STATE3:
				eLedState = STATE4;
				LedStepRight();
				break;
			case STATE4:
				eLedState = STATE5;
				LedStepRight();
				break;
			case STATE5:
				eLedState = STATE0;
				LedStepRight();
				break;
			default:
				break;
		}
		Delay(250);
	}
}

