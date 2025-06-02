#include <LPC21xx.H>
int iLoopCtr;

void Delay()
{
	for (iLoopCtr=0 ; iLoopCtr<480000; iLoopCtr++)
		{
			
		}
}

int main()
{

IO1DIR = 0x00010000;
IO1SET = 0x00010000;
Delay();
IO1CLR = 0x00010000;

	while(1)
		{	
		IO1SET = 0x00010000;

		IO1CLR = 0x00010000;
		}

}

