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