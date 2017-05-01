/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SUBSCRIBERLIST_H_
#define _MUPMPCC_SUBSCRIBERLIST_H_

#include <util/Vector.h>
#include <event/Subscriber.h>

namespace CyberLink {
    
class SubscriberList : public Vector<Subscriber>  {
public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  SubscriberList()
  {
  }
  
  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  Subscriber *getSubscriber(size_t n) {
    return get(n);
  }
};

}

#endif


