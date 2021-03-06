/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_NET_HOSTINTERFACE_H_
#define _UHTTP_NET_HOSTINTERFACE_H_

#include <net/Socket.h>
#include <net/NetworkInterfaceList.h>

#include <string>

namespace CyberLink {
	class HostInterface {
	public:
		static bool USE_LOOPBACK_ADDR;
		static bool USE_ONLY_IPV4_ADDR;
		static bool USE_ONLY_IPV6_ADDR;
		const static char *DEFAULT_IFNAME;
	};

	size_t GetNHostAddresses();
	const char *GetHostAddress(size_t n, std::string &buf);
	size_t GetHostAddresses(NetworkInterfaceList &netifList);

	bool IsIPv6Address(const std::string &host);
	const char *StripIPv6ScopeID(const std::string &addr, std::string &buf);
	int GetIPv6ScopeID(const std::string &addr);

	void SetHostInterface(const std::string &ifaddr);
	const char *GetHostInterface();
	bool HasAssignedHostInterface();

}

#endif
