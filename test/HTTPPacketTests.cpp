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
#include  <iostream>
#include "HTTPPacketTests.h"

using namespace CyberLink;

bool CyberLinkTest::TestHTTPPacket()
{
  const char *TEST_HTTP_HEADER_NAME = "testHeader";
  const char *TEST_HTTP_HEADER2_NAME = "testHeader2";
  const int TEST_HTTP_HEADER_INT_VALUE = 123456;
  const long TEST_HTTP_HEADER_LONG_VALUE = 123456789;
  const char *TEST_HTTP_HEADER_STRING = "testHeader: 123456\r\ntestHeader2: 123456789\r\n" ;
  
  const char TEST_HTTP_CONTENT_RANGE_STRING1[] = "bytes 111-222/333";
  const char TEST_HTTP_CONTENT_RANGE_STRING2[] = "bytes 111-222/*";
  
  const char TEST_HTTP_CASHCTRL_STRING[] = "max-age=123456";

  HTTPPacket *httpPacket;
  HTTPHeader *header;
  std::string headerStr;
  
  // HTTPPacket::setHeader (int)
  httpPacket = new HTTPPacket();
  httpPacket->setHeader(TEST_HTTP_HEADER_NAME, TEST_HTTP_HEADER_INT_VALUE);
  if (httpPacket->getHeader(TEST_HTTP_HEADER_NAME) == nullptr) {
	  std::cout << "getHeader failed. :" << __LINE__ << std::endl;
  }

  if (httpPacket->getIntegerHeaderValue(TEST_HTTP_HEADER_NAME) != TEST_HTTP_HEADER_INT_VALUE) {
	  std::cout << "getIntegerHeaderValue failed. :" << __LINE__ << std::endl;
  }
  delete httpPacket;
    
  // HTTPPacket::setHeader (long)
  httpPacket = new HTTPPacket();
  httpPacket->setHeader(TEST_HTTP_HEADER_NAME, TEST_HTTP_HEADER_LONG_VALUE);
  if (httpPacket->getHeader(TEST_HTTP_HEADER_NAME) == nullptr) {
	  std::cout << "getHeader failed. :" << __LINE__ << std::endl;
  }

  if (httpPacket->getLongHeaderValue(TEST_HTTP_HEADER_NAME) != TEST_HTTP_HEADER_INT_VALUE) {
	  std::cout << "getLongHeaderValue failed. :" << __LINE__ << std::endl;
  }
  delete httpPacket;
    
  // HTTPPacket::getHeaderString
  httpPacket = new HTTPPacket();
  httpPacket->setHeader(TEST_HTTP_HEADER_NAME, TEST_HTTP_HEADER_INT_VALUE);
  httpPacket->setHeader(TEST_HTTP_HEADER2_NAME, TEST_HTTP_HEADER_LONG_VALUE);
  httpPacket->getHeaderString(headerStr);
  if (headerStr.compare(TEST_HTTP_HEADER_STRING) != 0) {
	  std::cout << "getHeaderString failed. :" << __LINE__ << std::endl;
  }
  delete httpPacket;
    
  // HTTPPacket::setContentRange
  long contentRagne[3];
  httpPacket = new HTTPPacket();
  
  httpPacket->setContentRange(111, 222, 333);
  header = httpPacket->getHeader(HTTP::CONTENT_RANGE);
  if (strcmp(header->getValue(), TEST_HTTP_CONTENT_RANGE_STRING1) != 0) {
	  std::cout << "getHeader failed. :" << __LINE__ << std::endl;
  }
  httpPacket->getContentRange(contentRagne);
  if (contentRagne[0] != 111) {
	  std::cout << "getContentRange failed. :" << __LINE__ << std::endl;
  }
  if (contentRagne[1] != 222) {
	  std::cout << "getContentRange failed. :" << __LINE__ << std::endl;
  }
  if (contentRagne[2] != 333) {
	  std::cout << "getContentRange failed. :" << __LINE__ << std::endl;
  }
  
  httpPacket->setContentRange(111, 222, 0);
  header = httpPacket->getHeader(HTTP::CONTENT_RANGE);
  if (strcmp(header->getValue(), TEST_HTTP_CONTENT_RANGE_STRING2) != 0) {
	  std::cout << "getValue failed. :" << __LINE__ << std::endl;
  }

  httpPacket->getContentRange(contentRagne);
  if (contentRagne[0] != 111) {
	  std::cout << "getContentRange failed. :" << __LINE__ << std::endl;
  }
  if (contentRagne[1] != 222) {
	  std::cout << "getContentRange failed. :" << __LINE__ << std::endl;
  }
  if (contentRagne[2] != 0) {
	  std::cout << "getContentRange failed. :" << __LINE__ << std::endl;
  }
  delete httpPacket;
  
  // HTTPPacket::setCacheControl
  httpPacket = new HTTPPacket();
  httpPacket->setCacheControl(HTTP::MAX_AGE, 123456);
  header = httpPacket->getHeader(HTTP::CACHE_CONTROL);
  if (strcmp(header->getValue(), TEST_HTTP_CASHCTRL_STRING) != 0) {
	  std::cout << "getValue failed. :" << __LINE__ << std::endl;
  }

  if (strcmp(httpPacket->getCacheControl(), TEST_HTTP_CASHCTRL_STRING) != 0) {
	  std::cout << "getCacheControl failed. :" << __LINE__ << std::endl;
  }
  delete httpPacket;
  return true;
}
