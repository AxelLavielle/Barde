#ifndef ObjectMarkov_HH_INCLUDED
# define ObjectMarkov_HH_INCLUDED

# include <cstdio>
# include <fstream>
# include <iostream>
# include <cstdlib>
# include <vector>
# include <ctime>
# include "json/json.h"
# include "StyleSettings.hh"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

class ObjectMarkov
{
public:
  ObjectMarkov(const StyleSettings &settings, unsigned int nbNote);
  ObjectMarkov(const StyleSettings &settings, unsigned int nbNote, unsigned int seed);
  ObjectMarkov(const StyleSettings &settings, std::string luaMarkovFunction, unsigned int nbNote, unsigned int seed);
  ObjectMarkov(std::string styleJson, unsigned int nbNote);
  ObjectMarkov(std::string styleJson, unsigned int nbNote, unsigned int seed);
  ObjectMarkov(std::string styleJson, std::string luaMarkovFunction, unsigned int nbNote, unsigned int seed);
  ~ObjectMarkov();
  void                                  callLua();
  std::vector<std::pair<char, char> >   getVectorFromJson();
  StyleSettings                         getStyleFromJson();
  void                                  setRootJsonFromFile(std::string styleJson);
  void                                  setRootJsonFromStyle(const StyleSettings &settings);
private:
  std::string                           _styleJson;
  lua_State*                            _L;
  std::string                           _luaMarkovFunction;
  Json::Value                           _jsonNote;
  Json::Value                           _response;
  Json::Value                           _rootJson;
  unsigned int                          _seed;
  unsigned int                          _nbNote;
};

#endif /* ObjectMarkov_HH_INCLUDED */
