#ifndef ObjectMarkov_HH_INCLUDED
# define ObjectMarkov_HH_INCLUDED

#include "json/json.h"
# include <cstdio>
# include <fstream>
#include "StyleSettings.hh"

class ObjectMarkov
{
public:
  ObjectMarkov();
  ~ObjectMarkov();
  std::vector<std::pair<char, char> >  getVectorFromJson(Json::Value);
  StyleSettings getStyleFromJson(Json::Value);
};

#endif /* ObjectMarkov_HH_INCLUDED */
