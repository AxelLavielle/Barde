#ifndef __CLIENT__HH__
# define __CLIENT__HH__

#include <ctime>

#include "MusicParameters.hh"

class			Client
{
private:
  int			_fd;
  MusicParameters	_mp;
  unsigned short  _nbGeneration;
public:
  Client();
  Client(int fd);
  Client(const Client & client);
  const int		getFd() const;
  MusicParameters	getMp() const;
  bool operator==(const Client & lv);
  Client &operator=(const Client & client);
  void addGeneration();
  void refreshGeneration();
  bool needGeneration() const;
  unsigned short getNbGeneration() const;
};

#endif /* __CLIENT__HH__ */
