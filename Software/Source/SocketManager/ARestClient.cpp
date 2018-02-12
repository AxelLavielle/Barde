/*
  ==============================================================================

    ARestTClient.cpp
    Created: 13 Mar 2017 1:51:58pm
    Author:  Anthony

  ==============================================================================
*/

#include "ARestClient.hh"

ARestTClient::~ARestTClient()
{
}

std::string ARestTClient::getAddress() const
{
	return _address;
}

unsigned int ARestTClient::getPort() const
{
	return _port;
}

//void ARestTClient::setAddress(const std::string & address)
//{
//	_address = address;
//}
//
//void ARestTClient::setPort(const unsigned int & port)
//{
//	_port = port;
//}
