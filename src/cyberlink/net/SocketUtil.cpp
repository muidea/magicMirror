/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/


#include <stdio.h>
#include <string.h>

#include <net/SocketCore.h>
#include <net/SocketUtil.h>

using namespace CyberLink;

////////////////////////////////////////////////
//  DecodeError
////////////////////////////////////////////////

int CyberLink::GetSocketLastErrorCode() {
#if defined(WIN32)
  return WSAGetLastError();
#else
  return 0;
#endif
}

const char *CyberLink::DecodeSocketError(int ErrorCode) {
  static char msg[1024];

#if defined(WIN32)
  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
    FORMAT_MESSAGE_MAX_WIDTH_MASK,
    NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (LPSTR)msg, 1024, NULL);
#else
  msg[0] = '\0';
#endif
  return msg;
}

////////////////////////////////////////////////
//  toSocketAddrIn
////////////////////////////////////////////////
bool CyberLink::toSocketAddrIn(const std::string &addr, int port, struct sockaddr_in *sockaddr, bool isBindAddr) {
  SocketStartup();

  memset(sockaddr, 0, sizeof(sockaddr_in));

  sockaddr->sin_family = AF_INET;
  sockaddr->sin_addr.s_addr = htonl(INADDR_ANY);
  sockaddr->sin_port = htons((unsigned short)port);

  if ((isBindAddr == true) || (0 < addr.length())) {
    sockaddr->sin_addr.s_addr = inet_addr(addr.c_str());
    if (sockaddr->sin_addr.s_addr == INADDR_NONE) {
      struct hostent *hent = gethostbyname(addr.c_str());
      if (!hent)
        return false;
      memcpy(&(sockaddr->sin_addr), hent->h_addr, hent->h_length);
    }
  }

  return true;
}

////////////////////////////////////////////////
//  toSocketAddrInfo
////////////////////////////////////////////////

bool CyberLink::toSocketAddrInfo(int sockType, const std::string &addr, int port, struct addrinfo **addrInfo, bool isBindAddr) {
  SocketStartup();

  int errorn;

  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = sockType;
  hints.ai_flags= /*AI_NUMERICHOST | */AI_PASSIVE;
  
  char portStr[32];
  sprintf(portStr, "%d", port);
  
  if ( (errorn = getaddrinfo(addr.c_str(), portStr, &hints, addrInfo)) != 0) {
    return false;
  }
  
  if (isBindAddr)
    return true;
  
  hints.ai_family = (*addrInfo)->ai_family;
  freeaddrinfo(*addrInfo);
  if ((errorn = getaddrinfo(NULL, portStr, &hints, addrInfo)) != 0) {
    return false;
  }
  
  return true;
}
