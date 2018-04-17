	/*
  ==============================================================================

    FileManager.cpp
    Created: 13 Mar 2017 2:04:12pm
    Author:  Anthony

  ==============================================================================
*/

#include "FileManager.hh"

std::wstring _s2ws(const std::string& s)
{
	int slength = (int)s.length() + 1;
	#ifdef __linux__
	wchar_t* buf = new wchar_t[slength];
	mbtowc(buf, s.c_str(), slength);
	#else
	int len;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	#endif
	std::wstring r(buf);
	delete[] buf;
	return r;
}

std::string _ws2s(const std::wstring& s)
{
	int slength = (int)s.length() + 1;
	#ifdef __linux__
	std::string r;
	char* buf = new char[slength];
	for (unsigned int i; i < s.length(); i++)
	  {
	    buf[wctomb(buf, s.c_str()[i])] = 0;
	    r = r + buf;
	  }
	#else
	int len;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	#endif
	delete[] buf;
	return r;
}

std::wstring FileManager::getCurrentDirectory()
{
#ifdef __linux__
	char buff[FILENAME_MAX];
	getcwd(buff, FILENAME_MAX);
	return _s2ws(std::string(buff));
#else
	wchar_t buff[FILENAME_MAX];
	_wgetcwd(buff, FILENAME_MAX);
	return std::wstring(buff);
#endif // __linux__
}

void FileManager::getFilesList(const std::wstring &filePath, const std::wstring &extension, std::vector<std::wstring> & returnFileName)
{
#ifdef __linux__
	DIR *directory;
	struct dirent *dirp;
	if ((directory = opendir(_ws2s(filePath).c_str())) == NULL)
	{
		std::wcerr << "ERROR : Can not open given directory : " << filePath << std::endl;
		return;
	}
	while ((dirp = readdir(directory)) != NULL)
	{
	  if (std::string(dirp->d_name).find(_ws2s(extension)) != std::string::npos)
	    returnFileName.push_back(_s2ws(_ws2s(filePath) + std::string(dirp->d_name)));
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
	return _ws2s(filePath.substr(len, (filePath.size() - len) - (filePath.size() - tmpPos)));
}
