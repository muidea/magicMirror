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
#include <sstream>

#include <HTTP.h>
#include "HTTPServerTests.h"
#include <util/Random.h>
using namespace std;
using namespace CyberLink;

//////////////////////////////////////////////////////////////////////
// Simple Request Listener
//////////////////////////////////////////////////////////////////////

#define UHTTP_HTTP_SERVER_TEST_LOOP_COUNT 3
#define UHTTP_HTTP_SERVER_TEST_CONTENT "123456789abcedfghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define UHTTP_HTTP_SERVER_TEST_PARAM_NAME "param"

class HTTPSimpleRequestListener : public HTTPRequestListener
{
public:
  HTTPSimpleRequestListener();
  
  HTTP::StatusCode httpRequestRecieved(HTTPRequest *httpReq);
};

HTTPSimpleRequestListener::HTTPSimpleRequestListener()
{
}

HTTP::StatusCode HTTPSimpleRequestListener::httpRequestRecieved(HTTPRequest *httpReq)
{
  if (httpReq->isGetRequest() == false) {
    return httpReq->returnBadRequest();
  }
  
  std::string uri;
  httpReq->getURI(uri);
  if (uri.length() <= 0) {
    return httpReq->returnBadRequest();
  }
  
  string paramStr;
  if (!httpReq->getParameterValue(UHTTP_HTTP_SERVER_TEST_PARAM_NAME, &paramStr)) {
	  std::cout << "getParameterValue failed, :" << __LINE__ << std::endl;
  }
  
  std::string msg = UHTTP_HTTP_SERVER_TEST_CONTENT;
  msg.append(paramStr);
  
  HTTPResponse httpRes;
  httpRes.setStatusCode(HTTP::OK_REQUEST);
  httpRes.setContent(msg);
  httpReq->post(&httpRes);
  
  return HTTP::OK_REQUEST;
}

//////////////////////////////////////////////////////////////////////
// Simple Server
//////////////////////////////////////////////////////////////////////

static void RequestToHTTPServer(const std::string &ifaddr, int port)
{
  for (int n=0; n<UHTTP_HTTP_SERVER_TEST_LOOP_COUNT; n++) {
    HTTPRequest httpReq;
    httpReq.setMethod(HTTP::GET);
    char httpReqURL[64];
    snprintf(httpReqURL, sizeof(httpReqURL), "http://%s:%d/?%s=%d", ifaddr.c_str(), port, UHTTP_HTTP_SERVER_TEST_PARAM_NAME, n);
    httpReq.setURL(httpReqURL);
    
    string httpReqStr;
    httpReq.toString(httpReqStr);
    
    HTTPResponse *httpRes = httpReq.post();
	if (httpRes->getStatusCode() != 200) {
		std::cout << "getStatusCode failed, :" << __LINE__ << std::endl;
	}
    string httpResContent = httpRes->getContent();
	if (0 >= httpResContent.length()) {
		std::cout << "getContent failed, :" << __LINE__ << std::endl;
	}
    
    std::stringstream msgBuf;
    msgBuf << UHTTP_HTTP_SERVER_TEST_CONTENT << n;
	if (httpResContent.compare(msgBuf.str()) != 0) {
		std::cout << "getContent failed, :" << __LINE__ << std::endl;
	}
    
    string httpResStr;
    httpRes->toString(httpResStr);
  }
}

bool CyberLinkTest::TestHTTPServer()
{
  HTTPServer httpServer;
  HTTPSimpleRequestListener httpSimpleReqListener;
  httpServer.addRequestListener(&httpSimpleReqListener);

  Random rand ((unsigned int)1000, (unsigned int)10000);
  int httpPort = rand.rand();
  
  if (Socket::GetInstanceCount() != 0) {
	  std::cout << "GetInstanceCount failed, :" << __LINE__ << std::endl;
  }
  
  if (!httpServer.open(httpPort,"127.0.0.1")) {
	  std::cout << "httpServer.open failed, :" << __LINE__ << std::endl;
  }
  if (!httpServer.start()) {
	  std::cout << "httpServer.start failed, :" << __LINE__ << std::endl;
  }
  
  const std::string ifaddr = "127.0.0.1";
  RequestToHTTPServer(ifaddr, httpPort);
  
  httpServer.close();
  httpServer.stop();
  
  if (Socket::GetInstanceCount() != 0) {
	  std::cout << "GetInstanceCount failed, :" << __LINE__ << std::endl;
  }

  std::cout << "finish TestHTTPServer" << std::endl;

  return true;
}

bool CyberLinkTest::TestHTTPServerList()
{
	std::cout << "start TestHTTPServer" << std::endl;
	if (Socket::GetInstanceCount() != 0) {
		std::cout << "GetInstanceCount failed, :" << __LINE__ << std::endl;
   }
  
  Random rand ((unsigned int)1000, (unsigned int)10000);
  
  HTTPServerList httpServerList;
  httpServerList.open(rand.rand());

  HTTPSimpleRequestListener httpSimpleReqListener;
  httpServerList.addRequestListener(&httpSimpleReqListener);
  
  httpServerList.start();
  
  size_t htttpServerCount = httpServerList.size();
  if (0 >= htttpServerCount) {
	  std::cout << "httpServerList.start failed, :" << __LINE__ << std::endl;
  }
  for (size_t n= 0; n < htttpServerCount; n++) {
    HTTPServer *httpServer = httpServerList.getHTTPServer(n);
    const std::string ifaddr = httpServer->getAddress();
    int httpPort = httpServer->getPort();
    RequestToHTTPServer(ifaddr, httpPort);
  }
  
  httpServerList.close();
  httpServerList.stop();
  
  if (Socket::GetInstanceCount() != 0) {
	  std::cout << "httpServerList.start failed, :" << __LINE__ << std::endl;
  }

  return true;
}
