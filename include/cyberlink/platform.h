/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _CYBERLINK_PLATFORM_H_
#define _CYBERLINK_PLATFORM_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#if !defined(cyber_shared_ptr)

#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <memory>
typedef int ssize_t;
#ifndef HAVE_STRUCT_TIMESPEC
#define HAVE_STRUCT_TIMESPEC
#endif
#endif // WIN32


#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201103L)) || defined(__APPLE__) || (defined(_MSC_VER) && (_MSC_VER > 1600))
#define HAVE_STD_SHRAEDPTR 1
#define cyber_shared_ptr std::shared_ptr
#define cyber_weak_ptr std::weak_ptr
#endif

#if !defined(HAVE_STD_SHRAEDPTR)
#include <boost/shared_ptr.hpp>
#define cyber_shared_ptr boost::shared_ptr
#define cyber_weak_ptr boost::weak_ptr
#define nullptr NULL
#endif

#endif

#endif
