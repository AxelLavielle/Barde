/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== people.json ==================
static const unsigned char temp_binary_data_0[] =
"{\n"
"    \"encoding\" : \"UTF-8\",\n"
"    \"toto\" : \"titi\",\n"
"    \"encodi\" : \"UTF-7\",\n"
"    \"plug-ins\" : [\n"
"        \"python\",\n"
"        \"c++\",\n"
"        \"ruby\"\n"
"        ],\n"
"    \"indent\" : { \"length\" : 3, \"use_space\": true }\n"
"}\n";

const char* people_json = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x441eb498:  numBytes = 204; return people_json;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "people_json"
};

const char* originalFilenames[] =
{
    "people.json"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
