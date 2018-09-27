/*
  ==============================================================================

    PlayerFooter.cpp
    Created: 24 May 2018 5:18:03pm
    Author:  Anthony

  ==============================================================================
*/

#include "PlayerFooter.hh"

PlayerFooter::PlayerFooter(Player & player, MusicParameters &musicParameters) : _player(player), _musicParameters(musicParameters),
				_controlGroup(FlexBox::JustifyContent::flexStart, FlexBox::AlignContent::center, FlexBox::AlignItems::center, FlexBox::Direction::row)
{
	
	_playButton = new PlayingCtrlButton("Play", BUTTON_PLAYING_TYPE::PLAY);
	_playButton->addListener(this);

	_stopButton = new PlayingCtrlButton("Stop", BUTTON_PLAYING_TYPE::STOP);
	_stopButton->addListener(this);

	GuiFactory::initSlider(0, 100, 100, _volumeSlider);
	_volumeSlider.addListener(this);
	addAndMakeVisible(_volumeSlider);

	addAndMakeVisible(_controlGroup);
	FlexItem item(*_playButton);
	FlexItem item2(*_stopButton);
	item.alignSelf = FlexItem::AlignSelf::flexStart;
	item.margin.left = 10;
	item.margin.right = 10;
	item2.alignSelf = FlexItem::AlignSelf::flexStart;
	_controlGroup.addItem(item.withMinWidth(PLAYING_BUTTON_WIDTH).withMinHeight(PLAYING_BUTTON_HEIGHT));
	_controlGroup.addItem(item2.withMinWidth(PLAYING_BUTTON_WIDTH).withMinHeight(PLAYING_BUTTON_HEIGHT));

	initFlexBox();

	auto test = CmdManager::getInstance().getUserInfo().getRole();

}

PlayerFooter::~PlayerFooter()
{
}

void PlayerFooter::paint(Graphics & g)
{
	g.fillAll(Colour(0xFF304B69));
}

void PlayerFooter::resized()
{
	_flexBox.performLayout(getLocalBounds().toFloat());
}

void PlayerFooter::buttonClicked(Button * button)
{
	if (button == _playButton)
	{
		_player.newParams(_musicParameters);
	}
	else if (button == _stopButton)
	{
		_player.Stop();
	}
}

void PlayerFooter::sliderValueChanged(Slider * slider)
{
		//_player.setVolume(slider->getValue());
}

void PlayerFooter::initFlexBox()
{
	FlexItem groupItem(_controlGroup);
	FlexItem sliderItem(_volumeSlider);

	groupItem.flexGrow = 8;
	groupItem.alignSelf = FlexItem::AlignSelf::center;

	sliderItem.flexGrow = 1;
	sliderItem.alignSelf = FlexItem::AlignSelf::center;
	_flexBox = GuiFactory::createRowCenterFlexBox( { groupItem.withMinWidth(100.0f).withMinHeight(50.0f), sliderItem.withMinWidth(50.0f).withMinHeight(100.0f) } );
}
