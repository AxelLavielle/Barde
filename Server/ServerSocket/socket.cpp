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

int		Socket::readClient(int client_fd, char *str, int *size)
{
  char	buffer[30];
  int len = 0;
  int	i = 0;
  int	j = 0;
  while ((len = read(client_fd, buffer, 30)) >= 30)
    {
      j = 0;
      *size += len;
      str = (char *)realloc(str, len * sizeof(char *));
      while (len > 0)
	{
	  str[i] = buffer[j];
	  len--;
	  i++;
	  j++;
	}
      memset(&_buffer, 0, strlen(_buffer));
      }
  if (len == 0)
    return (0);
  else
    {
      *size += len;
      str = (char *)realloc(str, len * sizeof(char *));
      //std::cout << "la dernier length " << len << std::endl;
      j = 0;
      while (len > 0)
	{
	  str[i] = buffer[j];
	  i++;
	  j++;
	  len--;
	}
      str[i] = '\0';
    }
  //  std::cout << "la valeur de read " << str << std::endl;

  return (0);
}

void	Socket::addFdAndsetMax(int sd)
{
  if (sd > 0)
    {
      FD_SET(sd, &_master);
    }
  if (sd > _max_sd)
    {
      _max_sd = sd;
    }
}

int	Socket::fdIsSet(int fd)
{
  return FD_ISSET(fd, &_master);
}

int	Socket::closeFd(int fd)
{
  if (close(fd) == -1)
    return (1);
  FD_CLR(fd, &_master);
  return 0;
}

void	Socket::initFd()
{
  FD_ZERO(&_master);
  FD_SET(_fd, &_master);
  _max_sd = _fd;
}

int	Socket::handleEntries(std::list<Client> *clients, char *msg)
{
  int client_fd;
  int socketCount = select(_max_sd +1, &_master, NULL, NULL, NULL);
  if (FD_ISSET(_fd, &_master))
    {
      client_fd = accept(_fd, (struct sockaddr *)&_client, (socklen_t *)&_client_size);

      send(client_fd, msg, strlen(msg), 0);
      std::cout << "client " << client_fd << " a rejoin le server" << std::endl;
      clients->push_back(Client(client_fd));
      FD_SET(client_fd, &_master);
    }
  return (0);
}
