/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/
#include "platform.h"
#include "DateTests.h"
#include "HTTPClientTests.h"
#include "HTTPPacketTests.h"
#include "HTTPRequestTests.h"
#include "HTTPServerTests.h"
#include "HTTPStatusTests.h"
#include "LoggerTests.h"
#include "MessageQueueTest.h"
#include "MutexTests.h"
#include <iostream>
int main(int argc, char* argv[])
{
	/*
	std::cout << "DateTests.................." << std::endl;
	CyberLinkTest::TestDate();
	std::cout << "HTTPClientTests.................." << std::endl;
	CyberLinkTest::TestHTTPGet();
	std::cout << "HTTPPacketTests.................." << std::endl;
	CyberLinkTest::TestHTTPPacket();
	std::cout << "HTTPRequestTests.................." << std::endl;
	CyberLinkTest::TestHTTPRequest();
	CyberLinkTest::TestHTTPRequestConnection();
	*/
	std::cout << "HTTPServerTests.................." << std::endl;
	CyberLinkTest::TestHTTPServer();
	CyberLinkTest::TestHTTPServerList();
	/*
	std::cout << "HTTPStatusTests.................." << std::endl;
	CyberLinkTest::TestHTTPStatus();
	std::cout << "LoggerTests.................." << std::endl;
	CyberLinkTest::TestLogger();
	CyberLinkTest::TestLog();
	std::cout << "MessageQueueTest.................." << std::endl;
	CyberLinkTest::TestPostMessage();
	CyberLinkTest::TestClearMessage();
	CyberLinkTest::TestLoopMessage();
	CyberLinkTest::TestMessageCancelThread();
	std::cout << "MutexTests.................." << std::endl;
	CyberLinkTest::TestMutex();
	*/
	return 0;
}