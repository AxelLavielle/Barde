#include "Client.hh"

Client::Client(int fd)
{
  _fd = fd;
  _mp.setInstrumentsDrums(true);
  _mp.setSeed(std::time(NULL));
  _mp.setBpm(120);
  Instrument instru;
  instru.name = "Piano";
  instru.nb = ACOUSTICGRANDPIANO;
  instru.channel = 1;
  instru.velocity = 100; //Need change
  _mp.addInstrumentChords(instru);
  _mp.addInstrumentArpeggios(instru);
  _mp.setStyleName("Blues");
  srand(_mp.getSeed()); //Need to change that
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
