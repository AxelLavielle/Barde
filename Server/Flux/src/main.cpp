#include "Player.h"

int execCommand(Player *player, std::vector<std::string> command) {
  if (command[0] == "exit") {
    return -1;
  }
  else if (command[0] == "new") {
    player->newStream(command[1], command[2], true, true);
  }
  else if (command[0] == "delete") {
    player->deleteStream(command[1]);
  }
  else if (command[0] == "play") {
    player->playStream(command[1]); // MARCHE PAS
  }
  else if (command[0] == "stop") {
    player->stopStream(command[1]); // MARCHE PAS
  }
  else if (command[0] == "add") {
    player->addMediaStream(command[1], command[2]);
  }
  else if (command[0] == "info") {
    player->infoStream(command[1]);
  }
  return 0;
}

int main() {
  std::string line;
  std::string token;
  Player      *player = new Player();

  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);
    std::vector<std::string> command;
    while(std::getline(iss, token, ';')) {
	    command.push_back(token);
    }
    if (command.size() > 0) {
      if (execCommand(player, command) == -1) {
        return 0;
      }
    }
    command.clear();
  }
  return 0;
}
