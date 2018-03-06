	/*
  ==============================================================================

    FileManager.cpp
    Created: 13 Mar 2017 2:04:12pm
    Author:  Anthony

  ==============================================================================
*/

#include "FileManager.hh"

std::wstring FileManager::getCurrentDirectory()
{
	wchar_t buff[FILENAME_MAX];
#ifdef __linux__
	getcwd(buff, FILENAME_MAX);
#else
	_wgetcwd(buff, FILENAME_MAX);
#endif // __linux__
	return std::wstring(buff);
}

void FileManager::getFilesList(const std::wstring &filePath, const std::wstring &extension, std::vector<std::wstring> & returnFileName)
{
#ifdef __linux__
	DIR *directory;
	struct dirent *dirp;
	if ((directory = opendir(filePath.c_str())) == NULL)
	{
		std::cerr << "ERROR : Can not open given directory : " << filePath << std::endl;
		return;
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
	std::wstring  fullPath = filePath;
	fullPath += '*';
	fullPath += extension;
	hFind = FindFirstFile(fullPath.c_str(), &fileInfo);
	if (hFind != INVALID_HANDLE_VALUE) {
		returnFileName.push_back(filePath + fileInfo.cFileName);
		while (FindNextFile(hFind, &fileInfo) != 0) {
			returnFileName.push_back(filePath + fileInfo.cFileName);
		}
	}
#endif // __linux__
}

std::string ws2s(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	return r;
}

std::string FileManager::getFileName(const std::wstring & filePath)
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
	return ws2s(filePath.substr(len, (filePath.size() - len) - (filePath.size() - tmpPos)));
}
