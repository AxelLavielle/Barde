#include "Client.hh"

Client::Client(int fd)
{
  _fd = fd;
}

const int	Client::getFd()
{
  return _fd;
}
