#ifndef ObjectMarkov_HH_INCLUDED
# define ObjectMarkov_HH_INCLUDED

/*!
* \file ObjectMarkov.hh
* \brief This file containe the class doing link between the LUA code and CPP code
*/

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

/*! \Class ObjectMarkov
* \brief Doing link between LUA code and CPP code
*/

class ObjectMarkov
{
public:
	/*!
	* \brief initialize information file to call
	* \param settings : styleSettings Class
	* \param nbNote : number of note
	*/
  ObjectMarkov(const StyleSettings &settings, const unsigned int nbNote);
  /*!
  * \brief initialize information file to call
  * \param settings : styleSettings Class
  * \param nbNote : number of note
  * \param seed : starting value
  */
  ObjectMarkov(const StyleSettings &settings, const unsigned int nbNote, const unsigned int seed);
  /*!
  * \brief initialize information file to call
  * \param settings : styleSettings Class
  * \param luaMarkovFunction : name of the function to call from the lua file
  * \param nbNote : number of note
  */
  ObjectMarkov(const StyleSettings &settings, const std::string &luaMarkovFunction, const unsigned int nbNote, unsigned int seed);
  /*!
  * \brief initialize information file to call
  * \param styleJson : styleJson file as a String
  * \param nbNote : number of note
  */
  ObjectMarkov(const std::string &styleJson, const unsigned int nbNote);
  /*!
  * \brief initialize information file to call
  * \param styleJson : styleJson file as a String
  * \param nbNote : number of note
  * \param seed : starting value
  */
  ObjectMarkov(const std::string &styleJson, const unsigned int nbNote, const unsigned int seed);
  /*!
  * \brief initialize information file to call
  * \param styleJson : styleJson file as a String
  * \param luaMarkovFunction : name of the function to call from the lua file
  * \param nbNote : number of note
  * \param seed : starting value
  */
  ObjectMarkov(const std::string &styleJson, const std::string &luaMarkovFunction, const unsigned int nbNote, const unsigned int seed);
  /*!
  * \ brief Destructor
  */
  ~ObjectMarkov();
  void                                  callLua();
  std::vector<std::pair<char, char> >   getVectorFromJson();
  StyleSettings                         getStyleFromJson();
  void                                  setRootJsonFromFile(const std::string &styleJson);
  void                                  setRootJsonFromStyle(const StyleSettings &settings);
private:
  std::string                           _styleJson; /*!< style file as a String*/
  lua_State*                            _L; /*!< lua state*/
  std::string                           _luaMarkovFunction; /*!> the name of the lua function to call from the lua file*/
  Json::Value                           _jsonNote;
  Json::Value                           _response;
  Json::Value                           _rootJson;
  unsigned int                          _seed; /*!> the starting value*/
  unsigned int                          _nbNote; /*!> number of note*/
};

#endif /* ObjectMarkov_HH_INCLUDED */
