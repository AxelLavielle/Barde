/*
  ==============================================================================

    CmdManager.h
    Created: 13 Mar 2017 1:44:32pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef CMDMANAGER_HH_INCLUDED
#define CMDMANAGER_HH_INCLUDED

#include <sstream>
#include "./RestClient/RestClient.hh"
#include "./RestClient/RestClientException.hh"
#include "User.hh"
#include "Utils/NonCopyable.hpp"

class CmdManager : public NonCopyable
{
public:
	bool connectToServer();
	User getUserInfo();
	bool login(const std::string &email, const std::string & password);
	bool logout();
	bool editUserInfo(const User &user, const std::string & password);
	bool forgetPassword();
	bool createUser(const User & user, const std::string & password);
	bool signUp(const User & user, const std::string & password);
	bool sendComment(const std::string & comment);
	int	getResponseCode() const;
	std::string getResponseMsg() const;

	static CmdManager &getInstance();

private:
	CmdManager();
	void clearResponses();

	RestClient				_socket;
	User					_currentUser;
	int						_responseCode;
	std::string				_responseMsg;

	static CmdManager		_cmdManager;

};



#endif  // CMDMANAGER_HH_INCLUDED
