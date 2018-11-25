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
  CmdManager::sendResponseMessage(OK_REQUEST, PLAY_REQUEST, client.getMp().getSeed(), client, "OK : playing.\r\n");

}

void ThreadPoolGenerator::removeClient(const Client & client)
{
  _clientsMutex.lock();
  _clients.remove(client);
  _clientsMutex.unlock();
  CmdManager::sendResponseMessage(OK_REQUEST, STOP_REQUEST, 0, client, "OK : stop playing.\r\n");
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
      try {
	client = _clients.front();
	_clients.pop_front();
	
	while (client.needGeneration())
	  {
	    midiData = _musicGenerator.createMusic(client.getMp());
	    
	    char *tmp = new char[midiData.getMidiSize() + 2 + sizeof(int)];
	    
	    tmp[0] = 0x4;
	    tmp[1] = 0x0;
	    tmp[2] = 0x0;
	    tmp[3] = 0x0; //This depends of the endieness !!
	    
	    std::memcpy(&tmp[4], midiData.getMidiArray(), midiData.getMidiSize());
	    tmp[midiData.getMidiSize() + 4] = '\r';
	    tmp[midiData.getMidiSize() + 5] = '\n';
	    
	    //Need to check the return of send
	    if (send(client.getFd(), tmp, midiData.getMidiSize() + 2 + sizeof(int), MSG_NOSIGNAL) == -1)
	      {
		break; //If the client is disconnected or other error, he don't need generation
	      }
	    
	    
	    delete[] midiData.getMidiArray();
	    
	    client.addGeneration();
	    
	    delete[] tmp;
	  }
      }
      catch(std::bad_alloc&) {
	std::cout << "############################# Not enough memory ############################" << std::endl;
      }
      
      _clientsMutex.unlock();
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
  CmdManager::sendResponseMessage(OK_REQUEST, REFRESH_REQUEST, 0, client, "OK : playing with music parameters updated.\r\n");
}
