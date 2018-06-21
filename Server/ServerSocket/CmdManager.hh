#ifndef __CMDMANAGER__HH__
# define __CMDMANAGER__HH__

#include "Client.hh"

class CmdManager
{
public:
  CmdManager();
  void	parseMessage(char *buffer, Client &client);
};

#endif /* __CMDMANAGER__HH__*/
