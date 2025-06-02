#include <LPC21xx.H>

#define LED0_bm 0x00010000


void Delay(int iMilisecond){
	unsigned int uiLoopCounter=0;
	for (uiLoopCounter=0; uiLoopCounter < (5500*iMilisecond); uiLoopCounter++){}
}

int main()
{

IO1DIR = LED0_bm;

	while(1)
		{	
		IO1SET = LED0_bm;
		Delay(50);
		IO1CLR = LED0_bm;
		Delay(50);
		}

}

