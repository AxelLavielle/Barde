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
  _clientsMutex.lock();
  _clients.push_back(client);
  _clientsMutex.unlock();
}

void ThreadPoolGenerator::removeClient(const Client & client)
{
  _clientsMutex.lock();
  _clients.remove(client);
  _clientsMutex.unlock();
}

void ThreadPoolGenerator::generationManager()
{
  std::list<Client>::iterator it;
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
