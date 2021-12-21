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
DataArray<DataString> StringConverter::split(const DataString& s, char delim)
{
	DataArray<DataString> elems;

	const char* cstr = s.c_str();
	unsigned int strLength = (unsigned int)s.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end <= strLength) {
		while (end <= strLength) {
			if (cstr[end] == delim) {
				break;
			}
			end++;
		}

		elems.push_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}

DataString StringConverter::getFilePath(const DataString& fileName)
{
	const char* cstr = fileName.c_str();
	unsigned int strLength = (unsigned int)fileName.length();
	unsigned int end = strLength - 1;

	while (end != 0) {
		if (cstr[end] == '/') {
			break;
		}
		end--;
	}

	if (end == 0) {
		return fileName;
	}
	else {
		unsigned int start = 0;
		end = end + 1;
		return fileName.substr(start, end - start);
	}
}

bool StringConverter::loadTextFileWithIncludes(DataString& output, const DataString& fileName,
	const DataString& includeKeyword)
{
	std::ifstream file;
	file.open(fileName.c_str());

	DataString filePath = getFilePath(fileName);
	std::stringstream ss;
	DataString line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);

			if (line.find(includeKeyword) == DataString::npos) {
				ss << line << "\n";
			}
			else {
				DataString includeFileName = StringConverter::split(line, ' ')[1];
				includeFileName =
					includeFileName.substr(1, includeFileName.length() - 2);

				DataString toAppend;
				loadTextFileWithIncludes(toAppend, filePath + includeFileName,
					includeKeyword);
				ss << toAppend << "\n";
			}
		}
	}
	else {
		DEBUG_LOG(LOG_TYPE_IO, LOG_ERROR, "Unable to load shader: %s",
			fileName.c_str());
		return false;
	}

	output = ss.str();
	return true;
}