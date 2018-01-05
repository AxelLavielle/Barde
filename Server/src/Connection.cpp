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

  boost::asio::async_write(_socket, boost::asio::buffer(_message),
      boost::bind(&Connection::handle_write, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void Connection::handle_write(const boost::system::error_code&, size_t)
{
}

std::string Connection::make_daytime_string() const
{
  using namespace std;
  time_t now = time(0);
  return ctime(&now);
}
