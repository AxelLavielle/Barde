#ifndef __CLIENT__HH__
# define __CLIENT__HH__

#include <ctime>

#include "MusicParameters.hh"

#define NB_GENERATION_PER_PACKET 5 //5 is arbritary

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
  int		getFd() const;
  MusicParameters	getMp() const;
  MusicParameters changeMusiqueParameter();
  void addInstrumentArpeggios(Instrument instru);
  void addInstrumentChords(Instrument instru);
  void delInstrumentArpeggios(Instrument instru);
  void delInstrumentChords(Instrument instru);
  void setInstrumentsDrums(bool drum);
  void setStyleName(std::string style);
  void setBpm(int value);
  void setSeed(int seed);
  bool operator==(const Client & lv);
  Client &operator=(const Client & client);
  void addGeneration();
  void refreshGeneration();
  bool needGeneration() const;
  unsigned short getNbGeneration() const;
};

#endif /* __CLIENT__HH__ */
