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

	GuiFactory::initLabeledTextBox("Login", "", _userNameTextBox);
	addFlexItem(_userNameTextBox, 400, 50, FlexItem::AlignSelf::stretch, 1);

	GuiFactory::initLabeledTextBox("Password", "", _passwordTextBox);
	addFlexItem(_passwordTextBox, 400, 50, FlexItem::AlignSelf::stretch, 1);

	_flexBox = GuiFactory::createFlexBox(FlexBox::JustifyContent::center, FlexBox::AlignContent::center, FlexBox::AlignItems::stretch, FlexBox::Direction::column, _items, 500, 50);
}

void LoginPanel::buttonClicked(Button * button)
{
}
