/*
  ==============================================================================

    AComponent.h
    Created: 2 May 2018 6:09:43pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include <functional>
#include <map>
#include "../JuceLibraryCode/JuceHeader.h"

class AComponent : public Component
{
public:
	virtual ~AComponent() {};
	virtual void setChangeViewCallback(std::function<void(std::string)> changeView);
	virtual void changeView(std::string viewName);

private:
	std::function<void(std::string)>	_viewChanger;
};