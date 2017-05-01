/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : ImageFormat.h
*
*	Revision:
*
*	04/16/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_IMAGEFORMAT_H_
#define _CLINK_MEDIA_IMAGEFORMAT_H_

#include <media/server/object/format/DefaultFormat.h>

namespace CyberLink {

class ImageFormat : public DefaultFormat
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////
	
public:

	ImageFormat()
	{	
		setFile(NULL);
	}
	
	ImageFormat(File *file)
	{
		setFile(file);
	}

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////
	
public:

	virtual bool equals(File *file) = 0;
	virtual FormatObject *createObject(File *file) = 0;
	virtual const char *getMimeType() = 0;
	
	const char *getMediaClass()
	{
		return "object.item.imageItem.photo";
	}
	
	virtual int getAttributeList(uXML::AttributeList &attrList)
	{
		attrList.clear();
		return attrList.size();
	}

	const char *getCreator(std::string &buf)
	{
		buf = "";
		return buf.c_str();
	}
};

}

#endif
