/*
  ==============================================================================

    CmdManager.cpp
    Created: 13 Mar 2017 1:44:33pm
    Author:  Anthony

  ==============================================================================
*/

#include "CmdManager.hh"

bool CmdManager::connectToServer()
{
	if (_socket.connect("163.172.128.43", 80))
	{
		std::cout << "LALAL" << std::endl;
		std::cout << "Receive = " << _socket.get("/") << std::endl;;
		return true;
	}
	return false;
}
