#include <LPC21xx.H>

#include "timer.h"

#define TIMER0_EN_bm  0x1
#define TIMER0_RST_bm 0x2

#define TIMER0_MCR_bm 0x5
#define TIMER0_T0IR_bm 0x1

void InitTimer0(void){
	T0TCR |= TIMER0_EN_bm;
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR |= TIMER0_RST_bm;
	T0TCR &= (~TIMER0_RST_bm);
	while(T0TC != 15*uiTime){}
}

void InitTimer0Match0(unsigned int iDelayTime){
	T0TCR |= TIMER0_RST_bm; //wpisanie 1 w celu resetu timera
	T0TCR &= (~TIMER0_RST_bm); // wpisanie 0 w celu zakonczenia resetu
	
	T0MR0 = (15*iDelayTime); // wpisanie ilosci cykli pozadanego opoznienia do match register
	T0MCR |= TIMER0_MCR_bm; // ustawienie aby timer sie zatrzymal, zresetowal i ustawil flage po osiagnieciu wartosci
	
	InitTimer0(); //wlaczenie timera
}

void WaitOnTimer0Match0(){
	while ((T0IR & TIMER0_T0IR_bm) == 0){}
	T0IR = TIMER0_T0IR_bm;
}
