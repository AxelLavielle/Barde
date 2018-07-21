/*
  ==============================================================================

    ASocketManager.h
    Created: 13 Mar 2017 1:51:58pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef ASOCKETMANAGER_H_INCLUDED
#define ASOCKETMANAGER_H_INCLUDED

#include "IRestClient.hpp"

class ARestTClient : public IRestTClient
{
public:
	virtual ~ARestTClient();
	virtual std::string getAddress() const;
	virtual unsigned int getPort() const;
	virtual void setAddr(const std::string & address, const unsigned int port,  unsigned int timeOut) = 0;
	virtual std::string get(const std::string &uri, int & responseCode, std::string & responseMsg) = 0;
	virtual std::string post(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg) = 0;
	virtual std::string put(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg) = 0;
	virtual std::string patch(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg) = 0;

protected:
	std::string _address;
	unsigned int _port;
	unsigned int _timeOut;
};


#endif  // ASOCKETMANAGER_H_INCLUDED
