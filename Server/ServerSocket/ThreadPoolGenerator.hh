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

#include "Client.hh"
#include "AI/MusicGenerator.hh"

class ThreadPoolGenerator
{
public:
  void init();
  void addClient(const Client & client);
  void removeClient(const Client & client);
  void generationManager();

private:
    std::list<Client>         _clients;
    std::thread                 _generatorThread;
    std::mutex					        _clientsMutex;
    MusicGenerator              _musicGenerator;
};
