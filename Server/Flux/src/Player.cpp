#include "Player.h"

Player::Player(std::string port) {
  _vlc = libvlc_new(0, NULL);
  if (!_vlc) {
    std::cerr << "Failed to create vlc instance" << std::endl;
  }
  _port = port;
}

Player::~Player() {
  libvlc_vlm_release(_vlc);
}

int Player::infoStream(std::string user) {
  const char  *str;

  if ((str = libvlc_vlm_show_media(_vlc, user.c_str())) == NULL) {
    std::cerr << "Failed to show media info of " << user << std::endl;
    return -1;
  }
  std::cout << str << std::endl;
  return 0;
}

int Player::newStream(std::string user, std::string media, bool loop, bool play) {
  // std::string output("#transcode{vcodec=none,acodec=mpga,vb=800,ab=128,deinterlace}:duplicate{dst=rtp{sdp=rtsp://:");
  std::string output("#transcode{vcodec=none,acodec=mpga,vb=800,ab=128,deinterlace}:standard{access=http,mux=ts{use-key-frames},dst=:");

  if (this->existStream(user)) {
    std::cerr << "Stream " << user << " already exist" << std::endl;
    return -1;
  }
  output += _port;
  output += "/";
  output += user;
  output += "}";
  if (libvlc_vlm_add_broadcast(_vlc, user.c_str(), media.c_str(), output.c_str(), 0, NULL, true, loop) == -1) {
    std::cerr << "Failed to add broadcast " << user << " with input " << media << std::endl;
    return -1;
  }
  _streams.push_back(user);
  if (play) {
    return this->playStream(user);
  }
  return 0;
}

int Player::deleteStream(std::string user) {
  if (libvlc_vlm_del_media(_vlc, user.c_str()) == -1) {
    std::cerr << "Failed to delete media " << user << std::endl;
    return -1;
  }
  for (unsigned int i = 0; i < _streams.size(); ++i) {
    if (_streams[i] == user) {
      _streams.erase(_streams.begin() + i);
    }
  }
  return 0;
}

int Player::playStream(std::string user) {
  if (libvlc_vlm_play_media(_vlc, user.c_str()) == -1) {
    std::cerr << "Failed to play media " << user << std::endl;
    return -1;
  }
  return 0;
}

int Player::stopStream(std::string user) {
  if (libvlc_vlm_show_media(_vlc, user.c_str()) == NULL) {
    std::cerr << "Failed to stop media " << user << std::endl;
    return -1;
  }
  return 0;
}

int Player::addMediaStream(std::string user, std::string media) {
  if (libvlc_vlm_add_input(_vlc, user.c_str(), media.c_str()) == -1) {
    std::cerr << "Failed to add input " << media << " to media " << user << std::endl;
    return -1;
  }
  return 0;
}

bool Player::existStream(std::string user) {
  for (unsigned int i = 0; i < _streams.size(); ++i) {
    if (_streams[i] == user) {
      return true;
    }
  }
  return false;
}
