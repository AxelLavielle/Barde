/*
  ==============================================================================

    FileManager.h
    Created: 13 Mar 2017 2:04:12pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef FILEMANAGER_HH_INCLUDED
#define FILEMANAGER_HH_INCLUDED

#include <Windows.h>
#include <vector>

class FileManager
{
public:
	static void getFilesList(std::string filePath, std::string extension, std::vector<std::string> & returnFileName);
	static std::string getFileName(const std::string & filePath);

private:

};


#endif  // FILEMANAGER_HH_INCLUDED
