#include "Client.hh"

Client::Client(int fd)
{
  _fd = fd;
  // _mp.setInstrumentsDrums(true);
  _mp.setSeed(std::time(NULL));
  // _mp.setBpm(120);
  // Instrument instru;
  // instru.name = "Piano";
  // instru.nb = ACOUSTICGRANDPIANO;
  // instru.channel = 1;
  // instru.velocity = 100; //Need change
  // _mp.addInstrumentChords(instru);
  //_mp.addInstrumentArpeggios(instru);
   _mp.setStyleName("Blues");
  srand(_mp.getSeed()); //Need to change that

  _nbGeneration = 0;
}

Client::Client()
{
  _fd = -1;
  // _mp.setInstrumentsDrums(true);
  // _mp.setSeed(std::time(NULL));
  // _mp.setBpm(120);
  // Instrument instru;
  // instru.name = "Piano";
  // instru.nb = ACOUSTICGRANDPIANO;
  // instru.channel = 1;
  // instru.velocity = 100; //Need change
  // _mp.addInstrumentChords(instru);
  // _mp.addInstrumentArpeggios(instru);
  // _mp.setStyleName("Blues");
  srand(_mp.getSeed()); //Need to change that

  _nbGeneration = 0;
}

Client::Client(const Client & client)
{
  *this = client;
}

Client &Client::operator=(const Client & client)
{
  _fd = client.getFd();
  _mp = client.getMp();
  _nbGeneration = client.getNbGeneration();
}

unsigned short Client::getNbGeneration() const
{
  return (_nbGeneration);
}

const int	Client::getFd() const
{
  return _fd;
}

MusicParameters	Client::getMp() const
{
  return _mp;
}

void Client::addInstrumentArpeggios(Instrument instru)
{
  _mp.addInstrumentArpeggios(instru);
}

void Client::addInstrumentChords(Instrument instru)
{
  _mp.addInstrumentChords(instru);
}

void Client::delInstrumentArpeggios(Instrument instru)
{
  _mp.delInstrumentArpeggios(instru);
}

void Client::delInstrumentChords(Instrument instru)
{
  _mp.delInstrumentChords(instru);
}

void Client::setInstrumentsDrums(bool drum)
{
  _mp.setInstrumentsDrums(drum);
}

void Client::setStyleName(std::string style)
{
  _mp.setStyleName(style);
}


void Client::setBpm(int value)
{
  _mp.setBpm(value);
}


bool Client::operator==(const Client & lv)
{
  return (lv.getFd() == getFd());
}

void Client::addGeneration()
{
  _nbGeneration += 1;
}

void Client::refreshGeneration()
{
  _nbGeneration = 0;
}

bool Client::needGeneration() const
{
  return (_nbGeneration < 5); //5 is arbritary
}
