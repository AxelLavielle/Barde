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

User::User(const User & user)
{
	*this = user;
}

User & User::operator=(const User & user)
{
	_firstName = user.getFirstName();
	_lastName = user.getLastName();
	_userName = user.getUserName();
	_email = user.getEmail();
	//_dateOfBirth = user.getDateOfBirth();
	return *this;
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

void User::setUserName(const std::string & userName)
{
	_userName = userName;
}


void User::setEmail(const std::string & email)
{
	_email = email;
}


void User::setDayOfBirth(const std::string &dayOfBirth)
{
	_dateOfBirth.setDay(dayOfBirth);
}

void User::setMonthOfBirth(const std::string &monthOfBirth)
{
	_dateOfBirth.setMonth(monthOfBirth);
}

void User::setYearOfBirth(const std::string &yearOfBirth)
{
	_dateOfBirth.setYear(yearOfBirth);
}

void User::setDateOfBirth(const std::string & dateOfBirth)
{
	_dateOfBirth.setISODate(dateOfBirth);
}

std::string User::getFirstName() const
{
	return _firstName;
}

std::string User::getLastName() const
{
	return _lastName;
}

std::string User::getUserName() const
{
	return _userName;
}

std::string User::getEmail() const
{
	return _email;
}

std::string User::getDateOfBirth() const
{
	std::cout << "LLLLLLLLLLLLLLLLLLLLLLAAAAAAAAAAAA ===== " << _dateOfBirth.getIsoDate() << std::endl;
	return _dateOfBirth.getIsoDate();
}

std::string User::getYearOfBirth() const
{
	return _dateOfBirth.getYear();
}

std::string User::getMonthOfBirth() const
{
	return _dateOfBirth.getMonth();
}

std::string User::getDayOfBirth() const
{
	return _dateOfBirth.getDay();
}
