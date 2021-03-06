/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   people_json;
    const int            people_jsonSize = 204;

    extern const char*   blues_json;
    const int            blues_jsonSize = 299;

    extern const char*   dkjson_lua;
    const int            dkjson_luaSize = 22416;

    extern const char*   markov_lua;
    const int            markov_luaSize = 2345;

    extern const char*   back_png;
    const int            back_pngSize = 140671;

    extern const char*   logo_png;
    const int            logo_pngSize = 271238;

    extern const char*   Dark;
    const int            DarkSize = 34;

    extern const char*   DoxyBarde;
    const int            DoxyBardeSize = 107460;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 8;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}
