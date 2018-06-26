/*
  ==============================================================================

    ThreadPool.cpp
    Created: 21 Jun 2018 12:56:47pm
    Author:  anthony

  ==============================================================================
*/

#include "ThreadPoolGenerator.hh"

ThreadPoolGenerator::ThreadPoolGenerator()
{

}

ThreadPoolGenerator::~ThreadPoolGenerator()
{

}

void ThreadPoolGenerator::init()
{
  _generatorThread = std::thread(&ThreadPoolGenerator::generationManager, this);
}

void ThreadPoolGenerator::addClient(const Client & client)
{
  _clientsMutex.lock();
  if (_clients.size() == 0)
    _condVar.notify();
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
  std::list<Client>           clients;
  Midi midiData;

  while (42)
  {
      _clientsMutex.lock();
      clients = _clients; //This may be improved !!
      _clientsMutex.unlock();

      if (clients.size() > 0)
      {
        for (it = clients.begin(); it != clients.end(); ++it)
        {
          midiData = _musicGenerator.createMusic(it->getMp());
          //Need to add \r\n

          char *tmp = new char[midiData.getMidiSize() + 2];

          std::memcpy(tmp, midiData.getMidiArray(), midiData.getMidiSize());
          tmp[midiData.getMidiSize()] = '\r';
          tmp[midiData.getMidiSize() + 1] = '\n';
          send(it->getFd(), tmp, midiData.getMidiSize() + 2, MSG_NOSIGNAL);

          delete[] tmp;
        }
      }
      else
      {
        _condVar.wait();
      }
  }
}
