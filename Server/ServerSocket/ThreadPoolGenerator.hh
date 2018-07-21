/*
  ==============================================================================

    ThreadPool.hh
    Created: 21 Jun 2018 12:56:56pm
    Author:  anthony

  ==============================================================================
*/

#ifndef __THREAD_POOL_GENERATOR_HH__
#define __THREAD_POOL_GENERATOR_HH__

#include <list>
#include <thread>
#include <mutex>
#include <sys/types.h>
#include <sys/socket.h>

#include "Semaphore.hh"
#include "Client.hh"
#include "AI/MusicGenerator.hh"

#define PLAY_REQUEST 0x12
#define STOP_REQUEST 0x22
#define PAUSE_REQUEST 0x32
#define REFRESH_REQUEST 0x42

#ifndef __CMDMANAGER__HH__

#define BAD_REQUEST 0xC8
#define OK_REQUEST 0xC8

class CmdManager
{
public:
  CmdManager();
  ~CmdManager();
  void	parseMessage(char *buffer, Client &client, size_t bufferSize);
  void  disconnectClient(const Client & client);
  static void sendResponseMessage(const int responseCode, const int responseType, const int data, const Client & client, const std::string & message);
};
#endif

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
 #endif //__THREAD_POOL_GENERATOR_HH__
