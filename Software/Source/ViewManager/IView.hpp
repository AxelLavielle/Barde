/*
  ==============================================================================

    IView.hpp
    Created: 21 Mar 2017 2:06:55pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef IVIEW_HPP_INCLUDED
#define IVIEW_HPP_INCLUDED

class IView
{
public:
	virtual ~IView() {};
	virtual	bool init() = 0;
};

#endif  // IVIEW_HPP_INCLUDED
