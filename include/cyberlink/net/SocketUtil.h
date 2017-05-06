/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_NET_SOCKETUTIL_H_
#define _UHTTP_NET_SOCKETUTIL_H_

#include <platform.h>

#include <string.h>

#if defined(WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

namespace CyberLink {
int GetSocketLastErrorCode();
const char *DecodeSocketError(int ErrorCode);

bool toSocketAddrIn(const std::string &addr, int port, struct sockaddr_in *sockaddr, bool isBindAddr = true);
bool toSocketAddrInfo(int sockType, const std::string &addr, int port, struct addrinfo **addrInfo, bool isBindAddr = true);
}

#endif

