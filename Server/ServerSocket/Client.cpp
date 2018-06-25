#include "Client.hh"

Client::Client(int fd)
{
  _fd = fd;
}

const int	Client::getFd() const
{
  return _fd;
}

MusicParameters	Client::getMp()
{
  return _mp;
}

bool Client::operator==(const Client & lv)
{
  return (lv.getFd() == getFd());
}
