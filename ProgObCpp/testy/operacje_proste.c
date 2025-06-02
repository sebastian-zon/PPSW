#include "operacje_proste.h"


# define NULL '\0'

//  [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[operacje proste]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


// ------------- -------------    CopyString     ------------- ------------- 

void CopyString(char pcSource[], char pcDestination[]){

	unsigned char ucCharCounter = 0;
	
	for (ucCharCounter = 0; NULL != pcSource[ucCharCounter]; ucCharCounter++){
		pcDestination[ucCharCounter] = pcSource[ucCharCounter];
	}
	pcDestination[ucCharCounter] = NULL;
}

// ------------- -------------  eCompareString   ------------- ------------- 
enum Boolean eCompareString(char pcStr1[], char pcStr2[]){
		
	unsigned char ucCharCounter = 0;
	
	for (ucCharCounter = 0; (NULL != pcStr1[ucCharCounter]) || (NULL != pcStr2[ucCharCounter]); ucCharCounter++){
		if (pcStr1[ucCharCounter] != pcStr2[ucCharCounter]){
			return NOTEQUAL;
		}
	}
	return EQUAL;
}

// ------------- -------------   AppendString    ------------- ------------- 

void AppendString (char pcSourceStr[],char pcDestinationStr[]) {
		
	unsigned char ucCharCounter = 0;
	
	for(ucCharCounter = 0; NULL != pcDestinationStr[ucCharCounter]; ucCharCounter++) {}
	CopyString(pcSourceStr, (pcDestinationStr + ucCharCounter));
}

// ------------- ------------- ReplaceCharacters ------------- ------------- 

void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar) {
	
	unsigned char ucCharCounter = 0;
	
	for (ucCharCounter = 0; NULL != pcString[ucCharCounter]; ucCharCounter++) {
		if(cOldChar == pcString[ucCharCounter]){
			pcString[ucCharCounter] = cNewChar;
		}
	}
}