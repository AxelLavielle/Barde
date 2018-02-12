/*
  ==============================================================================

    CmdManager.cpp
    Created: 13 Mar 2017 1:44:33pm
    Author:  Anthony

  ==============================================================================
*/

#include "CmdManager.hh"

bool CmdManager::connectToServer()
{
	_socket.setAddr("163.172.128.43", 2010, 1000);
	getUserInfo();
	return true;
}

bool CmdManager::getUserInfo()
{
	Json::Value	root;
	Json::Value	user;
	Json::CharReaderBuilder rbuilder;
	std::string errs;
	std::stringstream ss;

	try
	{
		ss << _socket.get("/user/xavier.pe@outlook.fr");
	}
	catch (RestClientException &e)
	{
		std::cerr << "Error on request getUserInfo : " << e.what() << std::endl;
	}

	rbuilder["collectComments"] = false;
	Json::parseFromStream(rbuilder, ss, &root, &errs);
	user = root["data"]["user"];
	std::cout << "User email : " << user["email"] << std::endl;
	std::cout << "User firstname : " << user["name"]["firstName"] << std::endl;
	std::cout << "User lastname : " << user["name"]["lastName"] << std::endl;
	std::cout << "User username : " << user["name"]["userName"] << std::endl;
	return true;
}
