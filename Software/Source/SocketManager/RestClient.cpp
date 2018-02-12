/*
  ==============================================================================

    RestClient.cpp
    Created: 13 Mar 2017 1:52:11pm
    Author:  Anthony

  ==============================================================================
*/

#include "RestClient.hh"

RestClient::~RestClient()
{
}

void RestClient::setAddr(const std::string & address, const unsigned int port, const unsigned int timeOut)
{
	_address = address;
	_port = port;
	_timeOut = timeOut;
}

std::string RestClient::get(const std::string & uri)
{
	std::stringstream	ss;

	ss << "GET " << uri << " HTTP/1.1\n";
	ss << "User-Agent: BardeClient/1.0\n";
	ss << "Accept: */*\n";
	ss << "Host: localhost:8080\n";
	ss << "Connection: close\n";
	ss << "\n";
	return getResponse(ss.str());
}

std::string RestClient::parseResponse(const std::string &req)
{
	size_t	lenPos;
	size_t	lenNbPos;
	size_t	bodyLen;
	size_t	bodyStartPos;

	if (req.find("Transfer-Encoding: chunked") != std::string::npos) //This type of response is not implented
	{
		throw RestClientException("Chunked transfer encoding not implemented", 501);
	}
	if (req.find("Content-Type: application/json") == std::string::npos) //Only JSON is accepted for now
	{
		throw RestClientException("Content type not implemented", 501);
	}
	if ((lenPos = req.find("Content-Length: ")) == std::string::npos)
	{
		throw RestClientException("Error header format : Content-Length header not found", 400);
	}
	if ((lenNbPos = req.find("\r\n", lenPos)) == std::string::npos)
	{
		throw RestClientException("Bad request : Centent-length empty", 400);
	}
	bodyLen = std::stoi(req.substr(lenPos + 16, lenNbPos)); //16 is the length of the string "Content-Length: "
	if ((bodyStartPos = req.find("\r\n\r\n")) == std::string::npos)
	{
		throw RestClientException("Bad request", 400);
	}
	bodyStartPos += 4; //4 is the length of the string "\r\n\r\n"
	return (req.substr(bodyStartPos));
}

std::string RestClient::receive()
{
	int						socketStatus;
	int						nbByte;
	std::stringstream		msg;
	std::string				responseBody;
	char					buff[1024];


	std::cout << "Waiting server..." << std::endl;
	nbByte = 1;
	while ((socketStatus = _socket.waitUntilReady(true, _timeOut) > 0) && nbByte > 0)
	{
		std::cout << "Reading request..." << std::endl;
		nbByte = _socket.read(buff, 1023, false);
		buff[nbByte] = '\0';
		msg << buff;
	}
	if (socketStatus < 0)
	{
		throw RestClientException("Error on receiving request", 444);
	}
	responseBody = parseResponse(msg.str());
	return (responseBody);
}

std::string RestClient::getResponse(const std::string &req)
{
	int				socketStatus;
	std::string		response;

	std::cout << "Waiting server1..." << std::endl;
	if (_socket.connect(_address, _port, _timeOut) == false)
	{
		throw RestClientException("Can connect to the server", 444);
	}
	socketStatus = _socket.waitUntilReady(false, _timeOut * 2);
	if (socketStatus == 1)
	{
		std::cout << "Sanding request..." << std::endl;
		if (_socket.write(req.c_str(), strlen(req.c_str())) <= -1)
		{
			throw RestClientException("Error on sending request", 444);
		}
	}
	else if (socketStatus == 0)
	{
		throw RestClientException("Error on sending request : connection time out", 444);
	}
	else
	{
		throw RestClientException("Error on sending request : server doesn't respond", 444);
	}
	try {
		response = receive();
	}
	catch (const RestClientException &e)
	{
		throw e;
		_socket.close();
	}
	_socket.close();
	return response;
}
