/*
  ==============================================================================

    StringChecker.h
    Created: 26 May 2018 3:05:33pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include <string>
#include <regex>
#include <chrono>
#include <string>


class StringChecker
{
public:
	static bool isEmailValid(const std::string & email);
	static bool isNameValid(const std::string & name);
	static bool isUserNameValid(const std::string & userName);
	static bool isDateValid(const std::string & date);
	static bool isDayValid(const std::string & date);
	static bool isMonthValid(const std::string & date);
	static bool isYearValid(const std::string & date);
	static bool isDateInPast(const std::string &date);
	static bool isPasswordValid(const std::string &password);
	static bool isPasswordLongEnough(const std::string &password);
	static bool containsUppercase(const std::string &password);
	static bool containsLowercase(const std::string &password);
	static bool containsNumber(const std::string &password);
	static bool containsSpecialChar(const std::string &password);
};