/*
  ==============================================================================

    FileManager.h
    Created: 13 Mar 2017 2:04:12pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef FILEMANAGER_HH_INCLUDED
#define FILEMANAGER_HH_INCLUDED

#define UNICODE

#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>

#ifdef __linux__
	#include <unistd.h>
	#include <sys/types.h>
	#include <dirent.h>
#else
	#include <Windows.h>
	#include <direct.h>
#endif // __linux__

class FileManager
{
public:
	static void getFilesList(const std::wstring &filePath, const std::wstring &extension, std::vector<std::wstring> & returnFileName);
	static std::string getFileName(const std::wstring & filePath);
	static std::wstring getCurrentDirectory();

private:

};


#endif  // FILEMANAGER_HH_INCLUDED
