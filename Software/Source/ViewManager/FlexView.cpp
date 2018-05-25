/*
  ==============================================================================

    FlexView.cpp
    Created: 25 May 2018 1:11:29pm
    Author:  Anthony

  ==============================================================================
*/

#include "FlexView.hh"

void FlexView::resized()
{
	_flexBox.performLayout(getLocalBounds().toFloat());
}
