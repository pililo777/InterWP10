#pragma once
#include <string>

namespace CppWINRT {
    using namespace Windows::Foundation;
    using Platform::String;

    public ref class StringCharacterCounter sealed {
	public:
		unsigned int GetLength(String^ strToParse);
    };










}

