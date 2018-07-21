#include "CmdManager.hh"

CmdManager::CmdManager()
{
  _cmdFunctions[0x1] = std::bind(&CmdManager::manageMusicParameter, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  _cmdFunctions[0x2] = std::bind(&CmdManager::managePlayerCtrl, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  _cmdFunctions[0x3] = std::bind(&CmdManager::manageDisconnection, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  _threadPool.init();

  _playerCtrlFunctions[PLAY_REQUEST] = std::bind(&ThreadPoolGenerator::addClient, &_threadPool, std::placeholders::_1);
  _playerCtrlFunctions[STOP_REQUEST] = std::bind(&ThreadPoolGenerator::removeClient, &_threadPool, std::placeholders::_1);
  _playerCtrlFunctions[PAUSE_REQUEST] = std::bind(&ThreadPoolGenerator::removeClient, &_threadPool, std::placeholders::_1); //Pause not implemented in the IA
  _playerCtrlFunctions[REFRESH_REQUEST] = std::bind(&ThreadPoolGenerator::refreshClient, &_threadPool, std::placeholders::_1);

}

CmdManager::~CmdManager()
{

}

// void CmdManager::sendResponseMessage(const int responseCode, const int responseType, const Client & client, const std::string & message)
// {
//   int *msg = new int[4 + message.length() / sizeof(int)];
//
//   msg[0] = responseCode;
//   msg[1] = responseType;
//   msg[2] = 0;
//   std::memcpy(&msg[3], message.c_str(), message.length());
//   send(client.getFd(), msg, sizeof(int) + message.length(), MSG_NOSIGNAL);
//   delete[] msg;
// }

void CmdManager::sendResponseMessage(const int responseCode, const int responseType, const int data, const Client & client, const std::string & message)
{
  int *msg = new int[4 + message.length() / sizeof(int)];

  msg[0] = responseCode;
  msg[1] = responseType;
  msg[2] = data;
  std::memcpy(&msg[3], message.c_str(), message.length());
  send(client.getFd(), msg, sizeof(int) + message.length(), MSG_NOSIGNAL);
  delete[] msg;
}

void CmdManager::manageInstruments(const bool & add, const Client & client, const bool & arpeggios, const NbInstrument instruNb)
{
  Instrument instru;
  std::string msg = "OK : instrument ";
  int responseType;

  instru.name = ""; //Need to get from request
  instru.nb = instruNb;
  instru.channel = client.getMp().getFreeChannel(); //Need to manage that
  instru.velocity = 100; //Need to get from request

  if (instru.channel < 1) //Need to manage that
  {
    sendResponseMessage(BAD_REQUEST, UNKNOW_REQUEST, 0, client, "Bad Request : all channels are used.\r\n");
    return;
  }

  if (add)
  {
    if (arpeggios)
    {
      msg += "added in arpeggios.";
      responseType = ADDAEPEGES_REQUEST;
      client.getMp().addInstrumentArpeggios(instru);
    }
    else
    {
      client.getMp().addInstrumentChords(instru);
      responseType = ADDCHORD_REQUEST;
      msg += "added in chords.";
    }
  }
  else
  {
    if (arpeggios)
    {
      msg += "removed from arpeggios.";
      responseType = REMOVEAEPEGES_REQUEST;
      client.getMp().delInstrumentArpeggios(instru);
    }
    else
    {
      client.getMp().delInstrumentChords(instru);
      responseType = REMOVECHORD_REQUEST;
      msg += "removed from chords.";
    }
  }

  sendResponseMessage(OK_REQUEST, responseType, instruNb, client, msg + "\r\n");
}

void CmdManager::manageMusicParameter(int *buffer, Client &client, size_t bufferSize)
{
  if (bufferSize < 12)
  {
    sendResponseMessage(BAD_REQUEST, UNKNOW_REQUEST, 0, client, "Bad Request : bad format for music parameter request.\r\n");
    return;
  }
  if (buffer[1] == STYLE_REQUEST) //STYLE
  {
    if (buffer[2] == 0x111)
    {
      client.getMp().setStyleName("JAZZ");
      sendResponseMessage(OK_REQUEST, STYLE_REQUEST, 0x111, client, "OK : style setted.\r\n");
    }
    else if (buffer[2] == 0x211)
    {
      client.getMp().setStyleName("BLUES");
      sendResponseMessage(OK_REQUEST, STYLE_REQUEST, 0x211, client, "OK : style setted.\r\n");
    }
    else
      sendResponseMessage(BAD_REQUEST, STYLE_REQUEST, buffer[2], client, "Bad Request : style unknow.\r\n");
  }
  else if (buffer[1] == ADDCHORD_REQUEST)
    manageInstruments(true, client, false, static_cast<NbInstrument>(buffer[2]));
  else if (buffer[1] == ADDAEPEGES_REQUEST)
    manageInstruments(true, client, true, static_cast<NbInstrument>(buffer[2]));
  else if (buffer[1] == REMOVECHORD_REQUEST)
    manageInstruments(false, client, false, static_cast<NbInstrument>(buffer[2]));
  else if (buffer[1] == REMOVEAEPEGES_REQUEST)
    manageInstruments(false, client, true, static_cast<NbInstrument>(buffer[2]));
  else if (buffer[1] == DRUMS_REQUEST)
  {
    if (buffer[2] == 0x141)
    {
      client.getMp().setInstrumentsDrums(true);
      sendResponseMessage(OK_REQUEST, DRUMS_REQUEST, 0x141, client, "OK : drums enabled.\r\n");
    }
    else if (buffer[2] == 0x241)
    {
      client.getMp().setInstrumentsDrums(false);
      sendResponseMessage(OK_REQUEST, DRUMS_REQUEST, 0x241, client, "OK : drums disabled.\r\n");
    }
    else
      sendResponseMessage(BAD_REQUEST, DRUMS_REQUEST, buffer[2], client, "Bad Request : unknow drum value.\r\n");
  }
  else if (buffer[1] == BPM_REQUEST)
  {
    client.getMp().setBpm(buffer[2]);
    sendResponseMessage(OK_REQUEST, BPM_REQUEST, buffer[2], client, "OK : bpm modified.\r\n");
  }
  else
  {
    sendResponseMessage(BAD_REQUEST, BPM_REQUEST, buffer[2], client, "Bad Request : unknow music parameter request.\r\n");
  }
}

void CmdManager::managePlayerCtrl(int *buffer, Client &client, size_t bufferSize)
{
  if (bufferSize < 2)
  {
    sendResponseMessage(BAD_REQUEST, UNKNOW_REQUEST, 0, client, "Bad Request : bad format for player control request.\r\n");
    return;
  }
  try
  {
    (_playerCtrlFunctions.at(buffer[1]))(client);
    //Need to send ok or not
  }
  catch (const std::out_of_range & e)
  {
    std::cerr << "Error Player control command unknow." << std::endl;
    sendResponseMessage(BAD_REQUEST, UNKNOW_REQUEST, 0, client, "Bad Request : Player control command unknow.\r\n");
  }
}

void CmdManager::manageDisconnection(int *buffer, Client &client, size_t bufferSize)
{
  _threadPool.removeClient(client);
  sendResponseMessage(OK_REQUEST, DISCONNECTION_REQUEST, 0, client, "OK : client disconnected.\r\n");
}

void CmdManager::parseMessage(int *buffer, Client &client, size_t bufferSize)
{

  //Need to get the first in in order to know the request type


  if (bufferSize <= 0)
  {
    std::cerr << "Error request size too small." << std::endl;
    sendResponseMessage(0x1F4, UNKNOW_REQUEST, 0, client, "Bad Request : request size too small.\r\n");
    return;
  }
  try
  {
    std::cout << "la valeur est = " << buffer[0] << std::endl;
    (_cmdFunctions.at(buffer[0]))(buffer, client, bufferSize);
  }
  catch (const std::out_of_range & e)
  {
    std::cerr << "Error command unknow." << std::endl;
    sendResponseMessage(0x1F4, UNKNOW_REQUEST, 0, client, "Bad Request : command unknow.\r\n");
    return;
  }

  //For Debug
  // if (bufferSize > 0 && buffer[0] == 'P')
  // {
  //   std::cout << "The client want to play something" << std::endl;
  //   _threadPool.addClient(client);
  // }
  // else if (bufferSize > 0 && buffer[0] == 'S')
  // {
  //   std::cout << "The client want to stop playing" << std::endl;
  //   _threadPool.removeClient(client);
  // }
  //END debug
}

void CmdManager::disconnectClient(const Client & client)
{
  _threadPool.removeClient(client);
}
