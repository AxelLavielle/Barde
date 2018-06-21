/*
  ==============================================================================

    LoginPanel.cpp
    Created: 21 Jun 2018 11:47:53am
    Author:  Anthony

  ==============================================================================
*/

#include "LoginPanel.hh"

LoginPanel::LoginPanel()
{


	_flexBox = GuiFactory::createFlexBox(FlexBox::JustifyContent::center, FlexBox::AlignContent::center, FlexBox::AlignItems::stretch, FlexBox::Direction::column, _items, 500, 50);
}
