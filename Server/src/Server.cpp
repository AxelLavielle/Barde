#include "Server.hh"

Server::Server(boost::asio::io_service& io_service) : _acceptor(io_service, tcp::endpoint(tcp::v4(), 13))
{
  this->start_accept();
}

void Server::start_accept()
{
  Connection::pointer new_connection = Connection::create(_acceptor.get_io_service());

  _acceptor.async_accept(new_connection->getSocket(),
  boost::bind(&Server::handle_accept, this, new_connection,
    boost::asio::placeholders::error));
}

void Server::handle_accept(Connection::pointer new_connection, const boost::system::error_code& error)
{
  if (!error)
  {
    new_connection->start();
  }
  this->start_accept();
}
