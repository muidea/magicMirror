/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File: iTunesNode.h
*
*	Revision:
*
*	03/13/06
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITUNES_NODE_H_
#define _CLINK_MEDIA_ITUNES_NODE_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_ITUNES

#include <xml/Node.h>

namespace CyberLink {

class iTunesNode
{
	////////////////////////////////////////////////
	// Member
	////////////////////////////////////////////////

	uXML::Node *node;

	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////

public:

	iTunesNode();
	~iTunesNode();

	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////

public:

	void setNode(uXML::Node *value)
	{
		this->node = value;
	}

	uXML::Node *getNode()
	{
		return this->node;
	}

	////////////////////////////////////////////////
	// Key
	////////////////////////////////////////////////

public:

	const char *getKeyValue(const char *keyName);
	int getKeyInteger(const char *keyName);
	long getKeyLong(const char *keyName);

};

}

#endif

#endif
