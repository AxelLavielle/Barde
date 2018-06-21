#include "CmdManager.hh"

CmdManager::CmdManager()
{
  _threadPool.init();
}

void CmdManager::parseMessage(char *buffer, Client &client, size_t bufferSize)
{
  if (bufferSize > 0 && buffer[0] == 'P')
  {
    _threadPool.addClient(client);
  }
  else if (bufferSize > 0 && buffer[0] == 'S')
  {

  }
  std::cout << "client " << client.getFd() << " message : " << buffer << std::endl;
}

void CmdManager::disconnectClient(const Client & client)
{
  _threadPool.removeClient(client);
}
