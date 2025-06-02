#include "dekodowanie.h"
#include "konwersje.h"
#include "operacje_proste.h"

# define NULL '\0'

//  [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[dekodowanie]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

struct Token asToken[MAX_TOKEN_NR];

unsigned char ucTokenNr;

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