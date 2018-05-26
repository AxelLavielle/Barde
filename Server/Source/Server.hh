#ifndef SERVER_HH_
# define SERVER_HH_

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/thread/mutex.hpp>
#include "AI/MusicGenerator.hh"
#include "MusicParameters.hh"
#include "Connection.hh"

#define PORT 2468

using boost::asio::ip::tcp;

class Server
{
public:
  Server(boost::asio::io_service& io_service);
  ~Server();

private:
  void start_accept();
  void handle_accept(Connection::pointer new_connection, const boost::system::error_code& error);
  void Gen(const std::string& command);
  void Play(const tcp::socket& socket);

  tcp::acceptor _acceptor;
  boost::asio::thread_pool _genPool;
  boost::asio::thread_pool _playPool;
  MusicParameters _mp;
  MusicGenerator _mg;
  boost::mutex _genMtx;
  boost::mutex _playMtx;
};

#endif //SERVER_HH
