/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPRESPONSELISTENER_H_
#define _MUPMPCC_SSDPRESPONSELISTENER_H_

#include <util/Listener.h>
#include <ssdp/SSDPPacket.h>

namespace CyberLink {

class SearchResponseListener : public CyberLink::Listener {
public:
  virtual bool deviceSearchResponseReceived(SSDPPacket *ssdpPacket) = 0;
};

}

#endif

