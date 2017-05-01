/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File: ItemNodeList.h
*
*	Revision;
*
*	03/26/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITEMNODELIST_H_
#define _CLINK_MEDIA_ITEMNODELIST_H_

#include <util/Vector.h>
#include <media/server/object/item/ItemNode.h>

namespace CyberLink {

class ItemNodeList : public Vector<ItemNode>
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	ItemNodeList() 
	{
	}

	~ItemNodeList() 
	{
		clear();
	}
	
	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:
	
	ItemNode *getItemNode(int n)
	{
		return (ItemNode *)Vector::get(n);
	}

	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif




