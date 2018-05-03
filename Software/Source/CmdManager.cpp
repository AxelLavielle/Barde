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
	//api.barde.io
	//_socket.setAddr("163.172.128.43", 2010, 1000);
	//api-dev.barde.io
	_socket.setAddr("163.172.128.43", 2110, 1000);
	return true;
}

User CmdManager::getUserInfo()
{
	Json::Value				root;
	Json::Value				user;
	Json::CharReaderBuilder rbuilder;
	std::string				errs;
	std::stringstream		ss;
	int						responseCode;
	std::string				responseMsg;

	try
	{
		ss << _socket.get("/user/me", responseCode, responseMsg);
	}
	catch (RestClientException &e)
	{
		std::cerr << "Error on request getUserInfo : " << e.what() << std::endl;
	}

	rbuilder["collectComments"] = false;
	
	if (Json::parseFromStream(rbuilder, ss, &root, &errs) == false)
	{
		std::cerr << errs << std::endl;
		//throw; Need to throw something
	}
	user = root["data"]["user"];
	std::cout << "User email : " << user["email"] << std::endl;
	std::cout << "User firstname : " << user["name"]["firstName"] << std::endl;
	std::cout << "User lastname : " << user["name"]["lastName"] << std::endl;
	std::cout << "User username : " << user["name"]["userName"] << std::endl;

	_currentUser.setEmail(user["email"].asString());
	_currentUser.setFirstName(user["name"]["firstName"].asString());
	_currentUser.setLastName(user["name"]["lastName"].asString());
	_currentUser.setUserName(user["name"]["userName"].asString());
	_currentUser.setDateOfBirth(user["dateOfBirth"].asString());
	std::cout << "Date of birth = " << user["dateOfBirth"] << std::endl;
	return _currentUser;
}

bool CmdManager::login(const std::string &email, const std::string &password)
{
	try
	{
		//_socket.authentificate("arnaud.p@outlook.fr", "arnaud");
		return (_socket.authentificate(email, password));
	}
	catch (RestClientException &e)
	{
		std::cerr << "Error on request authentificate : " << e.what() << std::endl;
	}
	return false;
}

bool CmdManager::logout()
{

	return false;
}

bool CmdManager::editUserInfo(const User & user)
{
	Json::Value				root;
	int						responseCode;
	std::string				responseMsg;
	std::stringstream		ssJson;

	_currentUser = user;

	root["email"] = user.getEmail();
	//root["password"] = user.getPassword();
	root["firstName"] = user.getFirstName();
	root["lastName"] = user.getLastName();
	ssJson << root;

	//Need to manage date of birth
	//root[""] = ;

	try
	{
		_socket.patch("/user/", ssJson.str(), responseCode, responseMsg);
	}
	catch (RestClientException &e)
	{
		std::cerr << "Error on request editUserInfo : " << e.what() << std::endl;
	}
	return false;
}

bool CmdManager::forgetPassword()
{
	return false;
}

bool CmdManager::signUp(const User & user, const std::string & password)
{
	Json::Value				root;
	int						responseCode;
	std::string				responseMsg;
	std::stringstream		ssJson;

	_currentUser = user;
	root["email"] = user.getEmail();
	root["password"] = password;
	root["userName"] = user.getUserName();
	root["firstName"] = user.getFirstName();
	root["lastName"] = user.getLastName();
	root["yearOfBirth"] = user.getYearOfBirth();
	root["monthOfBirth"] = user.getMonthOfBirth();
	root["dayOfBirth"] = user.getDayOfBirth();
	ssJson << root;

	try
	{
		_socket.post("/user/register", ssJson.str(), responseCode, responseMsg);
	}
	catch (RestClientException &e)
	{
		std::cerr << "Error on request signUp : " << e.what() << " Message: " << e.getMessage() << " Info : "<< e.getInfo() << std::endl;
	}
	return true;
}
