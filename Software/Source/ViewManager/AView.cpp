/*
  ==============================================================================

    AView.cpp
    Created: 21 Mar 2017 2:07:07pm
    Author:  Anthony

  ==============================================================================
*/

#include "AView.hh"

AView::~AView()
{
}

void AView::setChangeViewCallback(std::function<void(std::string)> changeView)
{
	_viewChanger = changeView;
}

void AView::changeView(std::string viewName)
{
	_viewChanger(viewName);
}
