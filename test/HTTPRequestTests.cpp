/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string>
#include <vector>

#include <HTTP.h>
#include "HTTPRequestTests.h"

using namespace std;
using namespace CyberLink;

bool CyberLinkTest::TestHTTPRequest()
{
  HTTPRequest httpReq;
    
  //The first 500 bytes:
  httpReq.setContentRange(0, 499, 1234);
  if (httpReq.getContentRangeFirstPosition() != 0) {
	  std::cout << "getContentRangeFirstPosition failed. :" << __LINE__ << std::endl;
  }

  if (httpReq.getContentRangeLastPosition() != 499) {
	  std::cout << "getContentRangeLastPosition failed. :" << __LINE__ << std::endl;
  }
  if (httpReq.getContentRangeInstanceLength() != 1234) {
	  std::cout << "getContentRangeInstanceLength failed. :" << __LINE__ << std::endl;
  }
    
  //The second 500 bytes:
  httpReq.setContentRange(500, 999, 1234);
  if (httpReq.getContentRangeFirstPosition() != 500) {
	  std::cout << "getContentRangeFirstPosition failed. :" << __LINE__ << std::endl;
  }
  if (httpReq.getContentRangeLastPosition() != 999) {
	  std::cout << "getContentRangeLastPosition failed. :" << __LINE__ << std::endl;
  }
  if (httpReq.getContentRangeInstanceLength() != 1234) {
	  std::cout << "getContentRangeInstanceLength failed. :" << __LINE__ << std::endl;
  }
    
  //All except for the first 500 bytes:
  httpReq.setContentRange(500, 1233, 1234);
  if (httpReq.getContentRangeFirstPosition() != 500) {
	  std::cout << "getContentRangeFirstPosition failed. :" << __LINE__ << std::endl;
  }
  if (httpReq.getContentRangeLastPosition() != 1233) {
	  std::cout << "getContentRangeLastPosition failed. :" << __LINE__ << std::endl;
  }
  if (httpReq.getContentRangeInstanceLength() != 1234) {
	  std::cout << "getContentRangeInstanceLength failed. :" << __LINE__ << std::endl;
  }
    
  //All except for the first 500 bytes:
  httpReq.setContentRange(734, 1233, 1234);
  if (httpReq.getContentRangeFirstPosition() != 734) {
	  std::cout << "getContentRangeFirstPosition failed. :" << __LINE__ << std::endl;
  }
  if (httpReq.getContentRangeLastPosition() != 1233) {
	  std::cout << "getContentRangeLastPosition failed. :" << __LINE__ << std::endl;
  }
  if (httpReq.getContentRangeInstanceLength() != 1234) {
	  std::cout << "getContentRangeInstanceLength failed. :" << __LINE__ << std::endl;
  }
    
  //All except for the first 500 bytes:
  httpReq.setContentRange(734, 1233, 0);
  if (httpReq.getContentRangeFirstPosition() != 734) {
	  std::cout << "getContentRangeFirstPosition failed. :" << __LINE__ << std::endl;
  }
  if (httpReq.getContentRangeLastPosition() != 1233) {
	  std::cout << "getContentRangeLastPosition failed. :" << __LINE__ << std::endl;
  }
  if (httpReq.getContentRangeInstanceLength() != 0) {
	  std::cout << "getContentRangeInstanceLength failed. :" << __LINE__ << std::endl;
  }

  return true;
}

bool CyberLinkTest::TestHTTPRequestConnection()
{
  HTTPRequest httpReq;
    
  httpReq.setConnection(HTTP::CLOSE);
  if (httpReq.isCloseConnection() != true) {
	  std::cout << "isCloseConnection failed. :" << __LINE__ << std::endl;
  }
    
  httpReq.setConnection(HTTP::KEEP_ALIVE);
  if (httpReq.isKeepAliveConnection() != true) {
	  std::cout << "isKeepAliveConnection failed. :" << __LINE__ << std::endl;
  }
  return true;
}
