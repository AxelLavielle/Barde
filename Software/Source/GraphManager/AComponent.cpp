/*
  ==============================================================================

    AComponent.cpp
    Created: 2 May 2018 6:09:27pm
    Author:  Anthony

  ==============================================================================
*/

#include "AComponent.hh"

void AComponent::setChangeViewCallback(std::function<void(std::string)> changeView)
{
	_viewChanger = changeView;
}

void AComponent::changeView(std::string viewName)
{
	_viewChanger(viewName);
}

void AComponent::refresh()
{
}
