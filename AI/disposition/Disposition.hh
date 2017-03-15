#include <vector>
#include <utility>

class Disposition {

  private:
    std::vector<std::pair<char, char> > _markov;

  public:
    Disposition();
    ~Disposition();

  private:
    void createMidi();

};
