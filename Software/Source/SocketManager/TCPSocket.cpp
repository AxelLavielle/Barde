/*
  ==============================================================================

    TCPSocket.cpp
    Created: 13 Mar 2017 1:52:11pm
    Author:  Anthony

  ==============================================================================
*/

#include "TCPSocket.hh"

TCPSocket::~TCPSocket()
{
}

bool TCPSocket::connect(const std::string & address, const unsigned int port, const unsigned int timeOut)
{
	_address = address;
	_port = port;
	//This can be blocked
	return (_socket.connect(address, port, timeOut));
}

void TCPSocket::close()
{
}

std::string TCPSocket::read()
{
	//char msg[1000];

	//_socket.read(msg, 1024, false);
	return std::string();
}

bool TCPSocket::write(const std::string & message)
{
	return (_socket.write(message.c_str(), strlen(message.c_str())));
}

std::string TCPSocket::get(const std::string & uri)
{
	std::stringstream	ss;

	ss << "GET " << uri << " HTTP/1.1\n";
	ss << "User-Agent: BardeClient/1.0\n";
	ss << "Accept: */*\n";
	ss << "Host: localhost:8080\n";
	ss << "Connection: keep-alive\n"; //I will change that
	ss << "\n";
	return getResponse(ss.str());
}

std::string TCPSocket::parseResponse(const std::string &req)
{
	size_t	lenPos;
	size_t	lenNbPos;
	size_t	bodyLen;
	size_t	bodyStartPos;

	if (req.find("Transfer-Encoding: chunked") != std::string::npos) //This type of response is not implented
	{
		//Raise an exception !!!!!
	}
	if ((lenPos = req.find("Content-Length: ")) == std::string::npos)
	{
		//raise an exception !!!!!!!
	}
	if ((lenNbPos = req.find("\r\n", lenPos)) == std::string::npos)
	{
		//Rais an exception !!!!!!!
	}
	bodyLen = std::stoi(req.substr(lenPos + 16, lenNbPos)); //16 is the length of the string "Content-Length: "
	if ((bodyStartPos = req.find("\r\n\r\n")) == std::string::npos)
	{
		//Raise an exception !!!!!
	}
	bodyStartPos += 4; //4 is the length of the string "\r\n\r\n"
	return (req.substr(bodyStartPos));
}

std::string TCPSocket::receive()
{
	int						socketStatus;
	int						nbByte;
	std::stringstream		msg;
	std::string				responseBody;
	char					buff[1024];


	std::cout << "Waiting server..." << std::endl;
	while ((socketStatus = _socket.waitUntilReady(true, TIME_OUT) > 0))
	{
		std::cout << "Reading request..." << std::endl;
		nbByte = _socket.read(buff, 1023, false);
		buff[nbByte] = '\0';
		msg << buff;
	}
	if (socketStatus < 0)
	{
		std::cerr << "Error: server doesn't respond" << std::endl;

		//Raise an exception !!!!!!
	}
	responseBody = parseResponse(msg.str()); //If this function raise an exception, the response format is bad
	return (responseBody);
}

std::string TCPSocket::getResponse(const std::string &req)
{
	int	socketStatus;

	std::cout << "Waiting server..." << std::endl;
	socketStatus = _socket.waitUntilReady(false, TIME_OUT);
	if (socketStatus == 1)
	{
		std::cout << "Sanding request..." << std::endl;
		if (_socket.write(req.c_str(), strlen(req.c_str())) > -1)
		{
			std::cout << "Request sent with success" << std::endl;
		}
		else
		{
			std::cerr << "Error: can not send request" << std::endl;
		}
	}
	else if (socketStatus == 0)
	{
		std::cerr << "Error: socket timeout" << std::endl;
	}
	else
	{
		std::cerr << "Error: server doesn't respond" << std::endl;
	}
	return receive();
}
