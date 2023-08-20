#include "PacketParsing.h"

std::string toString(const std::wstring& wstr)
{
	std::vector<char> buf(wstr.size());
	std::use_facet<std::ctype<wchar_t>>(std::locale{}).narrow(wstr.data(), wstr.data() + wstr.size(), '?', buf.data());

	return std::string(buf.data(), buf.size());
}

std::ostream& operator<<(std::ostream& out, const std::wstring& string)
{
	return out << toString(string);
}