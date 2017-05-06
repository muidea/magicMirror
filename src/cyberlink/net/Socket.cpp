/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <errno.h>
#include <net/Socket.h>
#include <util/StringUtil.h>
#include <util/TimeUtil.h>
#include <net/SocketUtil.h>
#include <util/Mutex.h>

#include <stdio.h>

using namespace CyberLink;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

////////////////////////////////////////////////
//  Socket
////////////////////////////////////////////////

Socket::Socket() {
  setType(STREAM);
  
}

Socket::~Socket() {
  close();
}

////////////////////////////////////////////////
//  listen
////////////////////////////////////////////////

bool Socket::listen() {
  int ret = ::listen(sock, SOMAXCONN);
  if (ret != 0)
    setErrorCode(errno);
  return (ret == 0) ? true: false;
}

////////////////////////////////////////////////
//  bind
////////////////////////////////////////////////

bool Socket::bind(int bindPort, const std::string &bindAddr) {
  setLocalAddress("");
  setLocalPort(0);

  struct sockaddr_in toaddrInfo;
  if (toSocketAddrIn(bindAddr, bindPort, &toaddrInfo, true) == false)
	  return false;
  sock = socket(toaddrInfo.sin_family, SOCK_STREAM, IPPROTO_TCP);
  if (sock == -1) {
    close();
    return false;
  }
  size_t ret = ::bind(sock, (sockaddr*)&toaddrInfo, sizeof(toaddrInfo));
  if (ret != 0)
    setErrorCode(errno);

  if (ret != 0)
    return false;

  setLocalAddress(bindAddr);
  setLocalPort(bindPort);

  return true;
}

////////////////////////////////////////////////
//  accept
////////////////////////////////////////////////

bool Socket::accept(Socket *socket) {
  SOCKET clientSock;

  struct sockaddr_storage sockClientAddr;
  socklen_t nLength = sizeof(sockClientAddr);
  clientSock = ::accept(sock, (struct sockaddr *)&sockClientAddr, &nLength);
  if (0 < clientSock) {
    int sockOpt = 1;
#if defined(HAVE_SO_NOSIGPIPE) || defined(__APPLE_CC__)
    setsockopt(clientSock, SOL_SOCKET, SO_NOSIGPIPE, (void *)&sockOpt, sizeof(int));
#endif
  }
  else {
    setErrorCode(errno);
  }

#if defined(WIN32)
  if (clientSock == INVALID_SOCKET)
    return false;
#else
  if (clientSock < 0)
    return false;
#endif

  socket->setSocket(clientSock);
  socket->setLocalAddress(getLocalAddress());
  socket->setLocalPort(getLocalPort());

  return true;
}

////////////////////////////////////////////////
//  connect
////////////////////////////////////////////////

bool Socket::connect(const std::string &addr, int port) {
  struct sockaddr_in toaddrInfo;
  if (toSocketAddrIn(addr, port, &toaddrInfo, true) == false)
    return false;

  if (isBound() == false)
    this->sock = socket(toaddrInfo.sin_family, SOCK_STREAM, IPPROTO_TCP);

  if (this->sock == -1) {
    setErrorCode(errno);
    return false;
  }

#if defined(HAVE_SO_NOSIGPIPE) || defined(__APPLE_CC__)
  int sockOpt = 1;
  setsockopt(this->sock, SOL_SOCKET, SO_NOSIGPIPE, (void *)&sockOpt, sizeof(int));
#endif
  
  int ret = ::connect(this->sock, (sockaddr*)&toaddrInfo, sizeof(toaddrInfo));
  if (ret != 0)
    setErrorCode(errno);
  
  return (ret == 0) ? true : false;
}

////////////////////////////////////////////////
//  recv
////////////////////////////////////////////////

ssize_t Socket::recv(char *buffer, size_t bufferLen) {
  ssize_t recvLen = ::recv(sock, buffer, bufferLen, 0);
  return recvLen;
}


////////////////////////////////////////////////
//  send
////////////////////////////////////////////////

const int CG_NET_SOCKET_SEND_RETRY_CNT = 10;
const int CG_NET_SOCKET_SEND_RETRY_WAIT_MSEC = 1000;

ssize_t Socket::send(const char *cmd, size_t cmdLen) {
  if (cmdLen <= 0)
    return 0;
  ssize_t nTotalSent = 0;
  ssize_t cmdPos = 0;
  int retryCnt = 0;
  do {
    ssize_t nSent = ::send(sock, cmd + cmdPos, cmdLen, 0);
    // Thanks for Brent Hills (10/20/04)
    if (nSent <= 0)  {
      retryCnt++;
      if (CG_NET_SOCKET_SEND_RETRY_CNT < retryCnt)
        break;
      WaitRandom(CG_NET_SOCKET_SEND_RETRY_WAIT_MSEC);
      continue;
    }
    nTotalSent += nSent;
    cmdPos += nSent;
    cmdLen -= nSent;
    retryCnt = 0;
  } while (0 < cmdLen);
  
  return nTotalSent;
}

ssize_t Socket::send(const std::string &cmd) {
  return send(cmd.c_str(), cmd.size());
}

ssize_t Socket::send(const char c) {
  return send(&c, 1);
}
