/*
  ==============================================================================

    LoginPanel.hh
    Created: 21 Jun 2018 11:48:03am
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "../Factories/GuiFactory.hh"
#include "../ViewManager/FlexView.hh"
#include "LabeledTextBox.hh"

class LoginPanel : public FlexView, private Button::Listener
{
public:
	LoginPanel();

private:
	LabeledTextBox		_userNameTextBox;
	LabeledTextBox		_passwordTextBox;

};