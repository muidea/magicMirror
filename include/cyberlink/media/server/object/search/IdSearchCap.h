/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File: IdSearchCap.h
*
*	Revision;
*
*	08/07/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_IDSEARXHCAP_H_
#define _CLINK_MEDIA_IDSEARXHCAP_H_

#include <media/server/UPnP.h>
#include <media/server/object/SearchCap.h>
#include <media/server/object/SearchCriteria.h>

namespace CyberLink {

class IdSearchCap : public SearchCap 
{
public:

	IdSearchCap() 
	{
	}
	
	const char *getPropertyName() 
	{
		return SearchCriteria::ID;
	}

	bool compare(SearchCriteria *searchCri, ContentNode *conNode);
};

}

#endif


