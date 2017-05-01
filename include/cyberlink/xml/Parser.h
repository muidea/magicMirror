/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_PARSER_H_
#define _MUPMPCC_PARSER_H_

#include <stdio.h>
#include <string.h>
#include <string>

#include <io/File.h>
#include <net/URL.h>

#include <xml/XML.h>
#include <xml/Node.h>
#include <xml/ParserException.h>

namespace uXML {

const int PARSER_DEFAULT_READ_BUF_SIZE = 1024;

class Parser  {
 public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  Parser();
  ~Parser();

  ////////////////////////////////////////////////
  // parse (File)
  ////////////////////////////////////////////////

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
  cyber_shared_ptr<uXML::Node> parse(CyberLink::File *file);
#endif

  cyber_shared_ptr<uXML::Node> parse(CyberLink::URL *url);
  
  cyber_shared_ptr<uXML::Node> parse(const std::string &data, size_t len);

  cyber_shared_ptr<uXML::Node> parse(const std::string &data) {
    return parse(data, data.length());
  }
  
  cyber_shared_ptr<uXML::Node> parse(std::string *data) {
    return parse(data->c_str(), data->length());
  }
  
  cyber_shared_ptr<uXML::Node> parse(UnicodeStr *data, size_t len) {
    return parse((const std::string &)data, len);
  }
};

}

#endif
