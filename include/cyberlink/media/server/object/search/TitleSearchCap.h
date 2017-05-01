/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File: TitleSearchCap.h
*
*	Revision;
*
*	08/21/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_TITLESEARCHCAP_H_
#define _CLINK_MEDIA_TITLESEARCHCAP_H_

#include <media/server/UPnP.h>
#include <media/server/object/SearchCap.h>
#include <media/server/object/SearchCriteria.h>

namespace CyberLink {

class TitleSearchCap : public SearchCap 
{
public:

	TitleSearchCap() 
	{
	}
	
	const char *getPropertyName() 
	{
		return SearchCriteria::TITLE;
	}

	bool compare(SearchCriteria *searchCri, ContentNode *conNode);
};

}

#endif


