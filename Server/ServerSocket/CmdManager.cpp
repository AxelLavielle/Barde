#include "CmdManager.hh"

CmdManager::CmdManager()
{
  _cmdFunctions[0x1] = std::bind(&CmdManager::manageMusicParameter, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  _cmdFunctions[0x2] = std::bind(&CmdManager::managePlayerCtrl, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  _cmdFunctions[0x3] = std::bind(&CmdManager::manageDisconnection, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  _threadPool.init();

  _playerCtrlFunctions[0x12] = std::bind(&ThreadPoolGenerator::addClient, &_threadPool, std::placeholders::_1);
  _playerCtrlFunctions[0x22] = std::bind(&ThreadPoolGenerator::removeClient, &_threadPool, std::placeholders::_1);
  // _playerCtrlFunctions[0x32] = std::bind(&ThreadPoolGenerator::addClient, _threadPool, std::placeholders::_1);
  // _playerCtrlFunctions[0x42] = std::bind(&ThreadPoolGenerator::addClient, _threadPool, std::placeholders::_1);

}

CmdManager::~CmdManager()
{

}

void CmdManager::manageMusicParameter(int *buffer, Client &client, size_t bufferSize)
{
  if (buffer[1] == 0x11) //STYLE
  {

  }
  else if (buffer[1] == 0x21) //CHORD
  {

  }
  else if (buffer[1] == 0x31) //AEPEGES
  {

  }
  else if (buffer[1] == 0x41) //DRUM
  {
    if (buffer[2] == 0x141)
      client.getMp().setInstrumentsDrums(true);
    else if (buffer[2] == 0x241)
      client.getMp().setInstrumentsDrums(false);
  }
  else if (buffer[1] == 0x51) //BPM
  {
    client.getMp().setBpm(buffer[2]);
  }
}

void CmdManager::managePlayerCtrl(int *buffer, Client &client, size_t bufferSize)
{
  try
  {
    (_playerCtrlFunctions.at(buffer[1]))(client);
  }
  catch (const std::out_of_range & e)
  {
    std::cerr << "Error Player control command unknow." << std::endl;
    //Need to send an error to the client !!!
  }
}

void CmdManager::manageDisconnection(int *buffer, Client &client, size_t bufferSize)
{
  _threadPool.removeClient(client);
}

void CmdManager::parseMessage(char *buffer, Client &client, size_t bufferSize)
{

  //Need to get the first in in order to know the request type

  int *data;

  data = (int *)buffer;

  // if (bufferSize <= 4)
  //   return;
  // try
  // {
  //   (_cmdFunctions.at(buffer[0]))(client);
  // }
  // catch (const std::out_of_range & e)
  // {
  //   std::cerr << "Error command unknow." << std::endl;
  //   //Need to send an error to the client !!!
  //   return;
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
