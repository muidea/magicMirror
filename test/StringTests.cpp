/******************************************************************
*
* uHTTP for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <HTTP.h>
#include "StringTests.h"

using namespace std;
using namespace CyberLink;

void CyberLinkTest::TestValue2String()
{
  std::string buf;
    
  if (strcmp(Integer2String(1, buf), "1") != 0) {
	  std::cout << "Integer2String failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Integer2String(9, buf), "9") != 0) {
	  std::cout << "Integer2String failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Integer2String(10, buf), "10") != 0) {
	  std::cout << "Integer2String failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Integer2String(15, buf), "15") != 0) {
	  std::cout << "Integer2String failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Integer2String(255, buf), "255") != 0) {
	  std::cout << "Integer2String failed, :" << __LINE__ << std::endl;
  }

  if (strcmp(Long2String(1, buf), "1") != 0) {
	  std::cout << "Long2String failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Long2String(9, buf), "9") != 0) {
	  std::cout << "Long2String failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Long2String(10, buf), "10") != 0) {
	  std::cout << "Long2String failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Long2String(15, buf), "15") != 0) {
	  std::cout << "Long2String failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Long2String(255, buf), "255") != 0) {
	  std::cout << "Long2String failed, :" << __LINE__ << std::endl;
  }

  if (strcmp(Sizet2String(1, buf), "1") != 0) {
	  std::cout << "Sizet2String failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Sizet2String(9, buf), "9") != 0) {
	  std::cout << "Sizet2String failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Sizet2String(10, buf), "10") != 0) {
	  std::cout << "Sizet2String failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Sizet2String(15, buf), "15") != 0) {
	  std::cout << "Sizet2String failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Sizet2String(255, buf), "255") != 0) {
	  std::cout << "Sizet2String failed, :" << __LINE__ << std::endl;
  }
}

void CyberLinkTest::TestValue2HexString()
{
  std::string buf;
    
  if (strcmp(Integer2HexString(1, buf), "1") != 0) {
	  std::cout << "Integer2HexString failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Integer2HexString(9, buf), "9") != 0) {
	  std::cout << "Integer2HexString failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Integer2HexString(10, buf), "a") != 0) {
	  std::cout << "Integer2HexString failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Integer2HexString(15, buf), "f") != 0) {
	  std::cout << "Integer2HexString failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Integer2HexString(255, buf), "ff") != 0) {
	  std::cout << "Integer2HexString failed, :" << __LINE__ << std::endl;
  }

  if (strcmp(Long2HexString(1, buf), "1") != 0) {
	  std::cout << "Long2HexString failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Long2HexString(9, buf), "9") != 0) {
	  std::cout << "Long2HexString failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Long2HexString(10, buf), "a") != 0) {
	  std::cout << "Long2HexString failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Long2HexString(15, buf), "f") != 0) {
	  std::cout << "Long2HexString failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Long2HexString(255, buf), "ff") != 0) {
	  std::cout << "Long2HexString failed, :" << __LINE__ << std::endl;
  }

  if (strcmp(Sizet2HexString(1, buf), "1")  != 0) {
	  std::cout << "Sizet2HexString failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Sizet2HexString(9, buf), "9") != 0) {
	  std::cout << "Sizet2HexString failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Sizet2HexString(10, buf), "a") != 0) {
	  std::cout << "Sizet2HexString failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Sizet2HexString(15, buf), "f") != 0) {
	  std::cout << "Sizet2HexString failed, :" << __LINE__ << std::endl;
  }
  if (strcmp(Sizet2HexString(255, buf), "ff") != 0) {
	  std::cout << "Sizet2HexString failed, :" << __LINE__ << std::endl;
  }
}

void CyberLinkTest::TestHexString2Value()
{
	if (HexString2Integer("1") != 1) {
		std::cout << "HexString2Integer failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Integer("9") != 9) {
		std::cout << "HexString2Integer failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Integer("A") != 10) {
		std::cout << "HexString2Integer failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Integer("F") != 15) {
		std::cout << "HexString2Integer failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Integer("FF") != 255) {
		std::cout << "HexString2Integer failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Integer("a") != 10) {
		std::cout << "HexString2Integer failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Integer("f")!= 15) {
		std::cout << "HexString2Integer failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Integer("ff") != 255) {
		std::cout << "HexString2Integer failed, :" << __LINE__ << std::endl;
  }

	if (HexString2Long("1") != 1) {
		std::cout << "HexString2Long failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Long("9") != 9) {
		std::cout << "HexString2Long failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Long("A") != 10) {
		std::cout << "HexString2Long failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Long("F") != 15) {
		std::cout << "HexString2Long failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Long("FF") != 255) {
		std::cout << "HexString2Long failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Long("a") != 10) {
		std::cout << "HexString2Long failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Long("f") != 15) {
		std::cout << "HexString2Long failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Long("ff") != 255) {
		std::cout << "HexString2Long failed, :" << __LINE__ << std::endl;
  }

	if (HexString2Sizet("1") != 1) {
		std::cout << "HexString2Sizet failed, :" << __LINE__ << std::endl;
  }
if (HexString2Sizet("9") != 9) {
		std::cout << "HexString2Sizet failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Sizet("A") != 10) {
		std::cout << "HexString2Sizet failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Sizet("F") != 15) {
		std::cout << "HexString2Sizet failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Sizet("FF") != 255) {
		std::cout << "HexString2Sizet failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Sizet("a") != 10) {
		std::cout << "HexString2Sizet failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Sizet("f") != 15) {
		std::cout << "HexString2Sizet failed, :" << __LINE__ << std::endl;
  }
	if (HexString2Sizet("ff") != 255) {
		std::cout << "HexString2Sizet failed, :" << __LINE__ << std::endl;
  }
}

void CyberLinkTest::TestStringUtilParse()
{
  string valueStr;
  
  //UINT_MAX : 4294967295U
  // INT_MAX : 2147483647
  Integer2String(1, valueStr);
  if (strcmp("1", valueStr.c_str()) != 0) {
	  std::cout << "Integer2String failed, :" << __LINE__ << std::endl;
  }
  Integer2String(INT_MAX, valueStr);
  if (strcmp("2147483647", valueStr.c_str()) != 0) {
	  std::cout << "Integer2String failed, :" << __LINE__ << std::endl;
  }
  Integer2String(-1, valueStr);
  if (strcmp("-1", valueStr.c_str()) != 0) {
	  std::cout << "Integer2String failed, :" << __LINE__ << std::endl;
  }
  Integer2String(-INT_MAX, valueStr);
  if (strcmp("-2147483647", valueStr.c_str()) != 0) {
	  std::cout << "Integer2String failed, :" << __LINE__ << std::endl;
  }
  
  // UINT_LONG : 18446744073709551615UL
  // LONG_MAX :  9223372036854775807L
  Long2String(1, valueStr);
  if (strcmp("1", valueStr.c_str()) != 0) {
	  std::cout << "Long2String failed, :" << __LINE__ << std::endl;
  }
  Long2String(INT_MAX, valueStr);
  if (strcmp("2147483647", valueStr.c_str()) != 0) {
	  std::cout << "Long2String failed, :" << __LINE__ << std::endl;
  }
  Long2String(-1, valueStr);
  if (strcmp("-1", valueStr.c_str()) != 0) {
	  std::cout << "Long2String failed, :" << __LINE__ << std::endl;
  }
  Long2String(-INT_MAX, valueStr);
  if (strcmp("-2147483647", valueStr.c_str()) != 0) {
	  std::cout << "Long2String failed, :" << __LINE__ << std::endl;
  }
}

void CyberLinkTest::TestStringUtilTokenizer()
{
  StringTokenizer *strToken;
  const char *token[] = { "abcde", "test", "skonno" };
  char tokenStr[128];
  int tokenCnt;
    
  sprintf(tokenStr, "%s", token[0]);
  strToken = new StringTokenizer(tokenStr, ",");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
	if (strcmp(tstr, token[tokenCnt]) != 0) {
		std::cout << "nextToken failed, :" << __LINE__ << std::endl;
	}
    tokenCnt++;
  }
  if (tokenCnt != 1) {
	  std::cout << "nextToken failed, :" << __LINE__ << std::endl;
  }
  delete strToken;
    
  sprintf(tokenStr, "%s,%s,%s", token[0], token[1], token[2]);
  strToken = new StringTokenizer(tokenStr, ",");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
	if (strcmp(tstr, token[tokenCnt]) != 0) {
		std::cout << "nextToken failed, :" << __LINE__ << std::endl;
	}
    tokenCnt++;
  }
  if (tokenCnt != 3) {
	  std::cout << "nextToken failed, :" << __LINE__ << std::endl;
  }
  delete strToken;
    
  sprintf(tokenStr, "%s,%s,%s,", token[0], token[1], token[2]);
  strToken = new StringTokenizer(tokenStr, ",");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
	if (strcmp(tstr, token[tokenCnt]) != 0) {
		std::cout << "nextToken failed, :" << __LINE__ << std::endl;
	}
    tokenCnt++;
  }
  if (tokenCnt != 3) {
	  std::cout << "nextToken failed, :" << __LINE__ << std::endl;
  }
  delete strToken;
    
  sprintf(tokenStr, ",%s,%s,%s,", token[0], token[1], token[2]);
  strToken = new StringTokenizer(tokenStr, ",");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
	if (strcmp(tstr, token[tokenCnt]) != 0) {
		std::cout << "nextToken failed, :" << __LINE__ << std::endl;
	}
    tokenCnt++;
  }
  if (tokenCnt != 3) {
	  std::cout << "nextToken failed, :" << __LINE__ << std::endl;
  }
  delete strToken;
    
  strToken = new StringTokenizer("*", ",");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
	if (strcmp(tstr, "*") != 0) {
		std::cout << "nextToken failed, :" << __LINE__ << std::endl;
	}
    tokenCnt++;
  }
  if (tokenCnt != 1) {
	  std::cout << "nextToken failed, :" << __LINE__ << std::endl;
  }
  delete strToken;
    
  sprintf(tokenStr, "%s", token[0]);
  strToken = new StringTokenizer(tokenStr, ", \n\t");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
	if (strcmp(tstr, token[tokenCnt]) != 0) {
		std::cout << "nextToken failed, :" << __LINE__ << std::endl;
	}
    tokenCnt++;
  }
  if (tokenCnt != 1) {
	  std::cout << "nextToken failed, :" << __LINE__ << std::endl;
  }
  delete strToken;
    
  sprintf(tokenStr, "%s,,%s,,%s", token[0], token[1], token[2]);
  strToken = new StringTokenizer(tokenStr, ", \n\t");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
	if (strcmp(tstr, token[tokenCnt]) != 0) {
		std::cout << "nextToken failed, :" << __LINE__ << std::endl;
	}
    tokenCnt++;
  }
  if (tokenCnt != 3) {
	  std::cout << "nextToken failed, :" << __LINE__ << std::endl;
  }
  delete strToken;
    
  sprintf(tokenStr, "  %s,  %s,  %s,  ", token[0], token[1], token[2]);
  strToken = new StringTokenizer(tokenStr, ", \n\t");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
	if (strcmp(tstr, token[tokenCnt]) != 0) {
		std::cout << "nextToken failed, :" << __LINE__ << std::endl;
	}
    tokenCnt++;
  }
  if (tokenCnt != 3) {
	  std::cout << "nextToken failed, :" << __LINE__ << std::endl;
  }
  delete strToken;
    
  strToken = new StringTokenizer("*", ", \n\t");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
	if (strcmp(tstr, "*") != 0) {
		std::cout << "nextToken failed, :" << __LINE__ << std::endl;
	}
    tokenCnt++;
  }
  if (tokenCnt != 1) {
	  std::cout << "nextToken failed, :" << __LINE__ << std::endl;
  }
  delete strToken;
}
