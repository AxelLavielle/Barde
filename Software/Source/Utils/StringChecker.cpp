/*
  ==============================================================================

    StringChecker.cpp
    Created: 26 May 2018 3:05:33pm
    Author:  Anthony

  ==============================================================================
*/

#include "StringChecker.hh"

bool StringChecker::isEmailValid(const std::string &email)
{
	const std::regex pattern
	("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return std::regex_match(email, pattern);
}


bool StringChecker::isNameValid(const std::string &name)
{
	//TODO CHECK ACCENTS ERROR
	const std::regex pattern("^([a-zA-Z'àâéèêôùûçÀÂÉÈÔÙÛÇ-]+)$");
	return std::regex_match(name, pattern);
}


bool StringChecker::isUserNameValid(const std::string &userName)
{
	const std::regex pattern("(\\w+)");
	return std::regex_match(userName, pattern);
}


bool StringChecker::isDateValid(const std::string &date)
{
	const std::regex pattern("^([0-2][0-9]|(3)[0-1])(\\/)(((0)[0-9])|((1)[0-2]))(\\/)\\d{4}$");
	return std::regex_match(date, pattern);

}

	bool StringChecker::isDayValid(const std::string &date)
	{
		const std::regex pattern("^([0-2][0-9]|(3)[0-1])$");
		return std::regex_match(date, pattern);
	}


	bool StringChecker::isMonthValid(const std::string &date)
	{
		const std::regex pattern("^(((0)[0-9])|((1)[0-2]))$");
		return std::regex_match(date, pattern);
	}

	bool StringChecker::isYearValid(const std::string &date)
	{
		const std::regex pattern("^\\d{4}$");
		return std::regex_match(date, pattern);
	}