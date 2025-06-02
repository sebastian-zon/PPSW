#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000
#define BUT1_bm 0x00000010

void Delay(int iMilisecond){
	unsigned int uiLoopCounter=0;
	for (uiLoopCounter=0; uiLoopCounter < (5500*iMilisecond); uiLoopCounter++){}
}
void LedInit(){
	IO1DIR |= (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	IO1SET |= LED0_bm;
}

void LedOn(unsigned char ucLedIndeks){
	
	IO1CLR |= (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	switch (ucLedIndeks) {
		case 0:
			IO1SET |= LED0_bm;
			break;
		case 1:
			IO1SET |= LED1_bm;
			break;
		case 2:
			IO1SET |= LED2_bm;
			break;
		case 3:
			IO1SET |= LED3_bm;
			break;
	}
}

enum ButtonState {RELASED, PRESSED};
enum ButtonState eReadButton1(){
	if (BUT1_bm == (IO0PIN & BUT1_bm)) {
		return RELASED;
	}
	return PRESSED;
}


int main(){
	LedInit();
	while(1){
		switch (eReadButton1()){
			case PRESSED:
				LedOn(1);
				break;
			case RELASED:
				LedOn(0);
				break;
		}
	}
}

