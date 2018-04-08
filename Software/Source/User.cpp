/*
  ==============================================================================

    User.cpp
    Created: 13 Mar 2017 1:43:59pm
    Author:  Anthony

  ==============================================================================
*/

#include "User.hh"

User::User(const std::string & email, const std::string & userName, const std::string & firstName, const std::string & lastName)
{
	_email = email;
	_userName = userName;
	_firstName = firstName;
	_lastName = lastName;
}

User::User()
{
}

User::~User()
{
}

void User::setFirstName(const std::string & firstName)
{
	_firstName = firstName;
}

void User::setLastName(const std::string & lastName)
{
	_lastName = lastName;
}

void User::setUsertName(const std::string & userName)
{
	_userName = userName;
}

void User::setEmail(const std::string & email)
{
	_email = email;
}

void User::setDateOfBirth(const std::string & dateOfBirth)
{
	_dateOfBirth = dateOfBirth;
}

std::string User::getFirstName() const
{
	return _firstName;
}

std::string User::getLastName() const
{
	return _lastName;
}

std::string User::getUsertName() const
{
	return _userName;
}

std::string User::getEmail() const
{
	return _email;
}

std::string User::getDateOfBirth() const
{
	return _dateOfBirth;
}
