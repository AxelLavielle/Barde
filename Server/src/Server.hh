#ifndef SERVER_HH_
# define SERVER_HH_

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "Connection.hh"

#define PORT 2468

class Server
{
public:
  Server(boost::asio::io_service& io_service);

private:
  void start_accept();
  void handle_accept(Connection::pointer new_connection, const boost::system::error_code& error);

  tcp::acceptor _acceptor;
};

#endif //SERVER_HH
