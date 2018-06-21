#ifndef __CLIENT__HH__
# define __CLIENT__HH__

#include "MusicParameters.hh"

class			Client
{
private:
  int			_fd;
  MusicParameters	_mp;
public:
  Client(int fd);
  const int		getFd();
  MusicParameters	getMp();
};

#endif /* __CLIENT__HH__ */
