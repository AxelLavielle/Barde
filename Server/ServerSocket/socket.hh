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
#include <cerrno>
class Socket
{
private:
  int			_max_sd;
  struct protoent	*_pe;
  int			_fd;
  struct sockaddr_in	_server;
  struct sockaddr_in	_client;
  int			_port;
  socklen_t		_client_size;
  char			_buffer[30];
  fd_set		_master;
  int			*_message;
  unsigned long		_sizeOfMessage;
public:
  Socket();
  int			StartSocket();
  int     stopSocket();
  int			handleEntries(std::list<Client> *clients, char *msg);
  void			initFd();
  int			fdIsSet(int fd);
  void			addFdAndsetMax(int sd);
  int			closeFd(int fd);
  int			readClient(int client_fd);
  int			*getLastMessage();
  unsigned long		getLastSizeOfMessage();
};

#endif /* __SOCKET__HH__*/
