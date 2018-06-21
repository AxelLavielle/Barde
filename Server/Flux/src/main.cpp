#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

#include "CmdManager.hh"

int			main()
{
  struct protoent	*pe;
  int			fd;
  struct sockaddr_in	server;
  struct sockaddr_in	client;
  int			port;
  socklen_t		client_size;
  int			client_fd;
  char			buffer[100];
  port = 23;

  if (!(pe = getprotobyname("TCP")))
    return (1);
  client_size = sizeof(struct sockaddr_in);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = INADDR_ANY;
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (1);
  if (bind(fd, (const struct sockaddr *)&server, sizeof(server)) == -1)
    {
      if (close(fd) == -1)
	return (1);
      return (1);
    }

  if (listen(fd, 2) == -1)
    {
      if (close(fd) == -1)
	return (1);
      return (1);
    }
  if ((client_fd = accept(fd, (struct sockaddr *)&client, (socklen_t *)&client_size)) == -1)
    {
      if (close(fd) == -1)
	return (1);
      return (1);
    }
  std::cout << "le fs = " << client_fd << std::endl;
  write(client_fd, "coucoutoi\r\n", strlen("coucoutoi\r\n"));
  CmdManager cmd;

  cmd.sendMusicData(client_fd);
  while (read(client_fd, buffer, 100))
  {
    std::cout << buffer << std::endl;
    memset(&buffer, 0, strlen(buffer));
  }
  if (close(fd) == -1)
    return (1);
  if (close(client_fd) == -1)
    return (1);
}
