#include "ObjectMarkov.hh"

ObjectMarkov::ObjectMarkov(const StyleSettings &settings, unsigned int nbNote)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  setRootJsonFromStyle(settings);
  #ifdef _WIN64
  _luaMarkovFunction = "../Source/markovSource/markov.lua";
  #else
  _luaMarkovFunction = "../../Source/markovSource/markov.lua";  _nbNote = nbNote;
  #endif

  _seed = std::time(nullptr);
}

ObjectMarkov::ObjectMarkov(const StyleSettings &settings, unsigned int nbNote, unsigned int seed)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  setRootJsonFromStyle(settings);
  #ifdef _WIN64
  _luaMarkovFunction = "../Source/markovSource/markov.lua";
  #else
  _luaMarkovFunction = "../../Source/markovSource/markov.lua";  _nbNote = nbNote;
  #endif

  _seed = seed;
}

ObjectMarkov::ObjectMarkov(const StyleSettings &settings, std::string luaMarkovFunction, unsigned int nbNote, unsigned int seed)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  setRootJsonFromStyle(settings);
  _luaMarkovFunction = luaMarkovFunction;
  _nbNote = nbNote;
  _seed = seed;
}

ObjectMarkov::ObjectMarkov(std::string styleJson, unsigned int nbNote)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  setRootJsonFromFile(styleJson);
  #ifdef _WIN64
  _luaMarkovFunction = "../Source/markovSource/markov.lua";
  #else
  _luaMarkovFunction = "../../Source/markovSource/markov.lua";
  #endif

  _nbNote = nbNote;
  _seed = std::time(nullptr);
}

ObjectMarkov::ObjectMarkov(std::string styleJson, unsigned int nbNote, unsigned int seed)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  setRootJsonFromFile(styleJson);
  #ifdef _WIN64
  _luaMarkovFunction = "../Source/markovSource/markov.lua";
  #else
  _luaMarkovFunction = "../../Source/markovSource/markov.lua";
  #endif

  _nbNote = nbNote;
  _seed = seed;
}

ObjectMarkov::ObjectMarkov(std::string styleJson, std::string luaMarkovFunction, unsigned int nbNote, unsigned int seed)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  setRootJsonFromFile(styleJson);
  _luaMarkovFunction = luaMarkovFunction;
  _nbNote = nbNote;
  _seed = seed;
}

void ObjectMarkov::callLua()
{
  if (!_rootJson)
  {
    std::cout << "rootJson is null !!" << std::endl;
    return;
  }
  Json::Reader reader;
  luaL_dofile(_L, _luaMarkovFunction.c_str());
  //ObjectMarkov::getStyleFromJson(_rootJson["note"]);

  lua_getglobal(_L, "generateNote");
  Json::StyledWriter writer;
  std::string output = writer.write(_rootJson["scale"]);
  lua_pushstring(_L, output.c_str());

  output = writer.write(_rootJson["note"]);
  lua_pushstring(_L, output.c_str());
  lua_pushnumber(_L, _nbNote);
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

  vector.push_back(std::pair<char, char>(atoi(tmp["note"].asString().c_str()), atoi(tmp["scale"].asString().c_str())));

 while (tmp.isMember("next"))
   {
     tmp = tmp["next"];
     vector.push_back(std::pair<char, char>(atoi(tmp["note"].asString().c_str()), atoi(tmp["scale"].asString().c_str())));
}
  return vector;
}

StyleSettings ObjectMarkov::getStyleFromJson()
{
  StyleSettings style;

  Json::Value json = _rootJson["note"];

  for (Json::Value::iterator it = json["begin"].begin(); it != json["begin"].end(); ++it)
    style.addNote(atoi(it.key().asString().c_str()), (*it).asInt());
  for (Json::Value::iterator it = json.begin(); it != json.end(); ++it)
  {
    if (it.key().asString() != "begin")
    {
      for (Json::Value::iterator it2 = json[it.key().asString()].begin(); it2 != json[it.key().asString()].end(); ++it2)
      {
        style.addNoteFromNote(atoi(it.key().asString().c_str()), atoi(it2.key().asString().c_str()), (*it2).asInt());
      }
    }
  }
  return style;
}

void ObjectMarkov::setRootJsonFromFile(std::string styleJson)
{
  Json::Reader reader;
  std::ifstream style(styleJson.c_str(), std::ifstream::binary);
  bool parsingSuccessful = reader.parse(style, _rootJson, false);
  if (!parsingSuccessful)
  {
    // report to the user the failure and their locations in the document.
    std::cout  << "Failed to parse configuration\n"
               << reader.getFormattedErrorMessages();
  }
}

void ObjectMarkov::setRootJsonFromStyle(const StyleSettings &settings)
{
  std::map<char, std::pair<int, std::map<char, int> > > style = settings.getParam();

  _rootJson["scale"]["begin"]["3"] = 100;
  _rootJson["scale"]["3"]["3"] = 100;
  for (std::map<char, std::pair<int, std::map<char, int> > >::iterator itMap1 = style.begin(); itMap1 != style.end(); ++itMap1)
  {
    //_rootJson["note"].append(std::string(1, itMap1->first));
    _rootJson["note"]["begin"][std::string(1, itMap1->first)] = (itMap1->second).first;
    for (std::map<char, int>::iterator itMap2 = ((itMap1->second).second).begin(); itMap2 != ((itMap1->second).second).end(); ++itMap2)
      _rootJson["note"][std::string(1, itMap1->first)][std::string(1, itMap2->first)] = itMap2->second;
  }
}
