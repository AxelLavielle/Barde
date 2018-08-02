#include "Server.hh"

Server::Server()
{
//  signal(SIGINT, std::bind(&Server::signalHandler, this, std::placeholders::_1));
}

void Server::signalHandler(int signal)
{
  _so.stopSocket();
  std::cout << "COUCOU SIGNAL" << std::endl;
  exit(1); //Need to change that
}

void	Server::setPort(int port)
{
  _so.setPort(port);
}

int	Server::runServer()
{
  if (_so.StartSocket() == 1)
    return (1);
  std::cout << "Server is ready" << std::endl;
  while (1)
    {
      _so.initFd();

      int sd;
      for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
	  _so.addFdAndsetMax(it->getFd());
	}
      std::cout << "LA 0" << std::endl;
      int entries = _so.handleEntries(&_clients, "hello\r\n");
      std::cout << "Next handleEntries" << std::endl;
      if (entries == 1)
	return (1);
      else if (entries != 2)
	{
	  std::cout << "LA 1" << std::endl;
	  std::list<Client>::iterator it = _clients.begin();
	  std::cout << "LA 2" << std::endl;
	  while (it != _clients.end())
	    {
	      std::cout << "LA 3" << std::endl;
	      sd = it->getFd();
	      std::cout << "LA 4" << std::endl;
	      if (_so.fdIsSet(sd))
		{
		  std::cout << "LA 5" << std::endl;
		  
		  if ((_so.readClient(sd)) == 1)
		    {
		      std::cout << "LA 6" << std::endl;
		      return (1);
		    }
		  if (_so.getLastSizeOfMessage() > 0)
		    {
		      std::cout << "LA 7" << std::endl;
		      _cm.parseMessage(_so.getLastMessage(), *it, _so.getLastSizeOfMessage());
		      std::cout << "LA 8" << std::endl;
		      it++;
		    }
		  else
		    {
		      std::cout << "client " << sd << "est partie" << std::endl;
		      _cm.disconnectClient(*it);
		      std::cout << "LA 9" << std::endl;
		      if ((_so.closeFd(sd)) == 1)
			{
			  std::cout << "LA 10" << std::endl;
			  return (1);
			}
		      std::cout << "LA 11" << std::endl;
		      _clients.erase(it++);
		      std::cout << "LA 12" << std::endl;
		    }
		}
	      else
		{
		  std::cout << "LA 13" << std::endl;
		  it++;
		}
	    }
	}
    }
}
