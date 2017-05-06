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
#include <stdlib.h>

#include <platform.h>
#include <net/Socket.h>
#include <net/HostInterface.h>
#include <net/NetworkInterfaceList.h>
#include <net/SocketUtil.h>
#include <util/StringUtil.h>

#if defined(WIN32)
  #include <Iptypes.h>
  #include <Iphlpapi.h>
#else
  #include <sys/socket.h>
  #include <net/if.h>
  #if defined(HAVE_IFADDRS_H) || defined(__APPLE_CC__)
  #include <netdb.h>
  #include <ifaddrs.h>
  #else
  #include <sys/ioctl.h>
  #endif
#endif

#include <iostream>
#include <sstream>

using namespace std;

bool CyberLink::HostInterface::USE_LOOPBACK_ADDR = false;
bool CyberLink::HostInterface::USE_ONLY_IPV4_ADDR = false;
bool CyberLink::HostInterface::USE_ONLY_IPV6_ADDR = false;

#pragma comment(lib, "IPHLPAPI.lib")

////////////////////////////////////////////////
//  GetNHostAddresses
////////////////////////////////////////////////

size_t CyberLink::GetNHostAddresses() {
  if (HasAssignedHostInterface() == true)
    return 1;

  NetworkInterfaceList netIfList;
  return GetHostAddresses(netIfList);
}

const char *CyberLink::GetHostAddress(size_t n, std::string &buf) {
  buf = "";
  
  if (HasAssignedHostInterface() == false) {
    NetworkInterfaceList netIfList;
    size_t ifNum = GetHostAddresses(netIfList);
    if (0 < ifNum || n < ifNum) {
      NetworkInterface *netif = netIfList.getNetworkInterface(n);
      buf = netif->getAddress();
    }
  }
  else {
    buf = GetHostInterface();
  }
  
  return buf.c_str();
}

static bool IsUseAddress(const std::string &host) {
  if (CyberLink::HostInterface::USE_ONLY_IPV6_ADDR == true) {
    if (CyberLink::IsIPv6Address(host) == false)
      return false;
  }
  if (CyberLink::HostInterface::USE_ONLY_IPV4_ADDR == true) {
    if (CyberLink::IsIPv6Address(host) == true)
      return false;
  }
  return true;
}

////////////////////////////////////////////////
//  GetHostAddresses (WIN32)
////////////////////////////////////////////////

#if defined(_MSC_VER)

size_t CyberLink::GetHostAddresses(NetworkInterfaceList &netIfList) {
  SocketStartup();

  netIfList.clear();

  IP_ADAPTER_ADDRESSES *pAdapterAddresses, *ai;
  DWORD ifFlags = 
    GAA_FLAG_SKIP_ANYCAST | 
    GAA_FLAG_SKIP_FRIENDLY_NAME | 
    GAA_FLAG_SKIP_MULTICAST | 
    GAA_FLAG_SKIP_DNS_SERVER;
  ULONG outBufLen = 0;

  IP_ADAPTER_UNICAST_ADDRESS *uai;

  GetAdaptersAddresses(AF_UNSPEC, ifFlags, NULL, NULL, &outBufLen);
  pAdapterAddresses = (IP_ADAPTER_ADDRESSES *) LocalAlloc(LMEM_ZEROINIT, outBufLen);
  GetAdaptersAddresses(AF_UNSPEC, ifFlags, NULL, pAdapterAddresses, &outBufLen);
  ai = pAdapterAddresses;
  while (ai) {
    if (ai->OperStatus != IfOperStatusUp) {
      ai = ai->Next;
      continue;
    }
    if (ai->IfType == IF_TYPE_SOFTWARE_LOOPBACK) {
      ai = ai->Next;
      continue;
    }
    if (ai->IfType == IF_TYPE_TUNNEL) {
      ai = ai->Next;
      continue;
    }
    uai = ai->FirstUnicastAddress;
    while (uai) {
      SOCKET_ADDRESS sockaddr = uai->Address;
      SOCKADDR *saddr = sockaddr.lpSockaddr;
      INT saddrlen = sockaddr.iSockaddrLength;
      char addr[NI_MAXHOST];
      char port[NI_MAXSERV];
      int ret = getnameinfo(saddr, saddrlen, addr, sizeof(addr), port, sizeof(port), NI_NUMERICHOST | NI_NUMERICSERV);
      if (ret == 0) {
        if (IsUseAddress(addr) == true) {
          std::string addrStr = addr;
          int ifIdx = 0;
          if (IsIPv6Address(addr) == true) {
            ifIdx = GetIPv6ScopeID(addr);
            /*
            int pos = addrStr.find("%");
            if (pos != std::string::npos)
              addrStr = addrStr.substr(0, pos);
            */
          }

		  cyber_shared_ptr<NetworkInterface> netIf(new NetworkInterface(addrStr.c_str(), "", ifIdx));
          netIfList.add(netIf);
        }
      }
      else {
        int err = WSAGetLastError();
      }
      uai = uai->Next;
    }
    ai = ai->Next;
  }
  LocalFree(pAdapterAddresses);

  return netIfList.size();
}

