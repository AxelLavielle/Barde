#ifndef __CMDMANAGER__HH__
# define __CMDMANAGER__HH__

#include <map>
#include <sys/types.h>
#include <sys/socket.h>

#include "Client.hh"
#include "Instrument.hh"
#include "AI/MusicGenerator.hh"
#include "ThreadPoolGenerator.hh"

#define BAD_REQUEST 0xC8
#define OK_REQUEST 0xC8

#define ADDCHORD_REQUEST 0x21
#define ADDAEPEGES_REQUEST 0x31
#define REMOVECHORD_REQUEST 0x61
#define REMOVEAEPEGES_REQUEST 0x71
#define DRUMS_REQUEST 0x41
#define STYLE_REQUEST 0x11
#define BPM_REQUEST 0x51
#define DISCONNECTION_REQUEST 0x3

#define UNKNOW_REQUEST 0x0

class CmdManager
{
public:
  CmdManager();
  ~CmdManager();
  void	parseMessage(int *buffer, Client &client, size_t bufferSize);
  void  disconnectClient(const Client & client);
//  static void sendResponseMessage(const int responseCode, const int responseType, const Client & client, const std::string & message);
  static void sendResponseMessage(const int responseCode, const int responseType, const int data, const Client & client, const std::string & message);

private:
  void manageMusicParameter(int *buffer, Client &client, size_t bufferSize);
  void managePlayerCtrl(int *buffer, Client &client, size_t bufferSize);
  void manageDisconnection(int *buffer, Client &client, size_t bufferSize);
  void manageInstruments(const bool & add, const Client & client, const bool & arpeggios, const NbInstrument instruNb);
  std::map<int, std::function<void(int *buffer, Client &client, size_t bufferSize) > > _cmdFunctions;
  std::map<int, std::function<void(Client &client) > > _playerCtrlFunctions;

  ThreadPoolGenerator      _threadPool;
};

#endif /* __CMDMANAGER__HH__*/
