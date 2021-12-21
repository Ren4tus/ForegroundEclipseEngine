#pragma once
#include "../pch.h"
#include <windows.h>


class StringConverter {
private:
	StringConverter() {}
	static StringConverter* s_pInstance;

public:
	~StringConverter() {}
	static StringConverter* Instance() {
		if (s_pInstance == NULL) {
			s_pInstance = new StringConverter();
		}
		return s_pInstance;
	}
	static const std::string TrimStringAfterWord(std::string curString, char word);
	static const std::string TCHARToString(const TCHAR* ptsz);
	static const std::string GetProjectName(std::string GameRoot);

	template<typename T>
	static inline DataString toString(T val)
	{
		std::ostringstream convert;
		convert << val;
		return convert.str();
	}

	static DataArray<DataString> split(const DataString& s, char delim);
	static DataString getFilePath(const DataString& fileName);
	static bool loadTextFileWithIncludes(DataString& output, const DataString& fileName,
		const DataString& includeKeyword);
};
typedef StringConverter SC;