#else

////////////////////////////////////////////////
//  GetHostAddresses (UNIX)
////////////////////////////////////////////////

#if defined(HAVE_IFADDRS_H) || defined(__APPLE_CC__)

size_t CyberLink::GetHostAddresses(NetworkInterfaceList &netIfList) {
  netIfList.clear();
  struct ifaddrs *ifaddr;
  if (getifaddrs(&ifaddr) != 0)
    return 0;
  while (ifaddr) {
    
    // Thanks for Ricardo Rivldo (04/10/12) 
    if (!ifaddr->ifa_addr){
      ifaddr = ifaddr->ifa_next;
      continue;
    }
    
    // Thanks for Tobias.Gansen (01/15/06)
    if(ifaddr->ifa_addr->sa_family != AF_INET){
      ifaddr = ifaddr->ifa_next;
      continue;
    }
    if (!(ifaddr->ifa_flags & IFF_UP)) {
      ifaddr = ifaddr->ifa_next;
      continue;
    }
    if (ifaddr->ifa_flags & IFF_LOOPBACK) {
      ifaddr = ifaddr->ifa_next;
      continue;
    }    
    char addr[NI_MAXHOST+1];
    if (getnameinfo(ifaddr->ifa_addr, sizeof(sockaddr), addr, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) == 0) {
      if (IsUseAddress(addr) == true) {
        std::string addrStr = addr;
        char *ifname = ifaddr->ifa_name;
        int ifIdx = if_nametoindex(ifname);
        //cout << ifname << ", " << ifIdx << endl;
        NetworkInterface *netIf = new NetworkInterface(addr, ifname, ifIdx);
        netIfList.add(netIf);
      }
    }
    ifaddr = ifaddr->ifa_next;
  }
  freeifaddrs(ifaddr);
  return netIfList.size();
}

#else

static const char *PATH_PROC_NET_DEV = "/proc/net/dev";

size_t CyberLink::GetHostAddresses(NetworkInterfaceList &netIfList) {
  netIfList.clear();
  int s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s < 0)
    return 0;
  FILE *fd = fopen(PATH_PROC_NET_DEV, "r");
  char buffer[256+1];
  fgets(buffer, sizeof(buffer)-1, fd);
  fgets(buffer, sizeof(buffer)-1, fd);
  while (!feof(fd)) {
    char *ifname = buffer;
    char *sep;
    if (fgets(buffer, sizeof(buffer)-1, fd)!)
      break;
    sep = strrchr(buffer, ':');
    if (sep)
      *sep = 0;
    while (*ifname == ' ')
      ifname++;
    struct ifreq req;
    strcpy(req.ifr_name, ifname);
    if (ioctl(s, SIOCGIFFLAGS, &req) < 0)
      continue;
    if (!(req.ifr_flags & IFF_UP))
      continue;
    if (req.ifr_flags & IFF_LOOPBACK)
      continue;
    if (ioctl(s, SIOCGIFADDR, &req) < 0)
      continue;
    char ifaddr[20+1];
    strncpy(ifaddr, inet_ntoa(((struct sockaddr_in*)&req.ifr_addr)->sin_addr), sizeof(ifaddr)-1);
    NetworkInterface *netIf = new NetworkInterface(ifaddr, ifname, 0);
    netIfList.add(netIf);
    //cout << ifname << ", " << ifaddr << endl;
  }
  fclose(fd);
  close(s);
  return netIfList.size();
}

#endif

#endif

////////////////////////////////////////////////
//  IsIPv6Address
////////////////////////////////////////////////

bool CyberLink::IsIPv6Address(const std::string &addr) {
  if (addr.find(":") != std::string::npos)
    return true;
  return false;
}

////////////////////////////////////////////////
//  ScopeID
////////////////////////////////////////////////

const char *CyberLink::StripIPv6ScopeID(const std::string &addr, std::string &buf) {
  std::string addrStr = addr;
  if (IsIPv6Address(addr) == true) {
    size_t pos = addrStr.find("%");
    if (pos != std::string::npos)
      addrStr = addrStr.substr(0, pos);
  }
  buf = addrStr;
  return buf.c_str();
}

int CyberLink::GetIPv6ScopeID(const std::string &addr) {
  if (IsIPv6Address(addr) == false)
    return 0;
  std::string addrStr = addr;
  size_t pos = addrStr.find("%");
  if (pos == std::string::npos)
    return 0;
  std::string scopeStr = addrStr.substr(pos+1, addrStr.length());
  return atoi(scopeStr.c_str());
}

////////////////////////////////////////////////
//  GetHostURL
////////////////////////////////////////////////

static string ifAddress;

void CyberLink::SetHostInterface(const std::string &ifaddr) {
  ifAddress = ifaddr;
}

const char *CyberLink::GetHostInterface() {
  return ifAddress.c_str();
}

bool CyberLink::HasAssignedHostInterface() {
  return (0 < ifAddress.length()) ? true : false;
}
