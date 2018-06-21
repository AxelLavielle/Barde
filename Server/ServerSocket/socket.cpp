#include "socket.hh"

Socket::Socket()
{
  _port = 23;
  _client_size = sizeof(struct sockaddr_in);
  _server.sin_family = AF_INET;
  _server.sin_port = htons(_port);
  _server.sin_addr.s_addr = INADDR_ANY;
}

int Socket::StartSocket()
{
  if (!(_pe = getprotobyname("TCP")))
    return (1);
  if ((_fd = socket(AF_INET, SOCK_STREAM, _pe->p_proto)) == -1)
    return (1);
  if (bind(_fd, (const struct sockaddr *)&_server, sizeof(_server)) == -1)
    {
      if (close(_fd) == -1)
	return (1);
      return (1);
    }
  
  if (listen(_fd, 2) == -1)
    {
      if (close(_fd) == -1)
	return (1);
      return (1);
    }
  return (0);
}

std::string	Socket::readClient(int client_fd)
{
  char	buffer[30];
  std::ostringstream ss;
  int len = 0;
  while ((len = read(client_fd, buffer, 30)) >= 30)
    {
      ss << buffer;
      memset(&_buffer, 0, strlen(_buffer));
    }
  ss << buffer;
  std::string str = ss.str();
  return str;
}

void Socket::runMultiClient()
{
  int max_sd;
  int client_fd;
  std::string   buffer;
  int sd = 0;

  while (1)
    {
      FD_ZERO(&_master);
      FD_SET(_fd, &_master);
      max_sd = _fd;

      for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
	  sd = it->getFd();
	  if (sd > 0)
	    {
	       FD_SET(sd, &_master);
	    }
	  if (sd > max_sd)
	    {
	      max_sd = sd;
	    }
	}
      int socketCount = select(max_sd +1, &_master, NULL, NULL, NULL);
      if (FD_ISSET(_fd, &_master))
	{
	  client_fd = accept(_fd, (struct sockaddr *)&_client, (socklen_t *)&_client_size);

	  send(client_fd, "hello\r\n", strlen("hello\r\n"), 0);
	  _clients.push_back(Client(client_fd));
	  FD_SET(client_fd, &_master);
	}
      for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
	  sd = it->getFd();
	  if (FD_ISSET(sd, &_master))
	    {
	      buffer = Socket::readClient(sd);
	      if (!buffer.empty())
		{
		  std::cout << "client " << sd << "message : " << buffer << std::endl;
		}
	      else
		{
		  /*if (close(client_fd) == -1)
		    return (1);
		    */
		}
	  
	    }
	}
    }
}
