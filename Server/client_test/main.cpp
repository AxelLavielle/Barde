#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>


void send_msg(std::string host, int port, std::string msg)
{
	boost::asio::io_service ios;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);
	boost::asio::ip::tcp::socket socket(ios);

	socket.connect(endpoint);
	boost::system::error_code error;
	boost::asio::write(socket, boost::asio::buffer(msg), error);
  socket.close();
}

int main()
{
    send_msg("127.0.0.1", 2468, "Bardinho\n");
    return 0;
}
