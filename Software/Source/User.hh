/*
  ==============================================================================

    User.h
    Created: 13 Mar 2017 1:43:59pm
    Author:  Anthony

  ==============================================================================
*/

//#include "./RestClient/RestClient.hh"
#include "./RestClient/RestClient.hh"

#ifndef USER_HH_INCLUDED
#define USER_HH_INCLUDED

class User
{
public:
	User(const std::string &email, const std::string &userName, const std::string &firstName, const std::string & lastName);
	User();
	~User();
	void setFirstName(const std::string &firstName);
	void setLastName(const std::string &lastName);
	void setUsertName(const std::string &userName);
	void setEmail(const std::string &email);
	void setDateOfBirth(const std::string &dateOfBirth);
	std::string getFirstName() const;
	std::string getLastName() const;
	std::string getUsertName() const;
	std::string getEmail() const;
	std::string getDateOfBirth() const;

private:
	std::string _firstName;
	std::string _lastName;
	std::string _userName;
	std::string _email;
	std::string	_dateOfBirth;
};

#endif  // USER_HH_INCLUDED
