/*
  ==============================================================================

    RestClientException.h
    Created: 11 Feb 2018 6:43:36pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef __RESTCLIENT_HH__
#define __RESTCLIENT_HH__

#include <exception>

class RestClientException : public std::exception
{
	public:
		RestClientException(const char *msg, const int code = 500, const char* info = "");
		const char *getMessage() const;
		const int getCode() const;
		const char*getInfo() const;

	private:
		const char	*_msg;
		const char	*_info;
		const int	_code;
};

#endif