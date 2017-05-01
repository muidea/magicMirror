/******************************************************************
*
* uHTTP for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#elif defined(__APPLE__)
#define HAVE_IFADDRS_H
#define HAVE_SYS_RESOURCE_H
#endif

#include <string>
#include <vector>

#if defined(HAVE_IFADDRS_H)
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

#if defined(HAVE_SYS_RESOURCE_H)
#include <sys/resource.h>
#endif

#include <HTTP.h>
#include <net/SocketUtil.h>
#include "SocketTests.h"

using namespace std;
using namespace CyberLink;

void CyberLinkTest::SocketConnectionHttpServerTest(void)
{
  const char *CG_HOST_IPADDR = "www.cybergarage.org";
  const char *TEST_HTTP_METHOD = "GET /index.html HTTP/1.0";

  Socket *sock;
  ssize_t sentLen;
  ssize_t readLen;
  const char *line;
    
  sock = new Socket();
  if (!sock->connect(CG_HOST_IPADDR, 80)) {
	  std::cout << "sock->connect failed, :" << __LINE__ << std::endl;
  }
    
  sentLen = sock->send(TEST_HTTP_METHOD, strlen(TEST_HTTP_METHOD));
  if (sentLen != strlen(TEST_HTTP_METHOD)) {
	  std::cout << "sock->send failed, :" << __LINE__ << std::endl;
  }
  sentLen = sock->send(HTTP::CRLF, strlen(HTTP::CRLF));
  if (sentLen != strlen(HTTP::CRLF)) {
	  std::cout << "sock->send failed, :" << __LINE__ << std::endl;
  }
  sentLen = sock->send(HTTP::CRLF, strlen(HTTP::CRLF));
  if (sentLen != strlen(HTTP::CRLF)) {
	  std::cout << "sock->send failed, :" << __LINE__ << std::endl;
  }
    
  SocketInputStream sockIn(sock);
  InputStreamReader inReader(&sockIn);
  BufferedReader bufReader(&inReader);
    
  do {
    line = bufReader.readLine();
    readLen = strlen(line);
    //printf("%d:%s\n", readLen, line);
  } while (2 < readLen);
    
  sock->close();
  delete sock;
}


void CyberLinkTest::SocketConnectionLoopHttpServerTest()
{
  size_t socketRepeatCnt = 100;
#if defined(HAVE_SYS_RESOURCE_H)
  struct rlimit resLimit;
  BOOST_CHECK_EQUAL(getrlimit(RLIMIT_NOFILE, &resLimit), 0);
  socketRepeatCnt = resLimit.rlim_cur / 2;
#endif

  size_t startSocketCount = Socket::GetInstanceCount();
  for (size_t n=0; n<socketRepeatCnt; n++) {
    SocketConnectionHttpServerTest();
  }
  size_t endSocketCount = Socket::GetInstanceCount();
  if (startSocketCount != endSocketCount) {
	  std::cout << "GetInstanceCount failed, :" << __LINE__ << std::endl;
  }
}

