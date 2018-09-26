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

	GuiFactory::initBigTitle("Edit your music", _titleLabel);
	addFlexItem(_titleLabel, GuiFactory::getBoxLabelWidth(_titleLabel), GuiFactory::getBoxLabelHeight(_titleLabel));
	GuiFactory::initLittleTitle("Choose your style", _styleLabel);
	addFlexItem(_styleLabel, GuiFactory::getBoxLabelWidth(_styleLabel), GuiFactory::getBoxLabelHeight(_styleLabel));
	GuiFactory::initLittleTitle("Chords instruments", _chordsLabel);
	GuiFactory::initLittleTitle("Arpeggios instruments", _arpegiosLabel);
	GuiFactory::initLittleTitle("Drums instruments", _drumsLabel);

	GuiFactory::initToggleButton("Blues", "Blues", _bluesButton, true);
	_bluesButton.addListener(this);
	_bluesButton.setRadioGroupId(42, dontSendNotification);
	GuiFactory::initToggleButton("Reggae", "Reggae", _reggaeButton);
	_reggaeButton.addListener(this);
	_reggaeButton.setRadioGroupId(42, dontSendNotification);
	GuiFactory::initToggleButton("House (Coming soon !)", "House", _houseButton);
	_houseButton.addListener(this);
	_houseButton.setRadioGroupId(42, dontSendNotification);
	_houseButton.setEnabled(false); //remove this
	GuiFactory::initHoryzontalFlexGroup({ GuiFactory::createFlexItem(_bluesButton, GuiFactory::getBoxLabelWidth(_drumsLabel), 10, FlexItem::AlignSelf::autoAlign, 1), GuiFactory::createFlexItem(_reggaeButton, GuiFactory::getBoxLabelWidth(_drumsLabel), 10, FlexItem::AlignSelf::autoAlign, 1), GuiFactory::createFlexItem(_houseButton, GuiFactory::getBoxLabelWidth(_drumsLabel), 10, FlexItem::AlignSelf::autoAlign, 1) }, _styleGroup);
	addFlexItem(_styleGroup, 300, 100);

	initMusicParameters();

	initInstrumentsGroup();

	initInstrumentsButtons(_arpegiosInstrumentButtons, "Arpeggios", _musicParameters.getInstrumentsArpeggios());
	initInstrumentsButtons(_chordInstrumentButtons, "Chords", _musicParameters.getInstrumentsChords());
	GuiFactory::initToggleButton("Enable drums", "Drums", _drumsInstrumentButton, true);
	_drumsInstrumentButton.addListener(this);

	GuiFactory::initLittleTitle("Modify the BPM", _bpmTitleLabel);
	addFlexItem(_bpmTitleLabel, GuiFactory::getBoxLabelWidth(_bpmTitleLabel), GuiFactory::getBoxLabelHeight(_bpmTitleLabel));

	_bpmSlider.init(_musicParameters.getBpm(), std::bind(&PlayerPanel::sliderValueChanged, this, std::placeholders::_1));
	addAndMakeVisible(_bpmSlider);
	_items.push_back(GuiFactory::createFlexItem(_bpmSlider, 500, 50, FlexItem::AlignSelf::center).withMaxWidth(700));

	_flexBox = GuiFactory::createFlexBox(FlexBox::JustifyContent::spaceAround, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::Direction::column, _items);
}

void PlayerPanel::initMusicParameters()
{
	//TO DO CHANGE THAT
	_musicParameters.setSeed(static_cast<unsigned int>(std::time(NULL)));
	_musicParameters.setBpm(105);
	Instrument instru;
	instru.name = "SOPRANOSAX";
	instru.nb = SOPRANOSAX;
	instru.channel = 65 % 15;
	instru.velocity = 100; //Need change
	Instrument instru2;
	instru2.name = "ACOUSTICGRANDPIANO";
	instru2.nb = ACOUSTICGRANDPIANO;
	instru2.channel = 1;
	instru2.velocity = 100; //Need change
	_musicParameters.addInstrumentArpeggios(instru);
	_musicParameters.addInstrumentChords(instru2);
	_musicParameters.setStyleName("Blues");
	srand(_musicParameters.getSeed());
	_musicParameters.setInstrumentsDrums(true);
}

bool PlayerPanel::containInstrument(const std::vector<Instrument> & instruments, const std::string & instrumentName)
{
	std::vector<Instrument>::const_iterator it;

	for (it = instruments.begin(); it != instruments.end(); ++it)
	{
		if (instrumentName == it->name)
			return true;
	}
	return false;
}

void PlayerPanel::initInstrumentsButtons(ToggleButton buttons[], const std::string & categoryName, const std::vector<Instrument> & instruments)
{
	size_t i;

	i = 0;
	for (i = 0; i < _instrusChoice.size(); ++i)
	{
		if (containInstrument(instruments, _instrusChoice[i].toStdString()))
			GuiFactory::initToggleButton(_instrusChoice[i].toStdString(), categoryName, buttons[i], true);
		else
			GuiFactory::initToggleButton(_instrusChoice[i].toStdString(), categoryName, buttons[i]);
		buttons[i].addListener(this);
		if (categoryName == "Arpeggios")
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

void PlayerPanel::sliderValueChanged(Slider * slider)
{
	_musicParameters.setBpm(static_cast<int>(slider->getValue()));
}

void PlayerPanel::buttonClicked(Button * button)
{
		if (button->getName() == "Arpeggios")
		{
			Instrument instru;

			instru.name = button->getButtonText().toStdString();
			instru.nb = instrumentList.at(instru.name);
			instru.channel = instru.nb % 15;  //This is bad but i don't know how to fix
			instru.velocity = 100; //Need change
			if (button->getToggleState())
			{
				_musicParameters.addInstrumentArpeggios(instru);
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
				_musicParameters.addInstrumentChords(instru); 
			}
			else
				_musicParameters.delInstrumentChords(instru);

		}
		else if (button->getName() == "Drums")
		{
			_musicParameters.setInstrumentsDrums(button->getToggleState());
		}
		else if (button->getName() == "Blues" || button->getName() == "Reggae" || button->getName() == "House")
		{
			if (button->getToggleState())
			{
				_styleGroup.refreshExclusiveToggleItems(button->getButtonText().toStdString());
				_musicParameters.setStyleName(button->getButtonText().toStdString());
			}
		}
}

