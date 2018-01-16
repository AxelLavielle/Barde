/*
  ==============================================================================

    FileManager.cpp
    Created: 13 Mar 2017 2:04:12pm
    Author:  Anthony

  ==============================================================================
*/

#include "FileManager.hh"

void FileManager::getFilesList(std::string filePath, std::string extension, std::vector<std::string> & returnFileName)
{
	WIN32_FIND_DATA fileInfo;
	HANDLE hFind;
	std::string  fullPath = filePath + extension;
	hFind = FindFirstFile(fullPath.c_str(), &fileInfo);
	if (hFind != INVALID_HANDLE_VALUE) {
		returnFileName.push_back(filePath + fileInfo.cFileName);
		while (FindNextFile(hFind, &fileInfo) != 0) {
			returnFileName.push_back(filePath + fileInfo.cFileName);
		}
	}
}

std::string FileManager::getFileName(const std::string & filePath)
{
	size_t len;
	size_t tmpPos;

	len = filePath.size() - 1;

	while (len > 0 && filePath[len] != '.')
		len--;
	tmpPos = len;
	while (len > 0 && filePath[len] != '/' && filePath[len] != '\\')
		len--;
	len++;
	return filePath.substr(len, (filePath.size() - len) - (filePath.size() - tmpPos));
}
