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
	_isAuthenticated = false;
}

bool RestClient::getToken(const std::string & response)
{
	Json::CharReaderBuilder rbuilder;
	Json::Value				root;
	std::string				errs;
	std::stringstream		ss;

	ss << response;
	rbuilder["collectComments"] = false;

	if (Json::parseFromStream(rbuilder, ss, &root, &errs) == false)
	{
		std::cerr << errs << std::endl;
		return false;
	}
	_token = root["data"]["token"].asString();
	return true;
}

void RestClient::setToken(const std::string & token)
{
	_token = token;
}

bool RestClient::logout()
{
	_isAuthenticated = false;
	return true;
}

bool RestClient::authentificate(const std::string & email, const std::string & password)
{
	std::stringstream	ss;
	std::stringstream	ssJson;
	int					code = 0;
	std::string			responseMessage;
	std::string			response;
	Json::Value			root;

	root["email"] = email;
	root["password"] = password;
	ssJson << root;

	ss << "POST /auth/login" << " HTTP/1.1\r\n";
	ss << "User-Agent: BardeClient/1.0\r\n";
	ss << "Accept: */*\r\n";
	ss << "Host: localhost:8080\r\n";
	ss << "Content-Type: application/json\r\n";
	ss << "Content-Length: " << ssJson.str().length() << "\r\n";
	ss << "Connection: close\r\n";
	ss << "\r\n";

	ss << ssJson.str();

	response = getResponse(ss.str(), code, responseMessage);
	if (code != 200)
		throw RestClientException(response.c_str(), code);
	_isAuthenticated = true;
	getToken(response);
	return true;
}

std::string RestClient::get(const std::string & uri, int & responseCode, std::string & responseMsg)
{
	std::stringstream	ss;

	if (_isAuthenticated == false)
		throw RestClientException("Unauthorized", 401);
	ss << "GET " << uri << " HTTP/1.1\r\n";
	ss << "User-Agent: BardeClient/1.0\r\n";
	ss << "Accept: */*\r\n";
	ss << "Host: localhost:8080\r\n";
	ss << "Connection: close\r\n";
	ss << "Authorization: " << _token;
	ss << "\r\n";
	ss << "\r\n";
	return getResponse(ss.str(), responseCode, responseMsg);
}

std::string RestClient::get(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg)
{
	std::stringstream	ss;

	if (_isAuthenticated == false)
		throw RestClientException("Unauthorized", 401);
	ss << "GET " << uri << " HTTP/1.1\r\n";
	ss << "User-Agent: BardeClient/1.0\r\n";
	ss << "Accept: */*\r\n";
	ss << "Host: localhost:8080\r\n";
	ss << "Connection: close\r\n";
	ss << "Authorization: " << _token;
	ss << "\r\n";
	ss << "\r\n";
	ss << body;
	return getResponse(ss.str(), responseCode, responseMsg);
}

std::string RestClient::post(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg)
{
	std::stringstream	ss;

	//if (_isAuthenticated == false)
	//	throw RestClientException("Unauthorized", 401);
	ss << "POST " << uri << " HTTP/1.1\r\n";
	ss << "User-Agent: BardeClient/1.0\r\n";
	ss << "Accept: */*\r\n";
	ss << "Content-Type: application/json\r\n";
	ss << "Content-Length: " << body.length() << "\r\n";
	ss << "Host: localhost:8080\r\n";
	ss << "Connection: close\r\n";
	ss << "Authorization: " << _token;
	ss << "\r\n";
	ss << "\r\n";
	ss << body;
	return getResponse(ss.str(), responseCode, responseMsg);
}

std::string RestClient::put(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg)
{
	std::stringstream	ss;

	if (_isAuthenticated == false)
		throw RestClientException("Unauthorized", 401);
	ss << "PUT " << uri << " HTTP/1.1\r\n";
	ss << "User-Agent: BardeClient/1.0\r\n";
	ss << "Accept: */*\r\n";
	ss << "Content-Type: application/json\r\n";
	ss << "Content-Length: " << body.length() << "\r\n";
	ss << "Host: localhost:8080\r\n";
	ss << "Connection: close\r\n";
	ss << "Authorization: " << _token;
	ss << "\r\n";
	ss << "\r\n";
	ss << body;
	return getResponse(ss.str(), responseCode, responseMsg);
}

