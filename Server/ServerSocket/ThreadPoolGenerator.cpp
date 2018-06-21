/*
  ==============================================================================

    ThreadPool.cpp
    Created: 21 Jun 2018 12:56:47pm
    Author:  anthony

  ==============================================================================
*/

#include "ThreadPoolGenerator.hh"

void ThreadPoolGenerator::init()
{
  _generatorThread = std::thread(&ThreadPoolGenerator::generationManager, this);
}

void ThreadPoolGenerator::addClient(const Client & client)
{
    _clients.push_back(client);
}

void ThreadPoolGenerator::removeClient(const Client & client)
{
  _clients.push_back(client);
}

void ThreadPoolGenerator::generationManager()
{
  std::vector<Client>::iterator it;
  Midi midiData;
  while (42)
  {
      _clientsMutex.lock();
      if (_clients.size() > 0)
      {
        std::cout << "COUCOU !!!!" << std::endl;
        for (it = _clients.begin(); it != _clients.end(); ++it)
        {
          midiData = _musicGenerator.createMusic(it->getMp());

          write(it->getFd(), midiData.getMidiArray(), midiData.getMidiSize());
        }
      }
      else
      {
        //Need to do a pause
      }
      _clientsMutex.unlock();
  }
}
