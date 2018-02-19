#ifndef _CONNECTION_HH_
#define _CONNECTION_HH_

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "MusicParameters.hh"
#include "AI/MusicGenerator.hh"

using boost::asio::ip::tcp;

class Connection : public boost::enable_shared_from_this<Connection>
{
public:
  typedef boost::shared_ptr<Connection> pointer;
  static pointer create(boost::asio::io_service& io_service);
  tcp::socket& getSocket();
  void start();

private:
  Connection(boost::asio::io_service& io_service);
  void handle_write(const boost::system::error_code& error);
  void handle_receive(const boost::system::error_code& error);
  std::string make_daytime_string() const;

  tcp::socket _socket;
  std::string _message;
  boost::asio::streambuf _buffer;
  MusicParameters _mp;
  MusicGenerator _mg;
};

#endif //_CONNECTION_HH_
