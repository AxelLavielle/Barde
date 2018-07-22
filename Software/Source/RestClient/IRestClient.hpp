/*
  ==============================================================================

    ISockerManager.hpp
    Created: 13 Mar 2017 1:51:42pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef ISOCKERMANAGER_HPP_INCLUDED
#define ISOCKERMANAGER_HPP_INCLUDED

#include <string>
#include "../Utils/NonCopyable.hpp"

class IRestTClient : public NonCopyable
{
public:
	virtual void setAddr(const std::string & address, const unsigned int port, unsigned int timeOut) = 0;
	virtual std::string get(const std::string &uri, int & responseCode, std::string & responseMsg) = 0;
	virtual std::string post(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg) = 0;
	virtual std::string put(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg) = 0;
	virtual std::string patch(const std::string & uri, const std::string & body, int & responseCode, std::string & responseMsg) = 0;
};


#endif  // ISOCKERMANAGER_HPP_INCLUDED
