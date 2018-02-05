/*
  ==============================================================================

    ASocketManager.cpp
    Created: 13 Mar 2017 1:51:58pm
    Author:  Anthony

  ==============================================================================
*/

#include "ASocketManager.hh"

ASocketManager::~ASocketManager()
{
}

std::string ASocketManager::getAddress() const
{
	return _address;
}

unsigned int ASocketManager::getPort() const
{
	return _port;
}

//void ASocketManager::setAddress(const std::string & address)
//{
//	_address = address;
//}
//
//void ASocketManager::setPort(const unsigned int & port)
//{
//	_port = port;
//}
