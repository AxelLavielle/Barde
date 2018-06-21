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


void Socket::runMultiClient()
{
  int	client_socket[30];
  int max_sd;
  int client_fd;

  int sd = 0;
  for(int i = 0; i < 30; i++)
    {
      client_socket[i] = 0;
    }

  while (1)
    {
      FD_ZERO(&_master);
      FD_SET(_fd, &_master);
      max_sd = _fd;

      for (int i = 0; i < 30; i++)
	{
	  sd = client_socket[i];
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
	  for (int i = 0; i < 30; i++)
	    {
	      if (client_socket[i] == 0)
		{
		  client_socket[i] = client_fd;
		  FD_SET(client_fd, &_master);
		  break;
		}
	    }
	}
      for (int i = 0; i < 30; i++)
	{
	  sd = client_socket[i];
	  if (FD_ISSET(sd, &_master))
	    {
	      if (read(sd, _buffer, 100))
		{
		  std::cout << "client " << sd << "message : " << _buffer << std::endl;
		}
	      else
		{
		  /*if (close(client_fd) == -1)
		    return (1);
		    client_socket[i] = 0;*/
		}
	      memset(&_buffer, 0, strlen(_buffer));
	    }
	}
    }
}
