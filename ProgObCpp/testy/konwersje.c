#include "konwersje.h"

# define NULL '\0'

//  [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[konwersje]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

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
