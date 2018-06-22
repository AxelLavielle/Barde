#include "socket.hh"

Socket::Socket()
{
  _port = 23;
  _client_size = sizeof(struct sockaddr_in);
  _server.sin_family = AF_INET;
  _server.sin_port = htons(_port);
  _server.sin_addr.s_addr = INADDR_ANY;
  _message = NULL;
  _sizeOfMessage = 0;
}

int Socket::StartSocket()
{
  if (!(_pe = getprotobyname("TCP")))
    {
      std::cerr << "error to get the proto name " << std::endl;
      return (1);
    }
  if ((_fd = socket(AF_INET, SOCK_STREAM, _pe->p_proto)) == -1)
    {
      std::cerr << "failed to create socket" << std::endl;
      return (1);
    }
  if (bind(_fd, (const struct sockaddr *)&_server, sizeof(_server)) == -1)
    {
      std::cerr << "failed to bind" << std::endl;
      if (close(_fd) == -1)
	{
	  std::cerr << "failed to close socket" << std::endl;
	  return (1);
	}
      return (1);
    }

  if (listen(_fd, 2) == -1)
    {
      std::cerr << "failed to set listen" << std::endl;
      if (close(_fd) == -1)
	{
	  std::cerr << "failed to close socket" << std::endl;
	  return (1);
	}
      return (1);
    }

  return (0);
}

char *Socket::getLastMessage()
{
  return _message;
}

unsigned long Socket::getLastSizeOfMessage()
{
  return _sizeOfMessage;
}

int Socket::readClient(int client_fd)
{
  char buffer[30];
  int len = 0;
  int i = 0;
  int j = 0;
  if (_message != NULL)
    {
      free(_message);
      _sizeOfMessage = 0;
    }
  if ((_message = (char *)calloc(0, sizeof(char *))) == NULL)
    {
      std::cerr << "failed to malloc message with 0 as size " << std::endl;
      return (1);
    }

  while ((len = read(client_fd, buffer, 30)) >= 30)
    {
      j = 0;
      _sizeOfMessage += len;
      if ((_message = (char *)realloc(_message, _sizeOfMessage * sizeof(char *))) == NULL)
	{
	  std::cerr << "failed to realloc message with " << _sizeOfMessage << "as size" << std::endl;
	  return (1);
	}
      
      while (len > 0)
	{
	  _message[i] = buffer[j];
	  len--;
	  i++;
	  j++;
	}
    }
  if (_sizeOfMessage == 0 && len  == 0)
    return (0);
  else
    {
      _sizeOfMessage += len;
      if (( _message = (char *)realloc(_message, _sizeOfMessage * sizeof(char *))) == NULL)
	{
	  std::cerr << "failed to realloc message with " << _sizeOfMessage << "as size" << std::endl;
	  return (1);
	}
      j = 0;
      while (len > 0)
	{
	  _message[i] = buffer[j];
	  i++;
	  j++;
	  len--;
	}
    }
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
    {
      std::cerr << "failed to close socket" << std::endl;
      return (1);
    }
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
  select(_max_sd +1, &_master, NULL, NULL, NULL);
  if (FD_ISSET(_fd, &_master))
    {
      if ((client_fd = accept(_fd, (struct sockaddr *)&_client, (socklen_t *)&_client_size)) == -1)
	{
	  std::cerr << "failed to accept incoming new connection" << std::endl;
	  return (1);
	}

      if ((send(client_fd, msg, strlen(msg), 0)) == -1)
	{
	  std::cerr << "failed to send \"" << msg << "\" message" << std::endl;
	  return (1);
	}
      std::cout << "client " << client_fd << " a rejoin le server" << std::endl;
      clients->push_back(Client(client_fd));
      FD_SET(client_fd, &_master);
    }
  return (0);
}
