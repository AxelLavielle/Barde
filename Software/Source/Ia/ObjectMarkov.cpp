#include "ObjectMarkov.hh"

ObjectMarkov::ObjectMarkov(std::string styleJson, unsigned int nbNote)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  _styleJson = styleJson;
  _luaMarkovFunction = "markov.lua";
  _nbNote = nbNote;
  _seed = std::time(nullptr);
}

ObjectMarkov::ObjectMarkov(std::string styleJson, unsigned int nbNote, unsigned int seed)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  _styleJson = styleJson;
  _luaMarkovFunction = "markov.lua";
  _nbNote = nbNote;
  _seed = seed;
}

ObjectMarkov::ObjectMarkov(std::string styleJson, std::string luaMarkovFunction, unsigned int nbNote, unsigned int seed)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  _styleJson = styleJson;
  _luaMarkovFunction = luaMarkovFunction;
  _nbNote = nbNote;
  _seed = seed;
}

void ObjectMarkov::callLuaMarkov()
{
  luaL_dofile(_L, _luaMarkovFunction.c_str());
  Json::Reader reader;
  std::ifstream style(_styleJson.c_str(), std::ifstream::binary);
  bool parsingSuccessful = reader.parse(style, _rootJson, false);

  if (!parsingSuccessful)
  {
    // report to the user the failure and their locations in the document.
    std::cout  << "Failed to parse configuration\n"
               << reader.getFormattedErrorMessages();
    return;
  }
  //ObjectMarkov::getStyleFromJson(_rootJson["note"]);

  lua_getglobal(_L, "generateNote");
  Json::StyledWriter writer;
  std::string output = writer.write(_rootJson["scale"]);
  lua_pushstring(_L, output.c_str());

  output = writer.write(_rootJson["note"]);
  std::cout << _rootJson["note"] << std::endl;
  lua_pushstring(_L, output.c_str());
  lua_pushnumber(_L, 15);
  lua_pushnumber(_L, _seed);
  lua_call(_L,4,1);
  if (!lua_isnil(_L, -1))
  {
    if (reader.parse(lua_tostring(_L,-1), _response, false))
    {
      //std::vector<std::pair<char, char> > v = ObjectMarkov::getVectorFromJson(test);
      //StyleSettings style =  ObjectMarkov::getStyleFromJson(_rootJson["note"]);
    }
    lua_pop(_L,1);
  }
  else
  {
    std::cout << "nothing" << std::endl;
  }

}

ObjectMarkov::~ObjectMarkov()
{
  lua_close(_L);
}

std::vector<std::pair<char, char> >  ObjectMarkov::getVectorFromJson()
{
  Json::Value tmp = _response;
  std::vector<std::pair<char, char> >  vector;

  vector.push_back(std::pair<char, char>(tmp["note"].asString().c_str()[0], tmp["scale"].asString().c_str()[0]));

 while (tmp.isMember("next"))
   {
     tmp = tmp["next"];
     vector.push_back(std::pair<char, char>(tmp["note"].asString().c_str()[0], tmp["scale"].asString().c_str()[0]));
}
  return vector;
}

StyleSettings ObjectMarkov::getStyleFromJson()
{
  StyleSettings style;

  Json::Value json = _rootJson["note"];

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
