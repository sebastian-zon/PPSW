/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <string.h>

# undef NULL
# define NULL '\0'

#include "operacje_proste.h"

#include "konwersje.h"

#include "dekodowanie.h"


//  [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[testy]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

//  [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[operacje proste]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

void TestOf_CopyString(void){
    char cString1[] = "test1";
    char cString2[12] = "";
    
    printf("CopyString\n\n ");
    
    printf ("Test 1 - ");
    // sprawdzenie czy po skopiowaniu stringi sa takie same
    CopyString(cString1, cString2);
    if (EQUAL == eCompareString(cString1, cString2)) printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_eCompareString(void){
    char cString1[] = "string 0x01";
    char cStringSame[] = "string 0x01";
    char cStringShort[] = "string";
    char cStringLong[] = "string 0x123";
    char cStringDfferent[] = "stiing 0x01";
    
    printf("eCompareString\n\n");
    
    printf ("Test 1 - ");
    // sprawdzenie porównania takich samych łańcuchów
    if (EQUAL == eCompareString(cString1, cStringSame)) printf("OK\n\n"); else printf("Error\n\n");
    
    printf ("Test 2 - ");
    // sprawdzenie porównania z krótszym łańcuchem
    if (NOTEQUAL == eCompareString(cString1, cStringShort)) printf("OK\n\n"); else printf("Error\n\n");
    
    printf ("Test 3 - ");
    // sprawdzenie porównania z dłuższym łańcuchem
    if (NOTEQUAL == eCompareString(cString1, cStringLong)) printf("OK\n\n"); else printf("Error\n\n");
    
    printf ("Test 4 - ");
    // sprawdzenie porównania z innym łańcuchem
    if (NOTEQUAL == eCompareString(cString1, cStringDfferent)) printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_AppendString(void){
    char cString1[20] = "Ala ma ";
    char cString2[20] = "kota";
    char cStringEmpty[20] = "";
    
    printf("AppendString\n\n");
    
    printf ("Test 1 - ");
    // sprawdzenie dodawania dwóch niepustych łańcuchów
    AppendString(cString2, cString1);
    if (EQUAL == eCompareString(cString1, "Ala ma kota")) printf("OK\n\n"); else printf("Error\n\n");
    
    printf ("Test 2 - ");
    // sprawdzenie dodawania pustego łańcucha do niepustego łańcucha
    AppendString(cStringEmpty, cString1);
    if (EQUAL == eCompareString(cString1, "Ala ma kota")) printf("OK\n\n"); else printf("Error\n\n");
    
    printf ("Test 3 - ");
    // sprawdzenie dodawania niepustego łańcucha do pustego łańcucha
    AppendString(cString1, cStringEmpty);
    if (EQUAL == eCompareString(cStringEmpty, "Ala ma kota")) printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_ReplaceCharactersInString(void){
    char cString1[20] = "test stringow";
    char cOldChar = 't';
    char cNewChar = 'd';
    
    printf("ReplaceCharactersInString\n\n");
    
    printf ("Test 1 - ");
    // sprawdzenie zamiany znaków w łańcuchu
    ReplaceCharactersInString(cString1, cOldChar, cNewChar);
    if (EQUAL == eCompareString(cString1, "desd sdringow")) printf("OK\n\n"); else printf("Error\n\n");
}

//  [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[konwersje]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

void TestOf_UIntToHexStr(void){
    char cString1[7];
    
    printf("UIntToHexStr\n\n");
    
    printf ("Test 1 - ");
    // sprawdzenie konwersji liczby heksadecymalnej zawierajacej cyfry i litery
    UIntToHexStr(0x09FA, cString1);
    if (EQUAL == eCompareString(cString1, "0x09FA")) printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_eHexStringToUInt(void){
    char cStringGood[] = "0xFA09";
    char cStringBad1[] = "test";
    char cStringBad2[] = "0x12345";
    char cStringBad3[] = "0x";
    unsigned int uiResult;
    
    printf("eHexStringToUInt\n\n");
    
    printf ("Test 1 - ");
    // wykrycie niepoprawnych danych, litery zamiast liczby
    if ((OK == eHexStringToUInt(cStringGood, &uiResult)) && (64009 == uiResult)) printf("OK\n\n"); else printf("Error\n\n");
    
    printf ("Test 2 - ");
    // wykrycie niepoprawnych danych, litery zamiast liczby
    if (ERROR == eHexStringToUInt(cStringBad1, &uiResult)) printf("OK\n\n"); else printf("Error\n\n");
     
    printf ("Test 3 - ");
    // wykrycie niepoprawnych danych, za krotki łancuch
    if (ERROR == eHexStringToUInt(cStringBad2, &uiResult)) printf("OK\n\n"); else printf("Error\n\n");
    
    printf ("Test 4 - ");
    // wykrycie niepoprawnych danych, za długi łańcuch
    if (ERROR == eHexStringToUInt(cStringBad3, &uiResult)) printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_AppendUIntToString(void){
    char cString1[20] = "Test ";
    char cStringEmpty[20] = "";
    unsigned int uiNumber = 64009;
    
    
    printf("AppendUIntToString\n\n");
    
    printf ("Test 1 - ");
    // dodanie liczby do niepustego łańcucha
    AppendUIntToString(uiNumber, cString1);
    if (EQUAL == eCompareString(cString1, "Test 0xFA09")) printf("OK\n\n"); else printf("Error\n\n");

    printf ("Test 2 - ");
    // dodanie liczby do pustego łańcucha
    AppendUIntToString(uiNumber, cStringEmpty);
    if (EQUAL == eCompareString(cStringEmpty, "0xFA09")) printf("OK\n\n"); else printf("Error\n\n");
}

//  [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[dekodowanie]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

void TestOf_ucFindTokensInString(void){
    char cString1[] = "test three words";
    char cString2[] = "     ";
    char cString3[] = " test three  words";

    
    printf("ucFindTokensInString\n\n");
    
    printf ("Test 1 - ");
    // sprawdzenie poprawnego zliczania i wyszukiwania delimiterów
    ucTokenNr = ucFindTokensInString(cString1);
    if ((3 == ucTokenNr) && (EQUAL == eCompareString(asToken[0].uValue.pcString,"test three words")) && (EQUAL == eCompareString(asToken[1].uValue.pcString,"three words")) && (EQUAL == eCompareString(asToken[2].uValue.pcString,"words"))) printf("OK\n\n"); else printf("Error\n\n");

    printf ("Test 2 - ");
    // sprawdzenie dla łańcucha złożonego z samych delimiterów
    ucTokenNr = ucFindTokensInString(cString2);
    if (0 == ucTokenNr)printf("OK\n\n"); else printf("Error\n\n");

    printf ("Test 3 - ");
    // sprawdzenie poprawnego zliczania i wyszukiwania delimiterów przy dodatkowych delimiterach
    ucTokenNr = ucFindTokensInString(cString3);
    if ((3 == ucTokenNr) && (EQUAL == eCompareString(asToken[0].uValue.pcString,"test three  words")) && (EQUAL == eCompareString(asToken[1].uValue.pcString,"three  words")) && (EQUAL == eCompareString(asToken[2].uValue.pcString,"words"))) printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_eStringToKeyword(void){
    char cString1[] = "reset";
    char cString2[] = "reesett"; 
    enum KeywordCode eTest; 
    
    printf("eStringToKeyword\n\n");
    
    printf ("Test 1 - ");
    // sprawdzenie poprawności zamiany słowa kluczowego na enum
    if ((OK == eStringToKeyword(cString1, &eTest)) && RST == eTest) printf("OK\n\n"); else printf("Error\n\n");
    
    printf ("Test 2 - ");
    // sprawdzenie poprawności zamiany słowa, które nie jest kluczowe na enum
    if (ERROR == eStringToKeyword(cString2, &eTest)) printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_DecodeTokens(void){
    char cString1[] = "0x10 reset test";
    ucTokenNr = ucFindTokensInString(cString1);
    ReplaceCharactersInString(cString1, ' ', NULL);
    DecodeTokens();
  
    printf("DecodeTokens\n\n");
    
    printf("Test 1 - ");
    // sprawdzenie czy funkcja dziala poprawnie dla liczby
    if ((asToken[0].eType == NUMBER) && (0x10 == asToken[0].uValue.uiNumber)) printf("OK\n\n"); else printf("Error\n\n");

    printf("Test 2 - ");
    // sprawdzenie czy funkcja dziala poprawnie dla slowa kluczowego
    if ((asToken[1].eType == KEYWORD) && (RST == asToken[1].uValue.eKeyword)) printf("OK\n\n"); else printf("Error\n\n");
    
    printf("Test 3 - ");
    // sprawdzenie czy funkcja dziala poprawnie dla słowa
    if ((asToken[2].eType == STRING) && (&cString1[11] == asToken[2].uValue.pcString)) printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_DecodeMsg(void){
    char cString1[20] = "load 0x09FA now";
    
    printf("DecodeMsg\n\n");
    
    printf ("Test 1 - ");
    // sprawdzenie działania dla pełnej wiadomości
    DecodeMsg(cString1);
    if ((KEYWORD == asToken[0].eType) && (NUMBER == asToken[1].eType) && (STRING == asToken[2].eType) && (LD == asToken[0].uValue.eKeyword) && (0x09FA == asToken[1].uValue.uiNumber) && (EQUAL == eCompareString("now",asToken[2].uValue.pcString))) printf("OK\n\n"); else printf("Error\n\n");
}

//  [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[main]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

int main()
{
    printf("TESTY FUNKCJI DO OPERACJI NA STRINGACH \n\n\n");
    TestOf_CopyString();
    TestOf_eCompareString();
    TestOf_AppendString();
    TestOf_ReplaceCharactersInString();
    
    TestOf_UIntToHexStr();
    TestOf_eHexStringToUInt();
    TestOf_AppendUIntToString();
    

    printf("TESTY FUNKCJI DO DEKODOWANIA KOMUNIKATÓW\n\n\n");
    TestOf_ucFindTokensInString();
    TestOf_eStringToKeyword();
    TestOf_DecodeTokens();
    TestOf_DecodeMsg();
    return 0;
}