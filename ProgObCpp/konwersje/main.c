//************************************************************************************
//************************************************************************************
//														**
//						PROCESOR LPC2129/01                             **
//      funkcjonalnosci:											**
//					- konwersja liczby na lancuch znakowy       		**
//					- konwersja lancucha znakowego na liczbe  			**
// 					- dodawanie liczby do lancucha znakowego 			**
//														** 
//************************************************************************************

#include <LPC21xx.H>

# define NULL '\0'

// ------------- -------------     UIntToHexStr     ------------- -------------
void UIntToHexStr (unsigned int uiValue, char pcStr[]){
	unsigned char ucNibbleCounter;
	unsigned char ucNibbleBuffer;
	
	pcStr[0] = '0';
	pcStr[1] = 'x';
	for(ucNibbleCounter = 0; ucNibbleCounter < 4; ucNibbleCounter++){
		ucNibbleBuffer = (uiValue>>(ucNibbleCounter*4)) & 0x000F;
		if(ucNibbleBuffer < 10){
		    pcStr[5-ucNibbleCounter] = ('0' + ucNibbleBuffer);
		} else {
		    pcStr[5-ucNibbleCounter] = ('A' + ucNibbleBuffer - 10);  
		}
	    
	}
	pcStr[6] = NULL;	
}

// ------------- -------------   eHexStringToUInt   ------------- -------------
enum Result {OK, ERROR};

enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){
	unsigned char ucCharCounter;
	unsigned char ucCurrChar;
	
	if(('0' != pcStr[0])||('x' != pcStr[1])||(NULL == pcStr[2])){
		return ERROR;
	}
	*puiValue = 0;
	for(ucCharCounter = 2; NULL != pcStr[ucCharCounter]; ucCharCounter++){
		ucCurrChar = pcStr[ucCharCounter];
		if(6 == ucCharCounter){
			return ERROR;
		} 
		if(('A' <= ucCurrChar)&&('F' >= ucCurrChar)){
			*puiValue = (*puiValue << 4)+(ucCurrChar-'A'+10);
		} else if(('0' <= ucCurrChar)&&('9' >= ucCurrChar)){
			*puiValue = (*puiValue << 4)+(ucCurrChar-'0');
		} else {
			return ERROR;
		}
	} return OK;	
}


// ------------- -------------  AppendUIntToString  ------------- -------------
void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]){
	unsigned char ucCharCounter;
	
	for(ucCharCounter = 0; NULL != pcDestinationStr[ucCharCounter]; ucCharCounter++) {}
	UIntToHexStr(uiValue, (pcDestinationStr+ucCharCounter));
}

unsigned int iCorrectOut=0;
char cCorrect[20]="0x25AF";
enum Result eCorrect;

unsigned int iTooLongOut=0;
char cTooLong[20]="0x2A3B4C";
enum Result eTooLongTest;

unsigned int iWrongCharOut=0;
char cWrongChar[20]="0x632aCD";
enum Result eWrongChar;

int main() {
	
  eCorrect = eHexStringToUInt(cCorrect,&iCorrectOut);
	
  eTooLongTest = eHexStringToUInt(cTooLong,&iTooLongOut);
	
  eWrongChar = eHexStringToUInt(cWrongChar,&iWrongCharOut);
	
	while(1);
}
