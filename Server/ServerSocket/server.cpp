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
      int entries = _so.handleEntries(&_clients, "hello\r\n");
      if (entries == 1)
	return (1);
      else if (entries != 2)
	{
	  std::list<Client>::iterator it = _clients.begin();
	  while (it != _clients.end())
	    {
	      sd = it->getFd();
	      if (_so.fdIsSet(sd))
		{

		  if ((_so.readClient(sd)) == 1)
		    return (1);
		  if (_so.getLastSizeOfMessage() > 0)
		    {
		      _cm.parseMessage(_so.getLastMessage(), *it, _so.getLastSizeOfMessage());
		      it++;
		    }
		  else
		    {
		      std::cout << "client " << sd << "est partie" << std::endl;
		      _cm.disconnectClient(*it);
		      if ((_so.closeFd(sd)) == 1)
			return (1);
		      _clients.erase(it++);
		    }
		}
	      else
		{
		  it++;
		}
	    }
	}
    }
}
