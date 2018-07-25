#ifndef __SERVER__HH__
# define __SERVER__HH__

#include "socket.hh"
#include "Client.hh"
#include "CmdManager.hh"

class Server
{
private:
  Socket		_so;
  std::list<Client>	_clients;
  CmdManager		_cm;
public:
  Server();
  void			setPort(int port);
  int			runServer();
  void			signalHandler(int signal);
};

#endif /* __SERVER__HH__ */
