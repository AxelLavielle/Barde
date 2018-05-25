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
	//TO DO remove this list after the beta and use full instrumentList from instrument.hh
	_instrusChoice = { "ACOUSTICGRANDPIANO", "TRUMPET", "SOPRANOSAX" };

	_bpmLabel.setFontSize(13);
	_bpmLabel.setLabelText("Bpm : " + std::to_string(_musicParameters.getBpm()));
	_bpmLabel.setColour(Label::textColourId, Colours::black);

	GuiFactory::initBigTitle("Edit your music", _titleLabel);
	addFlexItem(_titleLabel, GuiFactory::getBoxLabelWidth(_titleLabel), GuiFactory::getBoxLabelHeight(_titleLabel));

	GuiFactory::initLittleTitle("Choice your style", _styleLabel);
	addFlexItem(_styleLabel, GuiFactory::getBoxLabelWidth(_styleLabel), GuiFactory::getBoxLabelHeight(_styleLabel));

	GuiFactory::initLittleTitle("Chords instruments", _chordsLabel);

	GuiFactory::initLittleTitle("Arpegios instruments", _arpegiosLabel);

	GuiFactory::initLittleTitle("Drums instruments", _drumsLabel);

	initInstrumentsGroup();

	initInstrumentsButtons(_arpegiosInstrumentButtons, "Arpegios");
	initInstrumentsButtons(_chordInstrumentButtons, "Chords");

	_bpmSlider.setRange(70, 200);
	_bpmSlider.setValue(_musicParameters.getBpm());
	_bpmSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	_bpmSlider.addListener(this);

	_bpmGroup.setAlignContent(FlexBox::AlignContent::stretch);
	_bpmGroup.setJustifyContent(FlexBox::JustifyContent::center);
	_bpmGroup.setAlignItems(FlexBox::AlignItems::stretch);
	_bpmGroup.setFlexDirection(FlexBox::Direction::row);
	_bpmGroup.addItem(GuiFactory::createFlexItem(_bpmSlider, 300, 30, FlexItem::AlignSelf::autoAlign, 1));
	_bpmGroup.addItem(GuiFactory::createFlexItem(_bpmLabel, GuiFactory::getBoxLabelWidth(_bpmLabel), GuiFactory::getBoxLabelHeight(_bpmLabel)));
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
		GuiFactory::initToggleButton(_instrusChoice[i].toStdString(), categoryName, buttons[i]);
		buttons[i].addListener(this);

		if (categoryName == "Arpegios")
			_arpegiosGroup.addItem(GuiFactory::createFlexItem(buttons[i], GuiFactory::getBoxLabelWidth(_arpegiosLabel), 10, FlexItem::AlignSelf::autoAlign, 1));
		else if (categoryName == "Chords")
			_chordsGroup.addItem(GuiFactory::createFlexItem(buttons[i], GuiFactory::getBoxLabelWidth(_arpegiosLabel), 10, FlexItem::AlignSelf::autoAlign, 1));
	}
}

void PlayerPanel::initInstrumentsGroup()
{
	_instrumentsGroup.setAlignContent(FlexBox::AlignContent::stretch);
	_instrumentsGroup.setJustifyContent(FlexBox::JustifyContent::center);
	_instrumentsGroup.setAlignItems(FlexBox::AlignItems::stretch);
	_instrumentsGroup.setFlexDirection(FlexBox::Direction::row);

	_chordsGroup.setAlignContent(FlexBox::AlignContent::stretch);
	_chordsGroup.setJustifyContent(FlexBox::JustifyContent::center);
	_chordsGroup.setAlignItems(FlexBox::AlignItems::stretch);
	_chordsGroup.setFlexDirection(FlexBox::Direction::column);
	_chordsGroup.addItem(GuiFactory::createFlexItem(_chordsLabel, GuiFactory::getBoxLabelWidth(_chordsLabel), GuiFactory::getBoxLabelHeight(_chordsLabel), FlexItem::AlignSelf::autoAlign, 1));

	_arpegiosGroup.setAlignContent(FlexBox::AlignContent::stretch);
	_arpegiosGroup.setJustifyContent(FlexBox::JustifyContent::center);
	_arpegiosGroup.setAlignItems(FlexBox::AlignItems::stretch);
	_arpegiosGroup.setFlexDirection(FlexBox::Direction::column);
	_arpegiosGroup.addItem(GuiFactory::createFlexItem(_arpegiosLabel, GuiFactory::getBoxLabelWidth(_arpegiosLabel), GuiFactory::getBoxLabelHeight(_arpegiosLabel), FlexItem::AlignSelf::autoAlign, 1));

	_drumsGroup.setAlignContent(FlexBox::AlignContent::stretch);
	_drumsGroup.setJustifyContent(FlexBox::JustifyContent::center);
	_drumsGroup.setAlignItems(FlexBox::AlignItems::stretch);
	_drumsGroup.setFlexDirection(FlexBox::Direction::column);
	_drumsGroup.addItem(GuiFactory::createFlexItem(_drumsLabel, GuiFactory::getBoxLabelWidth(_drumsLabel), GuiFactory::getBoxLabelHeight(_drumsLabel), FlexItem::AlignSelf::autoAlign, 1));


	_instrumentsGroup.addItem(GuiFactory::createFlexItem(_chordsGroup, GuiFactory::getBoxLabelWidth(_chordsLabel), 100, FlexItem::AlignSelf::autoAlign, 1));
	_instrumentsGroup.addItem(GuiFactory::createFlexItem(_arpegiosGroup, GuiFactory::getBoxLabelWidth(_chordsLabel), 100, FlexItem::AlignSelf::autoAlign, 1));
	_instrumentsGroup.addItem(GuiFactory::createFlexItem(_drumsGroup, GuiFactory::getBoxLabelWidth(_chordsLabel), 100, FlexItem::AlignSelf::autoAlign, 1));

	addFlexItem(_instrumentsGroup, 300, 100);
}

void PlayerPanel::paint(Graphics & g)
{
	g.fillAll(Colours::white);
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
			std::cout << "Arpeges: " << button->getButtonText() << " " << button->getToggleState() << std::endl;
			Instrument instru;

			//TODO Set Instrument
			instru.name = button->getButtonText().toStdString();
			instru.nb = instrumentList.at(instru.name);
			instru.channel = instru.nb;  //This is bad but i don't know how to fix
			instru.velocity = 100; //Need change
			if (button->getToggleState())
				_musicParameters.addInstrumentArpeggios(instru);
			else
				_musicParameters.delInstrumentArpeggios(instru);
		}

		else if (button->getName() == "Chords")
		{
			std::cout << "Chords: " << button->getButtonText() << " " << button->getToggleState() << std::endl;
			Instrument instru;

			//TODO CHECK THIS 
			instru.name = button->getButtonText().toStdString();
			instru.nb = instrumentList.at(instru.name);
			instru.channel = instru.nb; //This is bad but i don't know how to fix
			instru.velocity = 100; //Need change
			if (button->getToggleState())
				_musicParameters.addInstrumentChords(instru);
			else
				_musicParameters.delInstrumentChords(instru);

		}
		//else if (button->getName() == "Drums")
		//{
		//	_musicParameters.setInstrumentDrums(button->getToggleState());
		//}
}

