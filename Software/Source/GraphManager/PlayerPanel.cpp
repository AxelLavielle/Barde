/*
  ==============================================================================

    PlayerPanel.cpp
    Created: 24 May 2018 6:08:41pm
    Author:  Anthony

  ==============================================================================
*/

#include "PlayerPanel.hh"

PlayerPanel::PlayerPanel(MusicParameters & musicParameters) : _musicParameters(musicParameters)
{
	Theme::getInstance().parseTheme("../Themes/Dark");
	//TO DO remove this list after the beta and use full instrumentList from instrument.hh
	_instrusChoice = { "ACOUSTICGRANDPIANO", "TRUMPET", "SOPRANOSAX" };

	_bpmLabel.setFontSize(13);
	_bpmLabel.setLabelText("Bpm : " + std::to_string(_musicParameters.getBpm()));
	_bpmLabel.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor()));
	GuiFactory::initBigTitle("Edit your music", _titleLabel);
	addFlexItem(_titleLabel, GuiFactory::getBoxLabelWidth(_titleLabel), GuiFactory::getBoxLabelHeight(_titleLabel));
	GuiFactory::initLittleTitle("Choose your style", _styleLabel);
	addFlexItem(_styleLabel, GuiFactory::getBoxLabelWidth(_styleLabel), GuiFactory::getBoxLabelHeight(_styleLabel));
	GuiFactory::initLittleTitle("Chords instruments", _chordsLabel);
	GuiFactory::initLittleTitle("Arpegios instruments", _arpegiosLabel);
	GuiFactory::initLittleTitle("Drums instruments", _drumsLabel);

	GuiFactory::initToggleButton("Blues", "Blues", _bluesButton, true);
	_bluesButton.addListener(this);
	GuiFactory::initToggleButton("Reggae (Comming soon !)", "Reggae", _raggaeButton);
	_raggaeButton.addListener(this);
	GuiFactory::initToggleButton("House (Coming soon !)", "House", _houseButton);
	_houseButton.addListener(this);
	GuiFactory::initHoryzontalFlexGroup({ GuiFactory::createFlexItem(_bluesButton, GuiFactory::getBoxLabelWidth(_drumsLabel), 10, FlexItem::AlignSelf::autoAlign, 1), GuiFactory::createFlexItem(_raggaeButton, GuiFactory::getBoxLabelWidth(_drumsLabel), 10, FlexItem::AlignSelf::autoAlign, 1), GuiFactory::createFlexItem(_houseButton, GuiFactory::getBoxLabelWidth(_drumsLabel), 10, FlexItem::AlignSelf::autoAlign, 1) }, _styleGroup);
	addFlexItem(_styleGroup, 300, 100);

	initInstrumentsGroup();

	initInstrumentsButtons(_arpegiosInstrumentButtons, "Arpegios");
	initInstrumentsButtons(_chordInstrumentButtons, "Chords");
	GuiFactory::initToggleButton("Enable drums", "Drums", _drumsInstrumentButton, true);
	_drumsInstrumentButton.addListener(this);

	GuiFactory::initLittleTitle("Modify the BPM", _bpmTitleLabel);
	addFlexItem(_bpmTitleLabel, GuiFactory::getBoxLabelWidth(_bpmTitleLabel), GuiFactory::getBoxLabelHeight(_bpmTitleLabel));
	_bpmSlider.setRange(70, 200);
	_bpmSlider.setValue(_musicParameters.getBpm());
	_bpmSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	_bpmSlider.setColour(Label::textColourId, Colour(Theme::getInstance().getFontColor()));
	_bpmSlider.setColour(Slider::backgroundColourId, Colour(Theme::getInstance().getFontColor()));
	_bpmSlider.setColour(Slider::thumbColourId, Colours::pink);
	_bpmSlider.setColour(Slider::trackColourId, Colour(Theme::getInstance().getButtonColor()));
	_bpmSlider.setColour(Slider::textBoxBackgroundColourId, Colour(Theme::getInstance().getBackgroundColor()));
	_bpmSlider.setColour(Slider::textBoxTextColourId, Colour(Theme::getInstance().getFontColor()));
	_bpmSlider.addListener(this);
	GuiFactory::initHoryzontalFlexGroup( { GuiFactory::createFlexItem(_bpmSlider, 300, 30, FlexItem::AlignSelf::autoAlign, 1),
											GuiFactory::createFlexItem(_bpmLabel, 100, GuiFactory::getBoxLabelHeight(_bpmLabel)) }, _bpmGroup );
	addFlexItem(_bpmGroup, 400, 30);

	_flexBox = GuiFactory::createFlexBox(FlexBox::JustifyContent::spaceAround, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::Direction::column, _items);
}

void PlayerPanel::addFlexItem(Component & component, const float minWidth, const float maxHeight, const FlexItem::AlignSelf & align)
{
	addAndMakeVisible(component);
	_items.push_back(GuiFactory::createFlexItem(component, minWidth, maxHeight, align));
}

