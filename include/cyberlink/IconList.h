/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ICONLIST_H_
#define _MUPMPCC_ICONLIST_H_

#include <util/Vector.h>
#include <Icon.h>

namespace CyberLink{
    
class IconList : public Vector<Icon> {
 public:
    
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

 public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  IconList() 
  {
  }
    
  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  Icon *getIcon(size_t n) {
    return get(n);
  }
};

}

#endif



