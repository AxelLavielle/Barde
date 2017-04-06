/*
  ==============================================================================

    AView.h
    Created: 21 Mar 2017 2:07:07pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef AVIEW_HH_INCLUDED
#define AVIEW_HH_INCLUDED

#include "IView.hpp"

class AView : public IView
{
public:
	virtual ~AView();
	virtual bool init() = 0;
};

#endif  // AVIEW_HH_INCLUDED