void PlayerPanel::initInstrumentsButtons(ToggleButton buttons[], const std::string & categoryName)
{
	for (int i = 0; i < _instrusChoice.size(); i++)
	{
		//TO DO init ToggleButton from musicParameters
		if (i == 0)
			GuiFactory::initToggleButton(_instrusChoice[i].toStdString(), categoryName, buttons[i], true);
		else
			GuiFactory::initToggleButton(_instrusChoice[i].toStdString(), categoryName, buttons[i]);
		buttons[i].addListener(this);

		if (categoryName == "Arpegios")
			_arpegiosGroup.addItem(GuiFactory::createFlexItem(buttons[i], GuiFactory::getBoxLabelWidth(_arpegiosLabel), 10, FlexItem::AlignSelf::autoAlign, 1));
		else if (categoryName == "Chords")
			_chordsGroup.addItem(GuiFactory::createFlexItem(buttons[i], GuiFactory::getBoxLabelWidth(_chordsLabel), 10, FlexItem::AlignSelf::autoAlign, 1));
	}


}

void PlayerPanel::initInstrumentsGroup()
{

	GuiFactory::initVerticalFlexGroup( { GuiFactory::createFlexItemLabel(_chordsLabel, FlexItem::AlignSelf::autoAlign, 1) }, _chordsGroup);

	GuiFactory::initVerticalFlexGroup( { GuiFactory::createFlexItemLabel(_arpegiosLabel, FlexItem::AlignSelf::autoAlign, 1) } , _arpegiosGroup);

	GuiFactory::initVerticalFlexGroup( { GuiFactory::createFlexItemLabel(_drumsLabel, FlexItem::AlignSelf::autoAlign, 1), GuiFactory::createFlexItem(_drumsInstrumentButton, GuiFactory::getBoxLabelWidth(_drumsLabel), 10, FlexItem::AlignSelf::autoAlign, 1) } , _drumsGroup);

	GuiFactory::initHoryzontalFlexGroup( { GuiFactory::createFlexItem(_chordsGroup, GuiFactory::getBoxLabelWidth(_chordsLabel), 100, FlexItem::AlignSelf::autoAlign, 1), GuiFactory::createFlexItem(_arpegiosGroup, GuiFactory::getBoxLabelWidth(_arpegiosLabel), 100, FlexItem::AlignSelf::autoAlign, 1),
											GuiFactory::createFlexItem(_drumsGroup, GuiFactory::getBoxLabelWidth(_drumsLabel), 100, FlexItem::AlignSelf::autoAlign, 1) } , _instrumentsGroup);

	addFlexItem(_instrumentsGroup, 300, 100);
}

void PlayerPanel::paint(Graphics & g)
{
	g.fillAll(Colour(Theme::getInstance().getBackgroundColor()));
}

void PlayerPanel::resized()
{
	_flexBox.performLayout(getLocalBounds().toFloat());
}

void PlayerPanel::sliderValueChanged(Slider * slider)
{
	_bpmLabel.setText("Bpm : " + std::to_string(static_cast<int>(slider->getValue())), NotificationType::dontSendNotification);
	_musicParameters.setBpm(static_cast<int>(slider->getValue()));
}

void PlayerPanel::buttonClicked(Button * button)
{
		if (button->getName() == "Arpegios")
		{
			Instrument instru;

			instru.name = button->getButtonText().toStdString();
			instru.nb = instrumentList.at(instru.name);
			instru.channel = instru.nb % 15;  //This is bad but i don't know how to fix
			instru.velocity = 100; //Need change
			if (button->getToggleState())
			{
				_musicParameters.addInstrumentArpeggios(instru);
				_arpegiosGroup.refreshExclusiveToggleItems(button->getButtonText().toStdString());
			}
			else
				_musicParameters.delInstrumentArpeggios(instru);

		}

		else if (button->getName() == "Chords")
		{
			Instrument instru;

			instru.name = button->getButtonText().toStdString();
			instru.nb = instrumentList.at(instru.name);
			instru.channel = instru.nb % 15; //This is bad but i don't know how to fix
			instru.velocity = 100; //Need change
			if (button->getToggleState())
			{
				_chordsGroup.refreshExclusiveToggleItems(button->getButtonText().toStdString());
				_musicParameters.addInstrumentChords(instru);
			}
			else
				_musicParameters.delInstrumentChords(instru);

		}
		else if (button->getName() == "Drums")
		{
			_musicParameters.setInstrumentDrums(button->getToggleState());
		}
		else if (button->getName() == "Blues" || button->getName() == "Reggae" || button->getName() == "House")
		{
			if (button->getToggleState())
				_styleGroup.refreshExclusiveToggleItems(button->getButtonText().toStdString());
		}
}

