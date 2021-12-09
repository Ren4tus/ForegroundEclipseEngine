#pragma once
#include <string>
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

};
typedef StringConverter SC;