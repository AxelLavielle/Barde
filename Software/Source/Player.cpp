/*
  ==============================================================================

    Player.cpp
    Created: 13 Mar 2017 1:44:54pm
    Author:  Anthony

  ==============================================================================
*/

#include "Player.hh"

Player::Player()
{
	_soundManager = new SoundManager();
	_generator = new MusicGenerator();
}

Player::~Player()
{
	_stopQueue = true;
	_genThread.join();
	_playThread.join();
	delete _soundManager;
	delete _generator;
}

void Player::newParams(MusicParameters p)
{
	_graph2genM.lock();
	_graph2genQ.push_back(p);
	_graph2genM.unlock();
}

void Player::Init()
{
	_stopQueue = false;
	_genThread = std::thread(&MusicGenerator::launch, _generator, std::ref(_graph2genQ), std::ref(_gen2playQ), std::ref(_graph2genM), std::ref(_gen2playM), std::ref(_stopQueue));
	_playThread = std::thread(&SoundManager::launch, static_cast<SoundManager *>(_soundManager), std::ref(_gen2playQ), std::ref(_gen2playM), std::ref(_stopQueue));
}

void Player::Play(MusicParameters _musicParameters)
{
	_generator->createMusic(_musicParameters);
	_soundManager->play(_musicParameters.getMidi(), _musicParameters.getBpm(), _stopQueue);
}