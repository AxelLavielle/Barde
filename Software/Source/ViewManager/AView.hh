/*
  ==============================================================================

    AView.h
    Created: 21 Mar 2017 2:07:07pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef AVIEW_HH_INCLUDED
#define AVIEW_HH_INCLUDED

#include <functional>
#include "../JuceHeader.h"
#include "IView.hpp"

class AView : public IView, public Component
{
public:
	virtual ~AView();
	void setChangeViewCallback(std::function<void(std::string)> changeView);
	void changeView(std::string viewName);

private:
	std::function<void(std::string)>	_viewChanger;
};

#endif  // AVIEW_HH_INCLUDED
