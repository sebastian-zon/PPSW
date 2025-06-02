#include "led.h"

#include "keyboard.h"

void Delay(int iMiliseconds){
	unsigned int uiLoopCounter=0;
	
	for (uiLoopCounter=0; uiLoopCounter < (5500*iMiliseconds); uiLoopCounter++){}
}


enum ButtonState{PRESSED, RELEASED};
unsigned char ucShiftCounter = 0;
enum ButtonState eButtonState = RELEASED;

int main(){
	LedInit();
	KeyboardInit();
	while(1){
		switch (eButtonState){
			case RELEASED:
				if(BUTTON_0 == eKeyboardRead()){
					eButtonState = PRESSED;
					ucShiftCounter++;
					LedStepRight();
				}
				break;
			case PRESSED:
				if(4 == ucShiftCounter){
					eButtonState = RELEASED;
					ucShiftCounter = 0;
				} else {
					ucShiftCounter++;
					LedStepRight();
				}
				break;
		}
		Delay(250);
	}
}

