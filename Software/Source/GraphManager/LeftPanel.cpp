/*
  ==============================================================================

    LeftPanel.cpp
    Created: 24 May 2018 6:37:24pm
    Author:  Anthony

  ==============================================================================
*/

#include "LeftPanel.hh"

LeftPanel::LeftPanel()
{
   Image logo = ImageCache::getFromMemory (BinaryData::logo_png,    
										      BinaryData::logo_pngSize);
   _logoImage.setImage(logo);
   addAndMakeVisible(_logoImage);

   _flexBox = GuiFactory::createFlexBox(FlexBox::JustifyContent::flexStart, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::Direction::column,
	   { GuiFactory::createFlexItem(_logoImage, LOGO_WIDTH, LOGO_HEIGHT, 0, 0, FlexItem::AlignSelf::autoAlign, 1) });
}

void LeftPanel::paint(Graphics & g)
{
	g.fillAll(Colours::grey);
}

void LeftPanel::resized()
{
	_flexBox.performLayout(getLocalBounds().toFloat());
}
