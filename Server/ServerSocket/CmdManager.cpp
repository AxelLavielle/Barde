#include "CmdManager.hh"

CmdManager::CmdManager()
{
  _cmdFunctions[0x1] = std::bind(&CmdManager::manageMusicParameter, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  _cmdFunctions[0x2] = std::bind(&CmdManager::managePlayerCtrl, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  _cmdFunctions[0x3] = std::bind(&CmdManager::manageDisconnection, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  _threadPool.init();

  _playerCtrlFunctions[0x12] = std::bind(&ThreadPoolGenerator::addClient, &_threadPool, std::placeholders::_1);
  _playerCtrlFunctions[0x22] = std::bind(&ThreadPoolGenerator::removeClient, &_threadPool, std::placeholders::_1);
  _playerCtrlFunctions[0x32] = std::bind(&ThreadPoolGenerator::removeClient, &_threadPool, std::placeholders::_1); //Pause not implemented in the IA
  _playerCtrlFunctions[0x42] = std::bind(&ThreadPoolGenerator::refreshClient, &_threadPool, std::placeholders::_1);

}

CmdManager::~CmdManager()
{

}

void CmdManager::sendResponseMessage(const int responseCode, const Client & client, const std::string & message)
{
  int *msg = new int[2 + message.length() / sizeof(int)];

  msg[0] = responseCode;
  std::memcpy(&msg[1], message.c_str(), message.length());
  send(client.getFd(), msg, sizeof(int) + message.length(), MSG_NOSIGNAL);
}

void CmdManager::manageMusicParameter(int *buffer, Client &client, size_t bufferSize)
{
  if (bufferSize < 12)
  {
    sendResponseMessage(0x1F4, client, "Bad Request : bad format for music parameter request.\r\n");
    return;
  }
  if (buffer[1] == 0x11) //STYLE
  {
    if (buffer[2] == 0x111)
    {
      client.getMp().setStyleName("JAZZ");
    }
    else if (buffer[2] == 0x211)
    {
      client.getMp().setStyleName("BLUES");
    }
  }
  else if (buffer[1] == 0x21) //ADDCHORD
  {
    Instrument instru;

    instru.name = ""; //Need to get from request
    instru.nb = static_cast<NbInstrument>(buffer[2]);
    instru.channel = 1; //Need to manage that
    instru.velocity = 100; //Need to get from request
    client.getMp().addInstrumentChords(instru);
  }
  else if (buffer[1] == 0x31) //ADDAEPEGES
  {
    Instrument instru;

    instru.name = "";
    instru.nb = static_cast<NbInstrument>(buffer[2]);
    instru.channel = 2;
    instru.velocity = 100;
    client.getMp().addInstrumentArpeggios(instru);
  }
  else if (buffer[1] == 0x61) //REMOVECHORD
  {
    Instrument instru;

    instru.name = ""; //Need to get from request
    instru.nb = static_cast<NbInstrument>(buffer[2]);
    instru.channel = 1; //Need to manage that
    instru.velocity = 100; //Need to get from request
    client.getMp().delInstrumentChords(instru);
  }
  else if (buffer[1] == 0x71) //REMOVEAEPEGES
  {
    Instrument instru;

    instru.name = "";
    instru.nb = static_cast<NbInstrument>(buffer[2]);
    instru.channel = 2;
    instru.velocity = 100;
    client.getMp().delInstrumentArpeggios(instru);
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
  if (bufferSize < 8)
  {
    sendResponseMessage(0x1F4, client, "Bad Request : bad format for player control request.\r\n");
    return;
  }
  try
  {
    (_playerCtrlFunctions.at(buffer[1]))(client);
  }
  catch (const std::out_of_range & e)
  {
    std::cerr << "Error Player control command unknow." << std::endl;
    sendResponseMessage(0x1F4, client, "Bad Request : Player control command unknow.\r\n");
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
  // {
  //   std::cerr << "Error request size too small." << std::endl;
  //   sendResponseMessage(0x1F4, client, "Bad Request : request size too small.\r\n");
  //   return;
  // }
  // try
  // {
  //   (_cmdFunctions.at(buffer[0]))(data, client, bufferSize);
  // }
  // catch (const std::out_of_range & e)
  // {
  //   std::cerr << "Error command unknow." << std::endl;
  //   sendResponseMessage(0x1F4, client, "Bad Request : command unknow.\r\n");
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
