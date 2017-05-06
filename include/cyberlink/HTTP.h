/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_HTTP_H_
#define _UHTTP_HTTP_H_

#include <io/BufferedReader.h>
#include <io/InputStream.h>
#include <io/InputStreamReader.h>

#include <util/Mutex.h>
#include <util/Random.h>
#include <util/StringTokenizer.h>

#include <net/URI.h>
#include <net/URL.h>
#include <net/NetworkInterface.h>
#include <net/NetworkInterfaceList.h>
#include <net/HostInterface.h>
#include <net/SocketInputStream.h>

#include <http/HTTP.h>
#include <http/HTTPRequest.h>
#include <http/HTTPResponse.h>
#include <http/HTTPServer.h>
#include <http/HTTPServerList.h>
#include <http/HTTPRequestListener.h>

#ifdef WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif

#endif
