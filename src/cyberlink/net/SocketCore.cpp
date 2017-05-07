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
#include <net/SocketCore.h>
#include <net/SocketUtil.h>
#include <net/HostInterface.h>
#include <util/Mutex.h>
#include <util/StringUtil.h>

#if !defined(WIN32)
#include <fcntl.h>
#include <signal.h>
#endif

#if defined(__APPLE_CPP__) || defined(__APPLE_CC__)
#include <TargetConditionals.h>
#endif

using namespace CyberLink;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const int SocketCore::STREAM = 1;
const int SocketCore::DGRAM = 2;

////////////////////////////////////////////////
//  Static methods
////////////////////////////////////////////////

static SocketList gAllSocketList;
static Mutex      gSocketListMutex;

size_t SocketCore::GetInstanceCount() {
	return gAllSocketList.size();
}

SocketList *SocketCore::GetInstanceList() {
	return &gAllSocketList;
}

////////////////////////////////////////////////
//  SocketInit/Close
////////////////////////////////////////////////

static int startUpCount = 0;
static int clearUpCount = 0;

void CyberLink::SocketStartup() {
	if (SocketCore::GetInstanceCount() == 0) {
		if (startUpCount != clearUpCount) {
			std::cout << "Thread:" << _threadid << ", invalid startup......" << std::endl;
		}
		startUpCount++;

#if defined(WIN32)
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);

#endif

#if !defined(WIN32)
		// Thanks for Brent Hills (10/26/04)
		signal(SIGPIPE, SIG_IGN);
#endif
	}
}

void CyberLink::SocketCleanup() {
	if (SocketCore::GetInstanceCount() == 0) {
		clearUpCount++;
#if defined(WIN32)
		WSACleanup();
#endif

#if !defined(WIN32)
		// Thanks for Brent Hills (10/26/04)
		signal(SIGPIPE, SIG_DFL);
#endif
	}
}

////////////////////////////////////////////////
//  Constructor/Destructor
////////////////////////////////////////////////

SocketCore::SocketCore() {
	SocketStartup();
	setType(0);
	setLocalAddress("");
	setLocalPort(0);
	setErrorCode(0);
#if defined(WIN32)
	setSocket(INVALID_SOCKET);
#else
	setSocket(-1);
#endif

	std::cout << "Thread:" << _threadid << ", SocketCore:0x" << std::hex << this << std::endl;

	gSocketListMutex.lock();
	gAllSocketList.add(this);
	gSocketListMutex.unlock();
}

SocketCore::~SocketCore() {
	std::cout << "Thread:" << _threadid << ", ~SocketCore:0x" << std::hex << this << std::endl;

	SocketCleanup();
	gSocketListMutex.lock();
	gAllSocketList.remove(this);
	gSocketListMutex.unlock();

}

bool SocketCore::isBound() {
#if defined(WIN32)
	return (sock != INVALID_SOCKET) ? true : false;
#else
	return (0 <= sock) ? true : false;
#endif
}

////////////////////////////////////////////////
//  close
////////////////////////////////////////////////

bool SocketCore::close() {
	if (!isBound())
		return true;

#if defined(WIN32)
	WSAAsyncSelect(sock, NULL, 0, FD_CLOSE);
	shutdown(sock, SD_BOTH);
	closesocket(sock);
	setSocket(INVALID_SOCKET);
#else
	int flag = fcntl(sock, F_GETFL, 0);
	if (0 <= flag)
		fcntl(sock, F_SETFL, flag | O_NONBLOCK);
	shutdown(sock, 2);
	if (::close(sock) == -1) {
		setErrorCode(errno);
		return false;
	}
	setSocket(-1);
#endif

	return true;
}

////////////////////////////////////////////////
//  Socket Option
////////////////////////////////////////////////

bool SocketCore::setReuseAddress(bool flag) {
	int sockOptRet;
#if defined (WIN32)
	BOOL optval = (flag == true) ? 1 : 0;
	sockOptRet = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval, sizeof(optval));
#else
	int optval = (flag == true) ? 1 : 0;
	sockOptRet = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval, sizeof(optval));
#if defined(USE_SO_REUSEPORT) || defined(TARGET_OS_MAC) || defined(TARGET_OS_IPHONE)
	if (sockOptRet == 0) {
		sockOptRet = setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (const char *)&optval, sizeof(optval));
	}
#endif
#endif
	return (sockOptRet == 0) ? true : false;
}

bool SocketCore::setTimeout(time_t timeoutSec) {
	int sockOptRet;

#if defined (WIN32)
	timeval timeout;
	timeout.tv_sec = (long)timeoutSec;
	timeout.tv_usec = 0;

	sockOptRet = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
	if (sockOptRet == 0) {
		sockOptRet = setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(timeout));
	}
#else
	timeval timeout;
	timeout.tv_sec = timeoutSec;
	timeout.tv_usec = 0;

	sockOptRet = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
	if (sockOptRet == 0) {
		sockOptRet = setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(timeout));
	}
#endif

	return (sockOptRet == 0) ? true : false;
}
