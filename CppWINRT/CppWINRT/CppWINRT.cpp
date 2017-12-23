// CppWINRT.cpp
#include "pch.h"
#include "CppWINRT.h"

using namespace CppWINRT;
using namespace Platform;

unsigned int StringCharacterCounter::GetLength(String^ strToParse) {
	std::wstring stlString = strToParse->Data();

	return stlString.length();
}

