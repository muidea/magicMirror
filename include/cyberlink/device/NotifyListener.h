/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_NOTIFYLISTENER_H_
#define _MUPMPCC_NOTIFYLISTENER_H_

#include <util/Listener.h>
#include <ssdp/SSDPPacket.h>

namespace CyberLink {

class NotifyListener : public CyberLink::Listener {
public:
  virtual bool deviceNotifyReceived(SSDPPacket *ssdpPacket) = 0;
};

}

#endif

