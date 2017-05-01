/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : GIFPlugIn.h
*
*	Revision:
*
*	06/08/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_MPEGFORMT_H_
#define _CLINK_MEDIA_MPEGFORMT_H_

#include <media/server/object/format/MovieFormat.h>

namespace CyberLink {

class MPEGFormat : public MovieFormat
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	MPEGFormat();
	MPEGFormat(File *file);

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////
	
public:

	bool equals(File *file);
	
	FormatObject *createObject(File *file)
	{
		return new MPEGFormat(file);
	}
	
	const char *getMimeType()
	{
		return "video/mpeg";
	}

	int getAttributeList(uXML::AttributeList &attrList);
};

}

#endif


