#include "Server.hh"

Server::Server()
{
  
}

int	Server::runServer()
{
  _so.StartSocket();
  while (1)
    {
      _so.initFd();
      
      int sd;
      for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
	  _so.addFdAndsetMax(it->getFd());
	}
      _so.handleEntries(&_clients, "hello\r\n");
      
      std::list<Client>::iterator it = _clients.begin();      
      while (it != _clients.end())
	{
	  
	  sd = it->getFd();
	  if (_so.fdIsSet(sd))
	    {
	      char *str;
	      int size = 0;
	      str = (char *)malloc(1 * sizeof(char*));
	      int len = _so.readClient(sd, str, &size);
	      if (size > 0)
		{
		  //std::cout << "message recu: " << str << "pour size = " << size << std::endl;
		  _cm.parseMessage(str, *it, size);
		  it++;
		}
	      else
		{
		  std::cout << "client " << sd << "est partie" << std::endl;
		  _so.closeFd(sd);
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
