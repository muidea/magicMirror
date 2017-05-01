/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <stdlib.h>

#if defined(WIN32) || defined(__CYGWIN__)
#include <windows.h>
#include <winnls.h>
#else
#include <string.h>
#include <locale.h>
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
#include <iconv.h>
#endif
#endif

#include <xml/XML.h>
#include <util/StringUtil.h>
#ifndef WIN32
#include <util/Mutex.h>
#endif

#include <stdio.h>

#ifndef WIN32
static CyberLink::Mutex iconvMutex;
#endif

////////////////////////////////////////////////
// EscapeXMLChars
////////////////////////////////////////////////

const char *uXML::XML::EscapeXMLChars(const std::string &in, std::string &out) {
  out = in;
  
  // Thanks for Smolander Visa (09/06/05)
  CyberLink::StringReplaceChars(out, "&", "&amp;");

  CyberLink::StringReplaceChars(out, "<", "&lt;");
  CyberLink::StringReplaceChars(out, ">", "&gt;");
  CyberLink::StringReplaceChars(out, "\"", "&quot;");
  
  // Thanks for Brian Owens (12/02/04)
  CyberLink::StringReplaceChars(out, "'", "&apos;");
  
  return out.c_str();
}

const char *uXML::XML::EscapeXMLChars(std::string &in, std::string &out) {
  return EscapeXMLChars(in.c_str(), out);
}
