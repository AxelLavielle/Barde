/*
  ==============================================================================

    CmdManager.h
    Created: 13 Mar 2017 1:44:32pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef CMDMANAGER_HH_INCLUDED
#define CMDMANAGER_HH_INCLUDED

#include "./SocketManager/TCPSocket.hh"

class CmdManager
{
public:
	bool connectToServer();

private:
	TCPSocket	_socket;
};



#endif  // CMDMANAGER_HH_INCLUDED
