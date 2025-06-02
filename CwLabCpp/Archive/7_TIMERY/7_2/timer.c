#include <LPC21xx.H>

#include "timer.h"

#define TIMER0_EN_bm  0x1
#define TIMER0_RST_bm 0x2

void InitTimer0(void){
	T0TCR |= TIMER0_EN_bm;
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR |= TIMER0_RST_bm;
	T0TCR &= (~TIMER0_RST_bm);
	while(T0TC < 15*uiTime){}
}
