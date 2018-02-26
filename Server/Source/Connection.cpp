#include <boost/algorithm/string.hpp>
#include "Connection.hh"

Connection::Connection(boost::asio::io_service& io_service) : _socket(io_service)
{
}

Connection::pointer Connection::create(boost::asio::io_service& io_service)
{
  return pointer(new Connection(io_service));
}

tcp::socket& Connection::getSocket()
{
  return _socket;
}

void Connection::start()
{
  _message = this->make_daytime_string();

  std::cout << _socket.remote_endpoint().address().to_string() << ":" << _socket.remote_endpoint().port() << " connected!" << std::endl;
  boost::asio::async_write(_socket, _buffer,
    boost::bind(&Connection::handle_write, shared_from_this(),
        boost::asio::placeholders::error));
  boost::asio::async_read_until(_socket, _buffer, '\n',
    boost::bind(&Connection::handle_receive, shared_from_this(),
      boost::asio::placeholders::error));
}

void Connection::handle_write(const boost::system::error_code& error)
{
  if (error){
    std::cout << "Connection::handle_write : " << error.message() << std::endl;
  }
}

void Connection::handle_receive(const boost::system::error_code& error)
{
  std::string line;

  if (error) {
    std::cout << "Couldn't read client's message : " << error.message() << std::endl;
    return;
  }
  std::cout << "[" << _socket.remote_endpoint().address().to_string() << ":" << _socket.remote_endpoint().port() << "]" << std::endl;
  std::istream is(&_buffer);
  std::getline(is, line);
  std::cout << line;
  parseGenRequest(line);
  _mg.createMusic(_mp);
}

void Connection::parseGenRequest(const std::string& command)
{
  std::vector<std::string> params;
  size_t i;
  Instrument instrument;

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
    _mp.addInstrument(instrument);
  }
}

std::string Connection::make_daytime_string() const
{
  using namespace std;
  time_t now = time(0);
  return ctime(&now);
}
