#ifndef PLAYER_H_
# define PLAYER_H_

# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <vlc/vlc.h>

class Player {
private:
  libvlc_instance_t *_vlc;
  std::vector<std::string> _streams;
  std::string _port;
public:
  Player(std::string port = "3333");
  ~Player();
  int infoStream(std::string user);
  int newStream(std::string user, std::string media, bool loop, bool play);
  int deleteStream(std::string user);
  int playStream(std::string user);
  int stopStream(std::string user);
  int addMediaStream(std::string user, std::string media);
  bool existStream(std::string user);
};

#endif
