//************************************************************************************
//************************************************************************************
//																																									**
//						PROCESOR LPC2129/01                             											**
//      funkcjonalnosci:																														**
//					- kopiowanie lancucha znakowego       																	**
//					- porównywanie lancuchów znakowych  																		**
// 					- dodawanie lancuchów znakowych  																				**
// 					- zamiana znaków w lancuchu  																						**
//																																									** 
//************************************************************************************

#include <LPC21xx.H>
#include "stdio.h" 

# undef NULL
# define NULL '\0'

// ------------- -------------    CopyString     ------------- ------------- 

void CopyString(char pcSource[], char pcDestination[]){

	unsigned char ucCharCounter = 0;
	
	for (ucCharCounter = 0; NULL != pcSource[ucCharCounter]; ucCharCounter++){
		pcDestination[ucCharCounter] = pcSource[ucCharCounter];
	}
	pcDestination[ucCharCounter] = NULL;
}



// ------------- -------------  eCompareString   ------------- ------------- 

enum Boolean {
	EQUAL = 1,
	NOTEQUAL = 0
};

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


char one[20] = "String";
char two[20] = "LongerString";
int main(){
	CopyString(one, two);
	
	while(1){
			
	}
		
}
