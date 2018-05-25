/*
  ==============================================================================

    ReportPanel.cpp
    Created: 25 May 2018 1:00:43pm
    Author:  Anthony

  ==============================================================================
*/

#include "ReportPanel.hh"

ReportPanel::ReportPanel()
{
	GuiFactory::initBigTitle("Enter your comment", _titleLabel);
	addAndMakeVisible(_titleLabel);

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
											{ GuiFactory::createFlexItem(_titleLabel, 1000, 55), GuiFactory::createFlexItem(_commentTextEditor, 1000, 400), GuiFactory::createFlexItem(_sendButton, 100, 50, FlexItem::AlignSelf::flexEnd), GuiFactory::createFlexItem(_cancelButton, 100, 50, FlexItem::AlignSelf::flexEnd) } );
}

void ReportPanel::buttonClicked(Button * button)
{
	if (button->getName() == "Send")
	{
		//TO DO maque api request
		changeView("Player");
	}
	else if (button->getName() == "Cancel")
	{
		changeView("Player");
	}

}
