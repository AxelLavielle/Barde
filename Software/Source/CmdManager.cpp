/*
  ==============================================================================

    CmdManager.cpp
    Created: 13 Mar 2017 1:44:33pm
    Author:  Anthony

  ==============================================================================
*/

#include "CmdManager.hh"

CmdManager CmdManager::_cmdManager;

CmdManager::CmdManager()
{
}

void CmdManager::clearResponses()
{
	_responseCode = 0;
	_responseMsg = "";
}

bool CmdManager::connectToServer()
{
	//api.barde.io prod
	_socket.setAddr("163.172.191.206", 2100, 5000);
	//api.barder.io dev -> test
	//_socket.setAddr("163.172.128.43", 3000, 5000);
	return true;
}

User CmdManager::getUserInfo()
{
	Json::Value				root;
	Json::Value				user;
	Json::CharReaderBuilder rbuilder;
	std::string				errs;
	std::stringstream		ss;

	try
	{
		clearResponses();
		ss << _socket.get("/user/me", _responseCode, _responseMsg);
	}
	catch (RestClientException &e)
	{
		std::cerr << "Error on request getUserInfo : " << e.what() << std::endl;
		throw RestClientException(_responseMsg.c_str() , _responseCode);
	}

	rbuilder["collectComments"] = false;
	
	if (Json::parseFromStream(rbuilder, ss, &root, &errs) == false)
	{
		std::cerr << errs << std::endl;
		//throw; Need to throw something
	}
	user = root["data"]["user"];
	_currentUser.setEmail(user["email"].asString());
	_currentUser.setFirstName(user["name"]["firstName"].asString());
	_currentUser.setLastName(user["name"]["lastName"].asString());
	_currentUser.setUserName(user["name"]["userName"].asString());
	_currentUser.setDateOfBirth(user["dateOfBirth"].asString());
	_currentUser.setRole(user["role"].asString());
	return _currentUser;
}

bool CmdManager::login(const std::string &email, const std::string &password)
{
	try
	{
		return (_socket.authentificate(email, password));
	}
	catch (RestClientException &e)
	{
		std::cerr << "Error on request authentificate : " << e.what() << std::endl;
		_responseMsg = e.getMessage();
		_responseCode = e.getCode();
		return false;
	}
}



//bool CmdManager::forgotPassword(const std::string & email)
//{
	//TODO
//}






bool CmdManager::logout()
{
	_socket.logout();
	return true;
}

bool CmdManager::editUserInfo(const User & user, const std::string & password)
{
	Json::Value				root;
	std::stringstream		ssJson;

	_currentUser = user;

	root["email"] = user.getEmail();
	root["firstName"] = user.getFirstName();
	root["lastName"] = user.getLastName();
	root["dayOfBirth"] = user.getDayOfBirth();
	root["monthOfBirth"] = user.getMonthOfBirth();
	root["yearOfBirth"] = user.getYearOfBirth();
	if (password != "")
		root["password"] = password;
	ssJson << root;

	try
	{
		clearResponses();
		_socket.patch("/user/", ssJson.str(), _responseCode, _responseMsg);
	}
	catch (RestClientException &e)
	{
		std::cerr << "Error on request editUserInfo : " << e.what() << std::endl;
		return false;
	}
	return true;
}

/*bool CmdManager::forgetPassword(const std::string & password)
{
	Json::Value				root;
	std::stringstream		ssJson;


	root["email"] = password;
	ssJson << root;

	try
	{
		clearResponses();
		_socket.get("/user/password/reset", ssJson.str(), _responseCode, _responseMsg);
	}
	catch (RestClientException &e)
	{
		std::cerr << "Error on request resetUserPassword : " << e.what() << std::endl;
		return false;
	}
	return true;
}*/

bool CmdManager::createUser(const User & user, const std::string & password)
{
	//Json::Value				root;
	//std::stringstream		ssJson;

	//root["email"] = user.getEmail();
	//root["password"] = password;
	//root["userName"] = user.getUserName();
	//root["firstName"] = user.getFirstName();
	//root["lastName"] = user.getLastName();
	//root["yearOfBirth"] = user.getYearOfBirth();
	//root["monthOfBirth"] = user.getMonthOfBirth();
	//root["dayOfBirth"] = user.getDayOfBirth();
	//ssJson << root;

	//try
	//{
	//	clearResponses();
	//	_socket.post("/auth/register", ssJson.str(), _responseCode, _responseMsg);
	//	if (_responseCode != 200)
	//	{
	//		std::cerr << _responseMsg << std::endl;
	//		return false;
	//	}
	//}
	//catch (RestClientException &e)
	//{
	//	std::cerr << "Error on request createUser : " << e.what() << " Message: " << e.getMessage() << " Info : " << e.getInfo() << std::endl;
	//	return false;
	//}
	//return true;
	return false;
}

bool CmdManager::signUp(const User & user, const std::string & password)
{
	Json::Value				root;
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
		clearResponses();
		_socket.post("/auth/register", ssJson.str(), _responseCode, _responseMsg);
		if (_responseCode != 200)
			return false;
		if (_socket.authentificate(user.getEmail(), password) == false)
			return false;
	}
	catch (RestClientException &e)
	{
		std::cerr << "Error on request signUp : " << e.what() << " Message: " << e.getMessage() << " Info : "<< e.getInfo() << std::endl;
		return false;
	}
	return true;
}

bool CmdManager::sendComment(const std::string & comment)
{
	Json::Value				root;
	std::stringstream		ssJson;

	root["description"] = comment;
	ssJson << root;

	try
	{
		_socket.post("/report", ssJson.str(), _responseCode, _responseMsg);
	}
	catch (RestClientException &e)
	{
		std::cerr << "Error on request signUp : " << e.what() << " Message: " << e.getMessage() << " Info : " << e.getInfo() << std::endl;
		return false;
	}

	return true;
}

int CmdManager::getResponseCode() const
{
	return _responseCode;
}

std::string CmdManager::getResponseMsg() const
{
	return _responseMsg;
}

CmdManager & CmdManager::getInstance()
{
	return _cmdManager;
}
