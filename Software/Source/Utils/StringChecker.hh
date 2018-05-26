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

class StringChecker
{
public:
	static bool isEmailValid(const std::string & email);

};