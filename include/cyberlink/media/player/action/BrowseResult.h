/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : BrowseResult.h
*
*	Revision:
*
*	04/26/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_BROWSERESULT_H_
#define _CLINK_MEDIA_BROWSERESULT_H_

#include <xml/Node.h>

namespace CyberLink {

class BrowseResult
{
	cyber_shared_ptr<uXML::Node> resultNode;

	////////////////////////////////////////////////
	// Constrictor
	////////////////////////////////////////////////
	
public:

	BrowseResult(cyber_shared_ptr<uXML::Node> node)
	{
		setResultNode(node);
	}

	////////////////////////////////////////////////
	// Request
	////////////////////////////////////////////////

public:

	void setResultNode(cyber_shared_ptr<uXML::Node> node)
	{
		resultNode = node;
	}

	cyber_shared_ptr<uXML::Node> getResultNode()
	{
		return resultNode;
	}

	////////////////////////////////////////////////
	// ContentNode
	////////////////////////////////////////////////

public:

	int getNContentNodes()
	{
		return resultNode->getNNodes();
	}

	cyber_shared_ptr<uXML::Node> getContentNode(int n)
	{
		return resultNode->getNode(n);
	}

};

}

#endif


