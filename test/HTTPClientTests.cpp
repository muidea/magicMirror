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
#include "HTTPClientTests.h"

using namespace CyberLink;

bool CyberLinkTest::TestHTTPGet()
{
  HTTPRequest httpReq;
  httpReq.setMethod(HTTP::GET);    
  httpReq.setURL("http://www.yahoo.co.jp/");    
  httpReq.setHeader("User-Agent", "curl/7.21.4 (universal-apple-darwin11.0) libcurl/7.21.4 OpenSSL/0.9.8r zlib/1.2.5");
  httpReq.setHeader("Accept", "*/*");
  //httpReq.print();
  
  HTTPResponse *httpRes = httpReq.post();
  return httpRes->getStatusCode()== 200;
  //httpRes->print();
}
