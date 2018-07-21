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
	void buttonClicked(Button * button) override;

private:
	SimpleLabel			_introductionLabel;
	LabeledTextBox		_userNameTextBox;
	LabeledTextBox		_passwordTextBox;
};