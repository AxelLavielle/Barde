/*
  ==============================================================================

    RestClientException.cpp
    Created: 11 Feb 2018 6:44:10pm
    Author:  Anthony

  ==============================================================================
*/

#include "RestClientException.hh"

RestClientException::RestClientException(const char * msg, const int code, const char * info) : std::exception(msg), _msg(msg), _code(code), _info(info)
{
}

const char * RestClientException::getMessage() const
{
	return _msg;
}

const int RestClientException::getCode() const
{
	return _code;
}

const char * RestClientException::getInfo() const
{
	return _info;
}
