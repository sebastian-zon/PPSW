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

#define MAX_TOKEN_NR 3 //maksymalna dopuszczalna ilosc tokenow

#define MAX_KEYWORD_STRING_LTH 10 // mksymalna dlugosc komendy

struct Keyword {
enum KeywordCode eCode;
char cString[MAX_KEYWORD_STRING_LTH + 1];
};

#define MAX_KEYWORD_NR 3

extern unsigned char ucTokenNr;
extern struct Token asToken[MAX_TOKEN_NR];

unsigned char ucFindTokensInString (char *pcString);

enum  Result eStringToKeyword(char pcStr[],enum KeywordCode *peKeywordCode);

void DecodeTokens(void);

void DecodeMsg(char *pcString);