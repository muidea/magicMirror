/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_PROPERTYLIST_H_
#define _MUPMPCC_PROPERTYLIST_H_

#include <util/Vector.h>
#include <event/Property.h>

namespace CyberLink {

class PropertyList : public Vector<Property>  {
 public:
    
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  PropertyList() {
  }
  
  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////

 public:
  bool addProperty(Property *prop) {
        return add(prop);
  }
  
  bool removeProperty(Property *prop) {
    return remove(prop);
  }
  
  bool insertProperty(Property *prop, int index) {
    return insertAt(prop, index);
  }

  Property *getProperty(size_t n) {
    return get(n);
  }
};

}

#endif
