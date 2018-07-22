#include "Server.hh"

Server::Server(boost::asio::io_service& io_service) : _acceptor(io_service, tcp::endpoint(tcp::v4(), PORT)), _genPool(2), _playPool(2)
{
  this->start_accept();
  boost::asio::post(_genPool, Server::Gen);
  boost::asio::post(_playPool, Server::Play);
}

Server::~Server(){
  _genPool.join();
  _playPool.join();
}

void Server::start_accept()
{
  Connection::pointer new_connection = Connection::create(_acceptor.get_io_service(), &_genPool, &_playPool);

  _acceptor.async_accept(new_connection->getSocket(),
  boost::bind(&Server::handle_accept, this, new_connection,
    boost::asio::placeholders::error));
}

void Server::handle_accept(Connection::pointer new_connection, const boost::system::error_code& error)
{
  if (!error)
  {
    new_connection->start();
    this->start_accept();
  }
}

void Server::Gen(const std::string& command){
  std::vector<std::string> params;
  size_t i;
  Instrument instrument;

  _genMtx.lock();
  boost::algorithm::split(params, command, boost::algorithm::is_any_of(" "));
  _mp.setStyleName(params[0]);
  _mp.setBpm(std::stoi(params[1]));
  i = 2;
  while (i != params.size())
  {
    instrument.name = params[i];
    instrument.nb = instrumentList.find(params[i++])->second;
    instrument.channel = 1;
    instrument.velocity = 100;
    _mp.addInstrumentChords(instrument);
  }
  _mg.createMusic(_mp);
  _genMtx.unlock();
}

void Server::Play(const tcp::socket& socket){
  _playMtx.lock();
  _playMtx.unlock();
}
