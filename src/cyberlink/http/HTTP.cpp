/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sstream>
#include <http/HTTP.h>
#include <net/URI.h>

#ifdef NO_USE_OSTRINGSTREAM
#include <util/StringUtil.h>
#endif

using namespace std;
using namespace CyberLink;
#ifdef NO_USE_OSTRINGSTREAM
using namespace CyberLink;
#endif

int CyberLink::HTTP::GetPort(const std::string &urlStr) {
  int port = CyberLink::URLGetPort(urlStr);
  if (port <= 0)
    port = HTTP::DEFAULT_PORT;
    return port;
}

const char *CyberLink::HTTP::GetAbsoluteURL(const std::string &baseURLStr, const std::string &relURlStr, std::string &buf) {
  CyberLink::URL baseURL(baseURLStr);
  int port = baseURL.getPort();
  if (port <= 0)
    port = HTTP::DEFAULT_PORT;
  string relURlStrBuf;
#ifndef NO_USE_OSTRINGSTREAM
  ostringstream url;
  url << 
    baseURL.getProtocol() << URI::PROTOCOL_DELIM <<
    baseURL.getHost() << URI::COLON_DELIM <<
    port <<
    HTTP::GetRelativeURL(relURlStr, relURlStrBuf);
  buf = url.str();
#else
  string ibuf;
  buf = "";
  buf += baseURL.getProtocol();
  buf += URI::PROTOCOL_DELIM;
  buf += baseURL.getHost();
  buf += URI::COLON_DELIM;
  buf += Integer2String(port, ibuf);
  buf += HTTP::GetRelativeURL(relURlStr, relURlStrBuf);
#endif
  return buf.c_str();
}

const char *CyberLink::HTTP::GetRequestHostURL(const std::string &host, int port, std::string &buf) {
#ifndef NO_USE_OSTRINGSTREAM
  std::ostringstream url;
  url << "http://" << host << ":" << port;
  buf = url.str();
#else
  string ibuf;
  buf = "";
  buf +="http://";
  buf += host;
  buf += ":";
  buf += Integer2String(port, ibuf);
#endif
  return buf.c_str();
}

////////////////////////////////////////////////
// Chunk Size
////////////////////////////////////////////////
  
static size_t httpChunkSize = CyberLink::HTTP::DEFAULT_CHUNK_SIZE;

void CyberLink::HTTP::SetChunkSize(size_t size) {
  httpChunkSize = size;
}
  
size_t CyberLink::HTTP::GetChunkSize() {
  return httpChunkSize;
}
