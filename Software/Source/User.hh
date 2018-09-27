/*
  ==============================================================================

    User.h
    Created: 13 Mar 2017 1:43:59pm
    Author:  Anthony

  ==============================================================================
*/

//#include "./RestClient/RestClient.hh"
#include "./RestClient/RestClient.hh"
#include "DateTime.hh"

#ifndef USER_HH_INCLUDED
#define USER_HH_INCLUDED

class User
{
public:
	User(const std::string &email, const std::string &userName, const std::string &firstName, const std::string & lastName);
	User();
	User(const User & user);
	User & operator=(const User & user);
	~User();
	void setFirstName(const std::string &firstName);
	void setLastName(const std::string &lastName);
	void setUserName(const std::string &userName);
	void setDayOfBirth(const std::string &dayOfBirth);
	void setMonthOfBirth(const std::string &monthOfBirth);
	void setYearOfBirth(const std::string &yearOfBirth);
	void setEmail(const std::string &email);
	void setDateOfBirth(const std::string &dateOfBirth);
	void setRole(const std::string &role);

	std::string getFirstName() const;
	std::string getLastName() const;
	std::string getUserName() const;
	std::string getEmail() const;
	std::string getDateOfBirth() const;
	std::string getYearOfBirth() const;
	std::string getMonthOfBirth() const;
	std::string getDayOfBirth() const;
	std::string getRole() const;
	DateTime getDateOfBirthObject() const;

private:
	std::string _firstName;
	std::string _lastName;
	std::string _userName;
	std::string _email;
	std::string _role;
	DateTime	_dateOfBirth;
};

#endif  // USER_HH_INCLUDED
