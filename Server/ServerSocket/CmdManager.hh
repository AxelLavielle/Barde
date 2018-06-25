#ifndef __CMDMANAGER__HH__
# define __CMDMANAGER__HH__

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

  std::function<void(int *data)> _cmdFunctions[3];
  std::function<void(int *data)> _playerCtrlFunctions[4];

  ThreadPoolGenerator      _threadPool;
};

#endif /* __CMDMANAGER__HH__*/
