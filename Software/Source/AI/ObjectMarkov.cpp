#include "ObjectMarkov.hh"

ObjectMarkov::ObjectMarkov(const StyleSettings &settings, const unsigned int nbNote)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  setRootJsonFromStyle(settings);
  _luaMarkovFunction = SOURCEMARKOV;
  _luaMarkovFunction += "markov.lua";
  _nbNote = nbNote;
  _seed = static_cast<unsigned int>(std::time(nullptr));
}

ObjectMarkov::ObjectMarkov(const StyleSettings &settings, const unsigned int nbNote, const unsigned int seed)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  setRootJsonFromStyle(settings);
  _luaMarkovFunction = SOURCEMARKOV;
  _luaMarkovFunction += "markov.lua";
  _nbNote = nbNote;
  _seed = seed;
}

ObjectMarkov::ObjectMarkov(const StyleSettings &settings, const std::string &luaMarkovFunction, unsigned int nbNote, const unsigned int seed)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  setRootJsonFromStyle(settings);
  _luaMarkovFunction = luaMarkovFunction;
  _nbNote = nbNote;
  _seed = seed;
}

ObjectMarkov::ObjectMarkov(const std::string &styleJson, const unsigned int nbNote)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  setRootJsonFromFile(styleJson);
  _luaMarkovFunction = SOURCEMARKOV;
  _luaMarkovFunction += "markov.lua";

  _nbNote = nbNote;
  _seed = static_cast<unsigned int>(std::time(nullptr));
}

ObjectMarkov::ObjectMarkov(const std::string &styleJson, const unsigned int nbNote, const unsigned int seed)
{
  _L = luaL_newstate();
  luaL_openlibs(_L);
  setRootJsonFromFile(styleJson);
  _luaMarkovFunction = SOURCEMARKOV;
  _luaMarkovFunction += "markov.lua";

  _nbNote = nbNote;
  _seed = seed;
}

ObjectMarkov::ObjectMarkov(const std::string &styleJson, const std::string &luaMarkovFunction, const unsigned int nbNote, const unsigned int seed)
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
		//std::cerr << "rootJson is null !!" << std::endl;
		return;
	}
	Json::Reader reader;
	luaL_dofile(_L, _luaMarkovFunction.c_str());
	lua_pcall(_L, 0, 0, 0);
	Json::Value jsonNote = _rootJson["note"];
	lua_newtable(_L);
	for (Json::Value::iterator it = jsonNote.begin(); it != jsonNote.end(); ++it)
	{
		lua_newtable(_L);
		for (Json::Value::iterator it2 = jsonNote[it.key().asString()].begin(); it2 != jsonNote[it.key().asString()].end(); ++it2)
		{
			lua_pushinteger(_L, (*it2).asInt());
			lua_setfield(_L, -2, it2.key().asString().c_str());
		}
		lua_setfield(_L, -2, it.key().asString().c_str());
	}
	lua_setglobal(_L, "note");

	Json::Value jsonScale = _rootJson["scale"];
	lua_newtable(_L);
	for (Json::Value::iterator it = jsonScale.begin(); it != jsonScale.end(); ++it)
	{
		lua_newtable(_L);
		for (Json::Value::iterator it2 = jsonScale[it.key().asString()].begin(); it2 != jsonScale[it.key().asString()].end(); ++it2)
		{
			lua_pushinteger(_L, (*it2).asInt());
			lua_setfield(_L, -2, it2.key().asString().c_str());
		}
		lua_setfield(_L, -2, it.key().asString().c_str());
	}
	lua_setglobal(_L, "scale");

	lua_getglobal(_L, "generateNoteWithGlobal");
	lua_pushnumber(_L, _nbNote);
	lua_pushstring(_L, SOURCEMARKOV);

	lua_pcall(_L, 2, 1, 0);
	if (!lua_isnil(_L, -1))
	{
		if (reader.parse(lua_tostring(_L, -1), _response, false))
		{
			//std::vector<std::pair<char, char> > v = ObjectMarkov::getVectorFromJson(test);
			//StyleSettings style =  ObjectMarkov::getStyleFromJson(_rootJson["note"]);
		}
		lua_pop(_L, 1);
	}
	else
	{
		//std::cerr << "nothing" << std::endl;
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

  vector.push_back(std::pair<char, char>(static_cast<char>(atoi(tmp["note"].asString().c_str())), static_cast<char>(atoi(tmp["scale"].asString().c_str()))));
 while (tmp.isMember("next"))
   {
     tmp = tmp["next"];
     vector.push_back(std::pair<char, char>(static_cast<char>(atoi(tmp["note"].asString().c_str())), static_cast<char>(atoi(tmp["scale"].asString().c_str()))));
}
  return vector;
}

StyleSettings ObjectMarkov::getStyleFromJson()
{
  StyleSettings style;

  Json::Value json = _rootJson["note"];

  for (Json::Value::iterator it = json["begin"].begin(); it != json["begin"].end(); ++it)
    style.addNote(static_cast<char>(std::stoi(it.key().asString())), (*it).asInt());
  for (Json::Value::iterator it = json.begin(); it != json.end(); ++it)
  {
    if (it.key().asString() != "begin")
    {
      for (Json::Value::iterator it2 = json[it.key().asString()].begin(); it2 != json[it.key().asString()].end(); ++it2)
      {
        style.addNoteFromNote(static_cast<char>(std::stoi(it.key().asString())), static_cast<char>(std::stoi(it2.key().asString())), (*it2).asInt());
      }
    }
  }
  return style;
}

void ObjectMarkov::setRootJsonFromFile(const std::string &styleJson)
{
  Json::Reader reader;
  std::ifstream style(styleJson.c_str(), std::ifstream::binary);
  bool parsingSuccessful = reader.parse(style, _rootJson, false);
  if (!parsingSuccessful)
  {
    // report to the user the failure and their locations in the document.
    //std::cerr  << "Failed to parse configuration\n"
      //         << reader.getFormattedErrorMessages();
  }
}

void ObjectMarkov::setRootJsonFromStyle(const StyleSettings &settings)
{
  std::map<char, std::pair<int, std::map<char, int> > > style = settings.getParam();

  _rootJson["scale"]["begin"]["5"] = 100;
  _rootJson["scale"]["5"]["5"] = 100;
  for (std::map<char, std::pair<int, std::map<char, int> > >::iterator itMap1 = style.begin(); itMap1 != style.end(); ++itMap1)
  {
    //_rootJson["note"].append(std::string(1, itMap1->first));
    _rootJson["note"]["begin"][std::to_string(itMap1->first)] = (itMap1->second).first;
    for (std::map<char, int>::iterator itMap2 = ((itMap1->second).second).begin(); itMap2 != ((itMap1->second).second).end(); ++itMap2)
      _rootJson["note"][std::to_string(itMap1->first)][std::to_string(itMap2->first)] = itMap2->second;
  }
}
