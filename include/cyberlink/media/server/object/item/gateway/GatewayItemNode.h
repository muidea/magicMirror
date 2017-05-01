/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : GatewayItemNode.h
*
*	Revision:
*
*	02/12/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_GATEWAYITEMNODE_H_
#define _CLINK_MEDIA_GATEWAYITEMNODE_H_

#include <io/File.h>
#include <io/FileInputStream.h>
#include <media/server/object/item/ItemNode.h>

namespace CyberLink {

class GatewayItemNode : public ItemNode
{
	File *itemFile;

	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	GatewayItemNode();

	////////////////////////////////////////////////
	// File/TimeStamp
	////////////////////////////////////////////////
	
public:

	void setFile(File *file)
	{
		itemFile = file;
	}
	
	File *getFile()
	{
		return itemFile;
	}

	long getFileTimeStamp()
	{
		return itemFile->lastModified();
	}
	
	bool equals(File *file)
	{
		if (itemFile == NULL)
			return false;
		return itemFile->equals(file);
	}

	////////////////////////////////////////////////
	// Abstract methods
	////////////////////////////////////////////////

public:

	const char *getContent(std::string &buf);
	
	long getContentLength()
	{
		return itemFile->length();
	}

	InputStream *getContentInputStream();

	const char *getMimeType();
};

}

#endif


