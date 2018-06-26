/*
  ==============================================================================

    ReportPanel.h
    Created: 25 May 2018 1:00:43pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include "../Factories/GuiFactory.hh"
#include "../ViewManager/FlexView.hh"
#include "../CmdManager.hh"

class ReportPanel : public FlexView, private Button::Listener
{
public:
	ReportPanel();
	void refresh() override;
	void paint(Graphics & g) override;

private:
	void buttonClicked(Button * button) override;

	TextEditor		_commentTextEditor;
	TextButton		_sendButton;
	TextButton		_cancelButton;
	SimpleLabel		_titleLabel;
	SimpleLabel		_errorLabel;

	CmdManager		&_cmdManager;
};