/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : JPEGFormat.h
*
*	Revision:
*
*	04/18/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_JPEGFORMT_H_
#define _CLINK_MEDIA_JPEGFORMT_H_

#include <media/server/object/format/ImageFormat.h>

namespace CyberLink {

class JPEGFormat : public ImageFormat
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	JPEGFormat();
	JPEGFormat(File *file);

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////
	
public:

	bool equals(File *file);
	
	FormatObject *createObject(File *file)
	{
		return new JPEGFormat(file);
	}
	
	const char *getMimeType()
	{
		return "image/jpeg";
	}
};

}

#endif
