#ifndef __SOCKET__HH__
#define __SOCKET__HH__

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/select.h>
#include <list>
#include "Client.hh"
#include <string>
#include "CmdManager.hh"

class Socket
{
private:
  struct protoent	*_pe;
  int			_fd;
  struct sockaddr_in	_server;
  struct sockaddr_in	_client;
  int			_port;
  socklen_t		_client_size;
  char			_buffer[30];
  fd_set		_master;
  std::list<Client>	_clients;
  std::string		readClient(int client_fd);
  CmdManager		_cm;
public:
  Socket();
  int			runMultiClient();
  int			StartSocket();
};

#endif /* __SOCKET__HH__*/
