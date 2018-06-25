#ifndef __CLIENT__HH__
# define __CLIENT__HH__

#include <ctime>

#include "MusicParameters.hh"

class			Client
{
private:
  int			_fd;
  MusicParameters	_mp;
public:
  Client(int fd);
  const int		getFd() const;
  MusicParameters	getMp();
  bool operator==(const Client & lv);
};

#endif /* __CLIENT__HH__ */
