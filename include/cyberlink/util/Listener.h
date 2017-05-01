/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_UTIL_LISTENERLIST_H_
#define _UHTTP_UTIL_LISTENERLIST_H_

#include <util/Vector.h>

namespace CyberLink {

class Listener {
public:
    Listener() {
    }
    virtual ~Listener() {
    }
};

template <typename T> class ListenerList : public ::CyberLink::WeakVector<T> {

public:
    
  ListenerList() {
  }
};

}

#endif
