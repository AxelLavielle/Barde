/*
  ==============================================================================

    ReportPanel.cpp
    Created: 25 May 2018 1:00:43pm
    Author:  Anthony

  ==============================================================================
*/

#include "ReportPanel.hh"

ReportPanel::ReportPanel() : _cmdManager(CmdManager::getInstance())
{
	GuiFactory::initBigTitle("Enter your comment", _titleLabel);
	addAndMakeVisible(_titleLabel);

	GuiFactory::initLittleTitle("", _errorLabel);
	_errorLabel.setColour(Label::textColourId, Colours::red);
	addAndMakeVisible(_errorLabel);

	addAndMakeVisible(_commentTextEditor);

	_sendButton.setButtonText("Send comment");
	_sendButton.setName("Send");
	_sendButton.addListener(this);
	addAndMakeVisible(_sendButton);

	_cancelButton.setButtonText("Cancel");
	_cancelButton.setName("Cancel");
	_cancelButton.addListener(this);
	addAndMakeVisible(_cancelButton);

	_flexBox = GuiFactory::createFlexBox(FlexBox::JustifyContent::center, FlexBox::AlignContent::center, FlexBox::AlignItems::center, FlexBox::Direction::column,
											{ GuiFactory::createFlexItem(_titleLabel, 1000, 55), GuiFactory::createFlexItem(_errorLabel, 500, 20), GuiFactory::createFlexItem(_commentTextEditor, 1000, 400), GuiFactory::createFlexItem(_sendButton, 100, 50, FlexItem::AlignSelf::flexEnd), GuiFactory::createFlexItem(_cancelButton, 100, 50, FlexItem::AlignSelf::flexEnd) } );
}

void ReportPanel::buttonClicked(Button * button)
{
	if (button->getName() == "Send")
	{
		_errorLabel.setLabelText("");
		if (_commentTextEditor.getText() == "")
		{
			_errorLabel.setLabelText("Please enter a commment.");
			return;
		}
		try
		{
			_cmdManager.sendComment(_commentTextEditor.getText().toStdString());
		}
		catch (RestClientException &e)
		{
			_errorLabel.setLabelText("Connection error.");
		}
		_errorLabel.setColour(Label::textColourId, Colours::black);
		_errorLabel.setLabelText("Comment sent.");
		_commentTextEditor.setText("");
	}
	else if (button->getName() == "Cancel")
	{
		changeView("Player");
	}

}
