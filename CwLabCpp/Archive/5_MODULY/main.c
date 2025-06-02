#include "led.h"

#include "keyboard.h"

void Delay(int iMiliseconds){
	unsigned int uiLoopCounter=0;
	
	for (uiLoopCounter=0; uiLoopCounter < (5500*iMiliseconds); uiLoopCounter++){}
}

int main(){
	LedInit();
	KeyboardInit();
	while(1){
		switch (eKeyboardRead()){
			case BUTTON_1:
				LedStepRight();
				break;
			case BUTTON_2:
				LedStepLeft();
				break;
			default:
				break;
		}
		Delay(200);
	}
}

