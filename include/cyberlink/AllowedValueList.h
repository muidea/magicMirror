/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ALLOWEDVALUELIST_H_
#define _MUPMPCC_ALLOWEDVALUELIST_H_

#include <string>
#include <util/Vector.h>
#include <AllowedValue.h>

namespace CyberLink {
    
class AllowedValueList : public Vector<AllowedValue>  {
public:
    
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  AllowedValueList()
  {
  }

  AllowedValue *getAllowedValue(size_t n) {
    return get(n);
  }

};

}

#endif

