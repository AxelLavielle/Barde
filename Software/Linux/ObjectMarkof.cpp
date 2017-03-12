#include "ObjectMarkof.hh"
#include <iostream>
#include <fstream>

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
lua_State* L;

ObjectMarkof::ObjectMarkof()
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
    std::cout << "sits work " << lua_tostring(L,-1) << std::endl;
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

ObjectMarkof::~ObjectMarkof()
{
  lua_close(L);
}
