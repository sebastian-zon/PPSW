#include "led.h"

#include "keyboard.h"

void Delay(int iMiliseconds){
	unsigned int uiLoopCounter=0;
	
	for (uiLoopCounter=0; uiLoopCounter < (5500*iMiliseconds); uiLoopCounter++){}
}


enum LedState{LED_LEFT, LED_RIGHT};
unsigned char ucShiftCounter = 0;
enum LedState eLedState = LED_LEFT;

int main(){
	LedInit();
	KeyboardInit();
	while(1){
		switch (eLedState){
			case LED_LEFT:
				if(3 > ucShiftCounter){
					ucShiftCounter++;
					LedStepLeft();
				} else {
					eLedState = LED_RIGHT;
					ucShiftCounter--;
					LedStepRight();
				}
				break;
			case LED_RIGHT:
				if(0 < ucShiftCounter){
					ucShiftCounter--;
					LedStepRight();
				} else {
					eLedState = LED_LEFT;
					ucShiftCounter++;
					LedStepLeft();
				}
						break;
		}
		Delay(250);
	}
}

