/*
  ==============================================================================

    CmdManager.h
    Created: 13 Mar 2017 1:44:32pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef CMDMANAGER_HH_INCLUDED
#define CMDMANAGER_HH_INCLUDED

#include <sstream>
#include "json/json.h"
#include "./SocketManager/RestClient.hh"
#include "./SocketManager/RestClientException.hh"

class CmdManager
{
public:
	bool connectToServer();
	bool getUserInfo();

private:
	RestClient	_socket;
};



#endif  // CMDMANAGER_HH_INCLUDED
