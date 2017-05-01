/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_DEVICECHANGELISTENER_H_
#define _MUPMPCC_DEVICECHANGELISTENER_H_

#include <util/Listener.h>

namespace CyberLink {
class Device;

class DeviceChangeListener : public CyberLink::Listener {
public:
  virtual bool deviceAdded(Device *dev) = 0;
  virtual bool deviceRemoved(Device *dev) = 0;
};

}

#endif
