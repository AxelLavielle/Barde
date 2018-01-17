/*
  ==============================================================================

    FileManager.h
    Created: 13 Mar 2017 2:04:12pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef FILEMANAGER_HH_INCLUDED
#define FILEMANAGER_HH_INCLUDED

#include <vector>
#include <string>
#include <iostream>

#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef __linux__
	#include <unistd.h>
	#include <sys/types.h>
	#include <dirent.h>
#else
	#include <Windows.h>
	#include <direct.h>
#endif

class FileManager
{
public:
	static void getFilesList(const std::string &filePath, const std::string &extension, std::vector<std::string> & returnFileName);
	static std::string getFileName(const std::string & filePath);
	static std::string getCurrentDirectory();

private:

};


#endif  // FILEMANAGER_HH_INCLUDED
