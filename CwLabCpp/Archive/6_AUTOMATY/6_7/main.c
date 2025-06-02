#include "led.h"

#include "keyboard.h"

void Delay(int iMiliseconds){
	unsigned int uiLoopCounter=0;
	
	for (uiLoopCounter=0; uiLoopCounter < (5500*iMiliseconds); uiLoopCounter++){}
}


enum LedState{LED_LEFT, STOPPED, LED_RIGHT, BLINKING};
enum LedState eLedState = STOPPED;
unsigned char ucBlinkCounter = 0;

int main(){
	LedInit();
	KeyboardInit();
	while(1){
		switch (eLedState){
			case LED_LEFT:
				if(BUTTON_1 == eKeyboardRead()){
					eLedState = STOPPED;
				} else if(BUTTON_3 == eKeyboardRead()){
					eLedState = BLINKING;
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
			case BLINKING:
				if(10 == ucBlinkCounter){
					ucBlinkCounter = 0;
					eLedState = LED_RIGHT;LedStepRight();
				} else {
					if(ucBlinkCounter%2){
						LedOn(5);
				} else {
						LedOn(0);
				}
				ucBlinkCounter++;
			}
		}
		Delay(100);
	}
}
