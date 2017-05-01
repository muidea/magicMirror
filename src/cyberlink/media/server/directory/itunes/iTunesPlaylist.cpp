/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File: iTunesPlaylistList.cpp
*
*	Revision:
*
*	03/13/06
*		- first revision.
*
******************************************************************/

#ifdef SUPPORT_ITUNES

#include <media/server/directory/itunes/iTunesPlaylist.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

iTunesPlaylist::iTunesPlaylist(uXML::Node *node)
{
	setNode(node);
	playlistItemList = new iTunesPlaylistItemList();
}

iTunesPlaylist::~iTunesPlaylist()
{
	delete playlistItemList;
}

#endif
