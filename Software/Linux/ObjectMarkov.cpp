#include "ObjectMarkov.hh"
#include <iostream>
#include <fstream>
#include <cstdlib>

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
lua_State* L;

ObjectMarkov::ObjectMarkov()
{
  L = luaL_newstate();
  luaL_openlibs(L);
  std::cout << L << std::endl;

  luaL_dofile(L, "markov.lua");
  Json::Value root;
  Json::Reader reader;
  std::ifstream style("blues.json", std::ifstream::binary);
  bool parsingSuccessful = reader.parse(style, root, false);
  if (!parsingSuccessful)
  {
    // report to the user the failure and their locations in the document.
    std::cout  << "Failed to parse configuration\n"
               << reader.getFormattedErrorMessages();
    return;
  }
  ObjectMarkov::getStyleFromJson(root["note"]);
lua_getglobal(L, "generateNote");
  Json::StyledWriter writer;
  std::string output = writer.write( root["scale"]);
  lua_pushstring(L, output.c_str());
  //std::cout << "scale " << output.c_str() << std::endl;
  output = writer.write( root["note"]);
  //std::cout << "note " << output.c_str() << std::endl;
  lua_pushstring(L, output.c_str());
  lua_pushnumber(L, 10);
  lua_call(L,3,1);
  if (!lua_isnil(L, -1))
  {
    std::cout << "sits work " << std::endl;
    Json::Value test;
    if (reader.parse(lua_tostring(L,-1), test, false))
    {
      std::vector<std::pair<char, char> > v = ObjectMarkov::getVectorFromJson(test);
      int	i = -1;
      while (++i != v.size())
        std::cout << v[i].first << std::endl;
    }
    lua_pop(L,1);
  }
  else
  {
    std::cout << "nothin" << std::endl;
  }
  //std::cout << root << std::endl;
  //std::cout << result << std::endl;
  /*lua_getglobal(L, "generateNote");
  lua_pushstring(L, "10");
  lua_pushstring(L, "10");
  lua_pushnumber(L, 10);
  lua_call(L, 3, 1);*/
}

ObjectMarkov::~ObjectMarkov()
{
  lua_close(L);
}

std::vector<std::pair<char, char> >  ObjectMarkov::getVectorFromJson(Json::Value root)
{
  std::vector<std::pair<char, char> >  vector;
  bool  good = true;

  while (good)
  {
    vector.push_back(std::pair<char, char>(root["note"].asString().c_str()[0], root["scale"].asString().c_str()[0]));
    if (root.isMember("next"))
      root = root["next"];
    else
      good = false;
  }
  return vector;
}

StyleSettings ObjectMarkov::getStyleFromJson(Json::Value json)
{
  StyleSettings style;

  for (Json::Value::iterator it = json["begin"].begin(); it != json["begin"].end(); ++it)
    style.addNote(it.key().asString().c_str()[0], (*it).asInt());
  for (Json::Value::iterator it = json.begin(); it != json.end(); ++it)
  {
    if (it.key().asString() != "begin")
    {
      for (Json::Value::iterator it2 = json[it.key().asString()].begin(); it2 != json[it.key().asString()].end(); ++it2)
      {
        style.addNoteFromNote(it.key().asString().c_str()[0], it2.key().asString().c_str()[0], (*it2).asInt());
      }
    }
  }
  return style;
}
