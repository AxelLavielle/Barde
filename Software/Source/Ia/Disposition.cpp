#include "Disposition.hh"

Disposition::Disposition(){
  _markov.push_back(std::make_pair('A', '3'));
  _markov.push_back(std::make_pair('A', '3'));
  _markov.push_back(std::make_pair('A', '3'));
  _markov.push_back(std::make_pair('A', '3'));
  _markov.push_back(std::make_pair('D', '3'));
  _markov.push_back(std::make_pair('D', '3'));
  _markov.push_back(std::make_pair('A', '3'));
  _markov.push_back(std::make_pair('A', '3'));
  _markov.push_back(std::make_pair('E', '3'));
  _markov.push_back(std::make_pair('D', '3'));
  _markov.push_back(std::make_pair('A', '3'));
  _markov.push_back(std::make_pair('E', '3'));
}

Disposition::~Disposition(){}

void Disposition::createMidi(){

}
