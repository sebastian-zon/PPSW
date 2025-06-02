#include "led.h"

#include "keyboard.h"

#include "timer.h"

int main(){
	LedInit();
	KeyboardInit();
	InitTimer0();
	while(1){
		LedStepLeft();
		InitTimer0Match0(250000);
		WaitOnTimer0Match0();
		
	}
}
