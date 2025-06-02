#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000
#define BUT0_bm 0x00000010
#define BUT1_bm 0x00000040
#define BUT2_bm 0x00000020
#define BUT3_bm 0x00000080

void Delay(int iMiliseconds){
	unsigned int uiLoopCounter=0;
	for (uiLoopCounter=0; uiLoopCounter < (5500*iMiliseconds); uiLoopCounter++){}
}
void LedInit(){
	IO1DIR |= (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	IO1CLR = (LED1_bm | LED2_bm | LED3_bm);
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks){
	
	IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	switch (ucLedIndeks) {
		case 0:
			IO1SET = LED0_bm;
			break;
		case 1:
			IO1SET = LED1_bm;
			break;
		case 2:
			IO1SET = LED2_bm;
			break;
		case 3:
			IO1SET = LED3_bm;
			break;
	}
}


enum eStepDir {Left, Right};

void LedStep(enum eStepDir eDirection){
	static unsigned char ucStepIndex;
	if(Left == eDirection){
		ucStepIndex = ((ucStepIndex+1)%4);
	} else {
		ucStepIndex = ((ucStepIndex-1)%4);
	}
	LedOn(ucStepIndex);
}
void LedStepLeft() {
	LedStep(Left);
}
void LedStepRight() {
	LedStep(Right);
}

void KeyboardInit(){
	IO0DIR &= ((~BUT0_bm) & (~BUT1_bm) & (~BUT2_bm) & (~BUT3_bm));
}

enum KeyboardState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

enum KeyboardState eKeyboardRead(){
	if(0 == (IO0PIN & BUT0_bm)){
		return BUTTON_0;
	} else if(0 == (IO0PIN & BUT1_bm)){
		return BUTTON_1;
	} else if(0 == (IO0PIN & BUT2_bm)){
		return BUTTON_2;
	} else if(0 == (IO0PIN & BUT3_bm)){
		return BUTTON_3;
	} else {
		return RELASED;
	}
}


int main(){
	LedInit();
	KeyboardInit();;
	while(1){
		switch (eKeyboardRead()){
			case BUTTON_1:
				LedStepRight();
				Delay(200);
				break;
			case BUTTON_2:
				LedStepLeft();
				Delay(200);
				break;
			default:
				break;
		}
	}
}

