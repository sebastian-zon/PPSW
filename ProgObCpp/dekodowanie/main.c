# define NULL '\0'
enum Result {OK, ERROR};

// ------------- ------------- 		 CopyString  	 ------------- ------------- 

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
// enum Result {OK, ERROR};

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




//************************************************************************************
//************************************************************************************
//														**
//						PROCESOR LPC2129/01                             **
//      funkcjonalnosci:											**
//					- dekodowanie        		**
//					- konwersja lancucha znakowego na liczbe  			**
// 					- dodawanie liczby do lancucha znakowego 			**
//														** 
//************************************************************************************

#include <LPC21xx.H>

# define NULL '\0'


enum KeywordCode { LD, ST, RST};

union TokenValue {
enum KeywordCode eKeyword; // jezeli KEYWORD
unsigned int uiNumber; // jezeli NUMBER
char * pcString; // jezeli STRING
};

enum TokenType { KEYWORD, NUMBER, STRING};

struct Token {
enum TokenType eType; // KEYWORD, NUMBER, STRING
union TokenValue uValue; // enum, unsigned int, char*
};

#define MAX_TOKEN_NR 3 //maksymalna dopuszczalna ilosc tokenów
struct Token asToken[MAX_TOKEN_NR];

unsigned char ucTokenNr;

#define MAX_KEYWORD_STRING_LTH 10 // mksymalna dlugosc komendy

struct Keyword {
enum KeywordCode eCode;
char cString[MAX_KEYWORD_STRING_LTH + 1];
};

#define MAX_KEYWORD_NR 3
struct Keyword asKeywordList[MAX_KEYWORD_NR]= {
{RST,"reset"},
{LD, "load" },
{ST, "store"}
};

// ------------- -------------  ucFindTokensInString   ------------- -------------
unsigned char ucFindTokensInString (char *pcString){
	enum CharType { TOKEN, DELIMITER};
	enum CharType eState = DELIMITER;
	unsigned char ucCharCounter = 0;
	unsigned char ucTokenCounter = 0;
	unsigned char ucBuffer;
	for(ucCharCounter = 0; ; ucCharCounter++) {
		ucBuffer = pcString[ucCharCounter];
		switch (eState) {
			case TOKEN:
				if (MAX_TOKEN_NR == ucTokenCounter) {
					return ucTokenCounter;
				} else if (NULL == ucBuffer){
					return ucTokenCounter;
				} else if(ucBuffer == ' ') {
					eState = DELIMITER;
				} else {
					eState = TOKEN;
				}
				break;
			case DELIMITER:
				if (NULL == ucBuffer){
					return ucTokenCounter;
				} else if(ucBuffer == ' ') {
					eState = DELIMITER;
				} else {
					eState = TOKEN;
					asToken[ucTokenCounter].uValue.pcString=(pcString+ucCharCounter);
					ucTokenCounter++;
				}
				break;
			}
	}
}
// ------------- -------------  eStingToKeyword   ------------- -------------

//enum Result {OK, ERROR};
enum  Result eStringToKeyword(char pcStr[],enum KeywordCode *peKeywordCode) {
	unsigned char ucKeywordCounter = 0;
	
	for(ucKeywordCounter = 0; MAX_KEYWORD_NR > ucKeywordCounter; ucKeywordCounter++) {
		if(EQUAL == eCompareString(pcStr, asKeywordList[ucKeywordCounter].cString)) {
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}  
	return ERROR;
}

// ------------- -------------  DecodeTokens  ------------- -------------
void DecodeTokens(void) {
	unsigned char ucTokenCounter = 0;
	struct Token *psCurrentToken;
	enum KeywordCode eTokenCode;
	unsigned int uiTokenValue;
	
	
	for (ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++) {
		psCurrentToken = &asToken[ucTokenCounter];
		
		if(OK == eStringToKeyword(psCurrentToken->uValue.pcString, &eTokenCode)) {
			psCurrentToken->eType=KEYWORD;
			psCurrentToken->uValue.eKeyword=eTokenCode;
		} else if (OK == eHexStringToUInt(psCurrentToken->uValue.pcString, &uiTokenValue)){
			psCurrentToken-> eType=NUMBER;
			psCurrentToken->uValue.uiNumber=uiTokenValue;
		} else {
			psCurrentToken->eType=STRING;
		}
	}	
}
// ------------- -------------	  DecodeMsg	  ------------- -------------
void DecodeMsg(char *pcString) {
	ucTokenNr = ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString, ' ', NULL);
	DecodeTokens();
}
//------------------------------------------------------------------------

char cString[] = "Ola reset 0x56";
int main() {
	DecodeMsg(cString);
	while(1){}
}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

