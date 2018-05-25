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
	bool editUserInfo(const User &user);
	bool forgetPassword();
	bool createUser(const User & user, const std::string & password);
	bool signUp(const User & user, const std::string & password);


private:
	RestClient				_socket;
	User					_currentUser;
};



#endif  // CMDMANAGER_HH_INCLUDED
