/*
  ==============================================================================

    TCPSocket.h
    Created: 13 Mar 2017 1:52:11pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef TCPSOCKET_HH_INCLUDED
#define TCPSOCKET_HH_INCLUDED

#include <JuceHeader.h>
#include <sstream>
#include "ASocketManager.hh"

#define TIME_OUT 3000

class TCPSocket : public ASocketManager
{
public:
	~TCPSocket();
	virtual bool connect(const std::string & address, const unsigned int port, unsigned int timeOut = 3000);
	virtual void close();
	virtual std::string read();
	virtual bool write(const std::string &message);
	virtual std::string get(const std::string &uri);
	virtual std::string receive();

private:
	std::string getResponse(const std::string &req);
	std::string parseResponse(const std::string &req);

	StreamingSocket	_socket;
};



#endif  // TCPSOCKET_HH_INCLUDED
