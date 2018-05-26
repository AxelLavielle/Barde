/*
  ==============================================================================

    ReportPanel.h
    Created: 25 May 2018 1:00:43pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "../ViewManager/FlexView.hh"
#include "../Factories/GuiFactory.hh"

class ReportPanel : public FlexView, private Button::Listener
{
public:
	ReportPanel();

private:
	void buttonClicked(Button * button) override;

	TextEditor		_commentTextEditor;
	TextButton		_sendButton;
	TextButton		_cancelButton;
	SimpleLabel		_titleLabel;
};