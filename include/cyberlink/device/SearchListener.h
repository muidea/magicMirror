/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPSEARCHLISTENER_H_
#define _MUPMPCC_SSDPSEARCHLISTENER_H_

#include <util/Listener.h>
#include <ssdp/SSDPPacket.h>

namespace CyberLink {
    
class SearchListener : public CyberLink::Listener {
public:
  virtual bool deviceSearchReceived(SSDPPacket *ssdpPacket) = 0;
};

}

#endif

