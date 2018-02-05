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
	char msg[1000];

	_socket.read(msg, 1024, false);
	return std::string(msg);
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
	ss << "Connection: keep-alive\n";
	ss << "\n";
	return getResponse(ss.str());
}

std::string TCPSocket::receive()
{
	int						socketStatus;
	int						nbByte;
	std::stringstream		msg;
	char					buff[1024];


	std::cout << "Waiting server..." << std::endl;
	socketStatus = _socket.waitUntilReady(true, TIME_OUT);
	if (socketStatus == 1)
	{
		while ((nbByte = _socket.read(buff, 1023, false)) <= 1023)
		{
			std::cout << "Reading request..." << std::endl;
			buff[nbByte] = '\0';
			std::cout << buff << std::endl;
			msg << buff;
		}
		if (nbByte < 0)
		{
			std::cerr << "Error: can not receive message from server" << std::endl;
		}
		std::cout << "Message received" << std::endl;
	}
	else if (socketStatus == 0)
	{
		std::cerr << "Error: socket timeout" << std::endl;
	}
	else
	{
		std::cerr << "Error: server doesn't respond" << std::endl;
	}
	return (msg.str());
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
