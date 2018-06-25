#include "CmdManager.hh"

CmdManager::CmdManager()
{
  _cmdFunctions[0x1] = std::bind(&CmdManager::manageMusicParameter, this, std::placeholders::_1);
  _cmdFunctions[0x2] = std::bind(&CmdManager::manageMusicParameter, this, std::placeholders::_1);
  _cmdFunctions[0x3] = std::bind(&CmdManager::manageMusicParameter, this, std::placeholders::_1);

  _threadPool.init();
}

void CmdManager::manageMusicParameter(int *data)
{

}

void CmdManager::managePlayerCtrl(int *data)
{

}

void CmdManager::manageDisconnection(int *data)
{

}

void CmdManager::parseMessage(char *buffer, Client &client, size_t bufferSize)
{

  //Need to get the first in in order to know the request type

  int *data;

  data = (int *)buffer;

  // if (bufferSize <= 4)
  //   return;
  // if (data[0] == 0x12)
  // {
  //   std::cout << "The client want to play something" << std::endl;
  //   _threadPool.addClient(client);
  // }
  // else if (data[0] == 0x22)
  // {
  //   std::cout << "The client want to stop playing" << std::endl;
  //   _threadPool.removeClient(client);
  // }

  //For Debug
  if (bufferSize > 0 && buffer[0] == 'P')
  {
    std::cout << "The client want to play something" << std::endl;
    _threadPool.addClient(client);
  }
  else if (bufferSize > 0 && buffer[0] == 'S')
  {
    std::cout << "The client want to stop playing" << std::endl;
    _threadPool.removeClient(client);
  }
  //END debug
}

void CmdManager::disconnectClient(const Client & client)
{
  _threadPool.removeClient(client);
}
