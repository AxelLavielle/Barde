//#ifndef ObjectMarkov_HH_INCLUDED
//# define ObjectMarkov_HH_INCLUDED
//
//# include <cstdio>
//# include <fstream>
//# include <iostream>
//# include <cstdlib>
//# include <vector>
//# include "json/json.h"
//# include "StyleSettings.hh"
//
//extern "C" {
//    #include "lua.h"
//    #include "lualib.h"
//    #include "lauxlib.h"
//}
//
//class ObjectMarkov
//{
//public:
//  ObjectMarkov(std::string styleJson);
//  ObjectMarkov(std::string styleJson, std::string luaMarkovFunction);
//  void callLuaMarkov();
//  ~ObjectMarkov();
//  std::vector<std::pair<char, char> >  getVectorFromJson();
//  StyleSettings getStyleFromJson();
//private:
//  std::string _styleJson;
//  lua_State* _L;
//  std::string _luaMarkovFunction;
//  Json::Value _jsonNote;
//  Json::Value _response;
//  Json::Value _rootJson;
//};
//
//#endif /* ObjectMarkov_HH_INCLUDED */
