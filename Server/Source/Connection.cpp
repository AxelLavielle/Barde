#include "Connection.hh"

Connection::Connection(boost::asio::io_service& io_service, boost::asio::thread_pool *genPool, boost::asio::thread_pool *playPool) : _socket(io_service), _genPool(genPool), _playPool(playPool)
{
}

Connection::pointer Connection::create(boost::asio::io_service& io_service, boost::asio::thread_pool *genPool, boost::asio::thread_pool *playPool)
{
  return pointer(new Connection(io_service, genPool, playPool));
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
  std::string command;

  if (error) {
    std::cout << "Couldn't read client's message : " << error.message() << std::endl;
    return;
  }
  std::cout << "[" << _socket.remote_endpoint().address().to_string() << ":" << _socket.remote_endpoint().port() << "]" << std::endl;
  std::istream is(&_buffer);
  std::getline(is, command);
  std::cout << command;
  std::cout << "Waiting for music generation..." << std::endl;
  boost::asio::post(_genPool, );
  std::cout << "Generation done !" << std::endl;
  std::cout << "Waiting for music to play..." << std::endl;
  boost::asio::post(_playPool, _socket);
  std::cout << "Hope you had fun !" << std::endl;
}

std::string Connection::make_daytime_string() const
{
  using namespace std;
  time_t now = time(0);
  return ctime(&now);
}
