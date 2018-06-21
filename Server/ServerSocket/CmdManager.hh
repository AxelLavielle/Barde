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
  ThreadPoolGenerator      _threadPool;
};

#endif /* __CMDMANAGER__HH__*/
