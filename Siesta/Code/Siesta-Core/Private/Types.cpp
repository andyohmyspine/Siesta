#include "Types.h"

TString WideStringToString(const TWideString& WideString)
{
	TString Out;
	Out.resize(WideString.size(), 0);
	wcstombs(Out.data(), WideString.data(), Out.size());
	return Out;
}

TWideString StringToWideString(const TString& String)
{
	TWideString Out;
	Out.resize(String.size(), 0);
	mbstowcs(Out.data(), String.data(), Out.size());
	return Out;
}
