/*
  ==============================================================================

    TCPSocket.h
    Created: 13 Mar 2017 1:52:11pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef TCPSOCKET_HH_INCLUDED
#define TCPSOCKET_HH_INCLUDED

#include "JuceHeader.h"
#include <sstream>
#include "json/json.h"
#include "ARestClient.hh"
#include "RestClientException.hh"

class RestClient : public ARestTClient
{
public:
	~RestClient();
	virtual void setAddr(const std::string & address, const unsigned int port, unsigned int timeOut = 3000);
	bool getToken(const std::string & response);
	void setToken(const std::string & token);
	bool logout();
	bool authentificate(const std::string & email, const std::string & password);
	virtual std::string get(const std::string &uri, int & responseCode, std::string & responseMsg);
	std::string post(const std::string & uri, int & responseCode, std::string & responseMsg);
	virtual std::string receive(int & responseCode, std::string & responseMsg);
	virtual std::string post(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg);
	virtual std::string put(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg);
	virtual std::string patch(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg);

private:
	std::string getResponse(const std::string &req, int & responseCode, std::string & responseMsg);
	std::string parseResponse(const std::string &req, int & responseCode, std::string & responseMsg);

	StreamingSocket		_socket;
	std::string			_token;
	bool				_isAuthenticated;
};



#endif  // TCPSOCKET_HH_INCLUDED
