/*
  ==============================================================================

    ListItemComponent.cpp
    Created: 29 Apr 2018 3:47:39pm
    Author:  Oreo

  ==============================================================================
*/

#include "ListItemComponent.h"


ListItemComponent::ListItemComponent()
{
	_text = "";
	_isSelected = false;
}

ListItemComponent::~ListItemComponent()
{

}

void ListItemComponent::paint(Graphics& g)
{
	if (_isSelected)
	{
		g.setColour(Colours::blue);
		g.fillAll();
	}
}

String ListItemComponent::getText()
{
	return _text;
}

void ListItemComponent::setText(String text)
{
	_text = text;
}


bool ListItemComponent::isSelected()
{
	return _isSelected;
}


void ListItemComponent::setSelected(bool selected)
{
	_isSelected = selected;
}