std::string RestClient::patch(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg)
{
	std::stringstream	ss;

	if (_isAuthenticated == false)
		throw RestClientException("Unauthorized", 401);
	ss << "PATCH " << uri << " HTTP/1.1\r\n";
	ss << "User-Agent: BardeClient/1.0\r\n";
	ss << "Accept: */*\r\n";
	ss << "Content-Type: application/json\r\n";
	ss << "Content-Length: " << body.length() << "\r\n";
	ss << "Host: localhost:8080\r\n";
	ss << "Connection: close\r\n";
	ss << "Authorization: " << _token;
	ss << "\r\n";
	ss << "\r\n";
	ss << body;
	return getResponse(ss.str(), responseCode, responseMsg);
}

std::string RestClient::parseResponse(const std::string &req, int & responseCode, std::string & responseMsg)
{
	size_t		lenPos;
	size_t		lenNbPos;
	//	size_t		bodyLen;
	size_t		bodyStartPos;
	size_t		posCode;
	size_t		posEndCode;
	std::string	responseMessageCode;

	if (req.find("Transfer-Encoding: chunked") != std::string::npos) //This type of response is not implented
		throw RestClientException("Chunked transfer encoding not implemented", 501);
	if (req.find("Content-Type: application/json") == std::string::npos) //Only JSON is accepted for now
		throw RestClientException("Content type not implemented", 501);

	if ((posCode = req.find("HTTP/1.1 ")) == std::string::npos) //Manage HTTP error code from server
		throw RestClientException("Bad response", 501);
	posEndCode = req.find("\r\n");
	responseMessageCode = req.substr(posCode + 9, posEndCode - (posCode + 9)); //9 is the lenght of the string "HTTP/1.1 "
	responseCode = std::stoi(req.substr(posCode + 9, 3)); //9 is the lenght of the string "HTTP/1.1 ", 3 is the lenght of the HTTP response code (3 digits)
	responseMsg = req.substr(posCode + 9 + 4, posEndCode - (posCode + 9 + 4));

	if ((lenPos = req.find("Content-Length: ")) == std::string::npos)
		throw RestClientException("Error header format : Content-Length header not found", 400);
	if ((lenNbPos = req.find("\r\n", lenPos)) == std::string::npos)
		throw RestClientException("Bad request : Content-Length empty", 400);
	//bodyLen = std::stoi(req.substr(lenPos + 16, lenNbPos)); //16 is the length of the string "Content-Length: "
	if ((bodyStartPos = req.find("\r\n\r\n")) == std::string::npos)
		throw RestClientException("Bad request", 400);
	bodyStartPos += 4; //4 is the length of the string "\r\n\r\n"
	return (req.substr(bodyStartPos));
}

std::string RestClient::receive(int & responseCode, std::string & responseMsg)
{
	int						socketStatus;
	int						nbByte;
	std::stringstream		msg;
	std::string				responseBody;
	char					buff[1024];


	//std::cout << "Waiting server..." << std::endl;
	nbByte = 1;
	while ((socketStatus = _socket.waitUntilReady(true, _timeOut)) > 0 && nbByte > 0)
	{
		//std::cout << "Reading request..." << std::endl;
		nbByte = _socket.read(buff, 1023, false);
		buff[nbByte] = '\0';
		msg << buff;
	}
	if (socketStatus < 0)
	{
		throw RestClientException("Error on receiving request", 444);
	}
	responseBody = parseResponse(msg.str(), responseCode, responseMsg);
	return (responseBody);
}

std::string RestClient::getResponse(const std::string &req, int & responseCode, std::string & responseMsg)
{
	int				socketStatus;
	std::string		response;

	//std::cout << "Waiting server1..." << std::endl;
	if (_socket.connect(_address, _port, _timeOut) == false)
	{
		throw RestClientException("Can connect to the server", 444);
	}
	socketStatus = _socket.waitUntilReady(false, _timeOut * 2);
	if (socketStatus == 1)
	{
		//std::cout << "Sanding request..." << std::endl;
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
		response = receive(responseCode, responseMsg);
	}
	catch (const RestClientException &e)
	{
		_socket.close();
		throw e;
	}
	_socket.close();
	return response;
}
