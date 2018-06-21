#include "CmdManager.hh"

CmdManager::CmdManager()
{
}

void CmdManager::parseMessage(char *buffer, Client &client)
{
  std::cout << "client " << client.getFd() << " message : " << buffer << std::endl;
}
