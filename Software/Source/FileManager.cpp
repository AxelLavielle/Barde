	/*
  ==============================================================================

    FileManager.cpp
    Created: 13 Mar 2017 2:04:12pm
    Author:  Anthony

  ==============================================================================
*/

#include "FileManager.hh"

std::string FileManager::getCurrentDirectory()
{
	char buff[FILENAME_MAX];
#ifdef __linux__
	getcwd(buff, FILENAME_MAX);
#else
	_getcwd(buff, FILENAME_MAX);
#endif // __linux__
	return std::string(buff);
}

void FileManager::getFilesList(const std::string &filePath, const std::string &extension, std::vector<std::string> & returnFileName)
{
#ifdef __linux__
	DIR *directory;
	struct dirent *dirp;
	if ((directory = opendir(filePath.c_str())) == NULL)
	{
		std::cerr << "ERROR : Can not open given directory : " << filePath << std::endl;
	}
	while ((dirp = readdir(directory)) != NULL)
	{
		if (std::string(dirp->d_name).find(extension) != std::string::npos)
			returnFileName.push_back(filePath + std::string(dirp->d_name));
	}
	closedir(directory);
#else
	WIN32_FIND_DATA fileInfo;
	HANDLE hFind;
	std::string  fullPath = filePath + "*" + extension;
	hFind = FindFirstFile(fullPath.c_str(), &fileInfo);
	if (hFind != INVALID_HANDLE_VALUE) {
		returnFileName.push_back(filePath + fileInfo.cFileName);
		while (FindNextFile(hFind, &fileInfo) != 0) {
			returnFileName.push_back(filePath + fileInfo.cFileName);
		}
	}
#endif // __linux__
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
