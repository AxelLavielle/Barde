/*
  ==============================================================================

    ASocketManager.h
    Created: 13 Mar 2017 1:51:58pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef ASOCKETMANAGER_H_INCLUDED
#define ASOCKETMANAGER_H_INCLUDED

#include "ISocketManager.hpp"
#include <string>

class ASocketManager : public ISocketManager
{
public:
	virtual ~ASocketManager();
	virtual std::string getAddress() const;
	virtual unsigned int getPort() const;
	virtual bool connect(const std::string & address, const unsigned int port,  unsigned int timeOut) = 0;
	virtual bool write(const std::string &message) = 0;
	virtual std::string read() = 0;
	virtual void close() = 0;

protected:
	std::string _address;
	unsigned int _port;
};


#endif  // ASOCKETMANAGER_H_INCLUDED
