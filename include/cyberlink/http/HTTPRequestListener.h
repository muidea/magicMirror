/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_HTTPREQUESTLISTENER_H_
#define _UHTTP_HTTPREQUESTLISTENER_H_

#include <http/HTTPRequest.h>
#include <util/Listener.h>

namespace CyberLink {
    
class HTTPRequestListener : public Listener {
public:
  virtual HTTP::StatusCode httpRequestRecieved(HTTPRequest *httpReq) = 0;
};

}

#endif
