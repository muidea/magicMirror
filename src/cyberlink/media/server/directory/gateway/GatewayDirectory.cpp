/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2004
*
*	File : GatewayDirectory.cpp
*
*	Revision:
*
*	04/14/04
*		- first revision.
*	08/01/04
*		- Added <typeinfo> for typeid() for gcc 2.95.3.
*
******************************************************************/

#include <media/server/ContentDirectory.h>
#include <media/server/ConnectionManager.h>
#include <media/server/object/Format.h>
#include <media/server/object/FormatObject.h>
#include <media/server/directory/gateway/GatewayDirectory.h>
#include <io/FileList.h>

#include <typeinfo>
#include <sstream>

using namespace std;
using namespace CyberLink;
using namespace uXML;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
	
GatewayDirectory::GatewayDirectory(const char *name) : Directory(name)
{
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////
	
void GatewayDirectory::update()
{
}

