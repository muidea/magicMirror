/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_DEVICELIST_H_
#define _MUPMPCC_DEVICELIST_H_

#include <util/Vector.h>

namespace CyberLink {
class Device;

class DeviceList : public SharedVector<Device> {
public:
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  DeviceList() 
  {
  }
  
  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  cyber_shared_ptr<Device> getDevice(size_t n) {
    return get(n);
  }
};

}

#endif


