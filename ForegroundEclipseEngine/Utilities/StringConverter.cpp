#include <vector>
#include <iostream>
#include "StringConverter.h"
const std::string StringConverter::TrimStringAfterWord(std::string curString, char word)
{
	std::vector<std::string> tempStrArray;
	size_t prev = 0, cur;
	cur = curString.find('\\');
	while (cur != std::string::npos)
	{
		std::string sub_str = curString.substr(prev, cur - prev); // 문자열 split
		tempStrArray.push_back(sub_str);
		prev = cur + 1;
		cur = curString.find('\\', prev);
	}
	std::string finalPath;
	for (int i = 0; i < tempStrArray.size(); i++) {
		finalPath += tempStrArray[i] + "\\";
	}

    return finalPath;
}

const std::string StringConverter::TCHARToString(const TCHAR* ptsz)
{
	int len = wcslen((wchar_t*)ptsz);

	char* psz = new char[2 * len + 1];

	wcstombs(psz, (wchar_t*)ptsz, 2 * len + 1);
	std::string s = psz;

	delete[] psz;

	return s;
}

const std::string StringConverter::GetProjectName(std::string GameRoot)
{
	std::vector<std::string> tempStrArray;
	size_t prev = 0, cur;
	cur = GameRoot.find('\\');
	while (cur != std::string::npos)
	{
		std::string sub_str = GameRoot.substr(prev, cur - prev); // 문자열 split
		tempStrArray.push_back(sub_str);
		prev = cur + 1;
		cur = GameRoot.find('\\', prev);
	}
	return tempStrArray[tempStrArray.size() - 1];
}
