/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ADVERTISER_H_
#define _MUPMPCC_ADVERTISER_H_

#include <util/Thread.h>

namespace CyberLink {
class Device;

class Advertiser : public CyberLink::Thread {
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  Advertiser(Device *dev) {
    setDevice(dev);
  }
  
  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

private:
  
  Device *device;

 public:
  void setDevice(Device *dev) {
    device = dev;
  }
  
  Device *getDevice() {
    return device;
  }

  ////////////////////////////////////////////////
  // Thread
  ////////////////////////////////////////////////
  
 public:
  void run();

};

}

#endif

