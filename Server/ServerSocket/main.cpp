#include "Server.hh"

int	main()
{
  Server s;

  if ((s.runServer()) == 1)
    return (1);
  return (0);
}
