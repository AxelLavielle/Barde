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
  unsigned int n = std::thread::hardware_concurrency();
  std::cout << n << " concurrent threads are supported." << std::endl;

  while (n != 0)
  {
    _generatorThreads.push_back(std::thread(&ThreadPoolGenerator::generationManager, this));
    n--;
  }
}

void ThreadPoolGenerator::addClient(const Client & client)
{
  _clientsMutex.lock();
  _clients.push_back(client);
  _sem.notify();
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
  Client                      client;
  Midi midiData;

  while (42)
  {

      _clientsMutex.lock();
      if (_clients.size() == 0)
      {
        _clientsMutex.unlock();
        _sem.wait();
        _clientsMutex.lock();
      }
      client = _clients.front();
      _clients.pop_front();
      _clientsMutex.unlock();

      while (client.needGeneration())
      {
        midiData = _musicGenerator.createMusic(client.getMp());

        char *tmp = new char[midiData.getMidiSize() + 2];

        std::memcpy(tmp, midiData.getMidiArray(), midiData.getMidiSize());
        tmp[midiData.getMidiSize()] = '\r';
        tmp[midiData.getMidiSize() + 1] = '\n';

        //Need to check the return of send
        if (send(client.getFd(), tmp, midiData.getMidiSize() + 2, MSG_NOSIGNAL) == -1)
          break; //If the client is disconnected or other error, he don't need generation

        delete[] midiData.getMidiArray();

        client.addGeneration();

        delete[] tmp;
      }
  }
}

void ThreadPoolGenerator::refreshClient(const Client & client)
{
  std::list<Client>::iterator it;

  _clientsMutex.lock();
  for (it = _clients.begin(); it != _clients.end(); ++it)
  {
    *it = client;
  }
  _clientsMutex.unlock();
}
