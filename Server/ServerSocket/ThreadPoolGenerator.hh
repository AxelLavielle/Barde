/*
  ==============================================================================

    ThreadPool.hh
    Created: 21 Jun 2018 12:56:56pm
    Author:  anthony

  ==============================================================================
*/

#pragma once

#include <list>
#include <thread>
#include <mutex>
#include <sys/types.h>
#include <sys/socket.h>

#include "Client.hh"
#include "AI/MusicGenerator.hh"
#include "Semaphore.hh"

class ThreadPoolGenerator
{
public:
  ThreadPoolGenerator();
  ~ThreadPoolGenerator();
  void init();
  void addClient(const Client & client);
  void removeClient(const Client & client);
  void generationManager();
  void refreshClient(const Client & client);

private:
    std::list<Client>           _clients;
    std::list<std::thread>      _generatorThreads;
    std::mutex					        _clientsMutex;
    MusicGenerator              _musicGenerator;
    Semaphore                   _sem;
};
