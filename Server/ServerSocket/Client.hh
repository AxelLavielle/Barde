#ifndef __CLIENT__HH__
# define __CLIENT_HH__

class Client
{
private:
  int		_fd;
public:
  Client(int fd);
  const int	getFd();
};

#endif /* __CLIENT__HH__*/
