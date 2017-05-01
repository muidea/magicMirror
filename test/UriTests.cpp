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
#include "UriTests.h"

using namespace CyberLink;

void CyberLinkTest::TestHTTPUri()
{
  URL url;
  
  url.setString("http://www.yahoo.co.jp/index.html");
  if (url.getProtocol() != "http") {
	  std::cout << "getProtocol failed, :" << __LINE__ << std::endl;
  }
  if (url.getHost() != "www.yahoo.co.jp") {
	  std::cout << "getHost failed, :" << __LINE__ << std::endl;
  }
  if (url.getPort() != 80) {
	  std::cout << "getPort failed, :" << __LINE__ << std::endl;
  }
  if (url.getPath() != "/index.html") {
	  std::cout << "getPath failed, :" << __LINE__ << std::endl;
  }

  url.setString("https://www.yahoo.co.jp/index.html");
  if (url.getProtocol() != "https") {
	  std::cout << "getProtocol failed, :" << __LINE__ << std::endl;
  }
  if (url.getHost() != "www.yahoo.co.jp") {
	  std::cout << "getHost failed, :" << __LINE__ << std::endl;
  }
  if (url.getPort() != 443) {
	  std::cout << "getPort failed, :" << __LINE__ << std::endl;
  }
  if (url.getPath() != "/index.html") {
	  std::cout << "getPath failed, :" << __LINE__ << std::endl;
  }
}

void CyberLinkTest::TestHTTPGetAbsoluteURL()
{
  // URLGetAbsoluteURL
  std::string urlBuf;
  URLGetAbsoluteURL("http://www.cybergarage.org:8080/test.html", "blog/index.html", urlBuf);
  if (strcmp(urlBuf.c_str(), "http://www.cybergarage.org:8080/blog/index.html") != 0) {
	  std::cout << "URLGetAbsoluteURL failed, :" << __LINE__ << std::endl;
  }
}

void CyberLinkTest::TestHTTPGetHostURL()
{
  // GetHostURL
  std::string urlBuf;
  GetHostURL("www.cybergarage.org", 8080, "blog/index.html", urlBuf);
  if (strcmp(urlBuf.c_str(), "http://www.cybergarage.org:8080/blog/index.html") != 0) {
	  std::cout << "URLGetAbsoluteURL failed, :" << __LINE__ << std::endl;
  }
}
