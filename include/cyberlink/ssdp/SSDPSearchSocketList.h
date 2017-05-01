/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPSEARCHSOCKETLIST_H_
#define _MUPMPCC_SSDPSEARCHSOCKETLIST_H_

#include <util/Vector.h>
#include <ssdp/SSDPSearchSocket.h>
#include <device/SearchListener.h>

namespace CyberLink {
    
class SSDPSearchSocketList : public Vector<SSDPSearchSocket>  {
public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  SSDPSearchSocketList();
  ~SSDPSearchSocketList();

  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  SSDPSearchSocket *getSSDPSearchSocket(size_t n) {
    return get(n);
  }
  
  void addSearchListener(SearchListener *listener);
  void removeSearchListener(SearchListener *listener);

  bool open();
  bool close();
    
  bool start();
  bool stop();

};

}

#endif
