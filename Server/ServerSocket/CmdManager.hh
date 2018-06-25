#ifndef __CMDMANAGER__HH__
# define __CMDMANAGER__HH__

#include <map>

#include "Client.hh"
#include "ThreadPoolGenerator.hh"

class CmdManager
{
public:
  CmdManager();
  void	parseMessage(char *buffer, Client &client, size_t bufferSize);
  void  disconnectClient(const Client & client);

private:
  void manageMusicParameter(int *data);
  void managePlayerCtrl(int *data);
  void manageDisconnection(int *data);

  std::map<int, std::function<void(int *data) > > _cmdFunctions;
  std::map<int, std::function<void(int *data) > > _playerCtrlFunctions;

  ThreadPoolGenerator      _threadPool;
};

#endif /* __CMDMANAGER__HH__*/
