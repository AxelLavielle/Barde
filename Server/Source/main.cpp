#include "Connection.hh"
#include "Server.hh"

int main()
{
  try
  {
    boost::asio::io_service io_service;
    Server server(io_service);
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
