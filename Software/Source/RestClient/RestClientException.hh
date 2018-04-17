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
		RestClientException(const char *msg, const int code = 500, const char* info = "") ;
		const char *getMessage() const;
		int getCode() const;
		const char *getInfo() const;
		virtual const char *what() const noexcept;

	private:
		const char	*_msg;
		const int	_code;
		const char	*_info;
};

#endif
