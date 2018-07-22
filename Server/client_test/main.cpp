#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

#define HOST "127.0.0.1"
#define PORT 2468

void send_msg(boost::asio::ip::tcp::socket *socket, std::string msg)
{
	boost::system::error_code error;
	boost::asio::write(*socket, boost::asio::buffer(msg), error);
}

int main()
{
	boost::asio::io_service ios;
	boost::asio::ip::tcp::socket *socket = new boost::asio::ip::tcp::socket(ios);
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(HOST), PORT);

	socket->connect(endpoint);
	send_msg(socket, "Blues 90 ACOUSTICGRANDPIANO\n");
	socket->close();
	return 0;
}
