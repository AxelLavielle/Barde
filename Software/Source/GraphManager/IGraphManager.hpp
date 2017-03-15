/*
  ==============================================================================

    IGraphManager.hpp
    Created: 6 Mar 2017 12:08:36pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef IGRAPHMANAGER_HPP_INCLUDED
#define IGRAPHMANAGER_HPP_INCLUDED

class IGraphManager
{
public:
	virtual ~IGraphManager() {};
	virtual int init(void) = 0;
};



#endif  // IGRAPHMANAGER_HPP_INCLUDED
