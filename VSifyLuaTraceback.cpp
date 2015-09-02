#include "VSifyLuaTraceback.h"

using namespace std;

namespace
{
	//-------------------------------------------------------------------------
	bool ReadLine(size_t& begin, const string& text, string& line)
	{
		size_t i = begin;
		while (i < text.size())
		{
			if (text[i] == '\n')
			{
				line = text.substr(begin, i + 1 - begin);
				begin = i + 1;
				return true;
			}
			++i;
		}

		if (begin == text.size())
		{
			return false;
		}
		else
		{
			line = text.substr(begin, text.size() - begin);
			begin = text.size();
			return true;
		}
	}

	//-------------------------------------------------------------------------
	string ConvertLine(string line, bool first, const string& pathPrefix)
	{
		bool candidate = (first || (!line.empty() && line[0] == '\t'));
		if (!candidate) { return line; }

		size_t firstColonPos = line.find(':');
		if (firstColonPos == string::npos) { return line; }

		size_t secondColonPos = line.find(':', firstColonPos + 1);
		if (secondColonPos == string::npos) { return line; }

		for (size_t i = firstColonPos + 1; i < secondColonPos; ++i)
		{
			if (!isdigit(line[i])) { return line; }
		}

		// Nested error position {
		if (secondColonPos + 2 < line.size() &&
			line[secondColonPos + 1] == ' ' &&
			line[secondColonPos + 2] == '$')
		{
			string rest = line.substr(secondColonPos + 3);
			string convertedRest = ConvertLine(rest, first, pathPrefix);
			if (rest != convertedRest)
			{
				return convertedRest;
			}
		}
		// Nested error position }

		size_t begin = first ? 0 : 1;

		string path = line.substr(begin, firstColonPos - begin);
		if (path.substr(0, 9) == "[string \"" &&
			path.substr(path.length() - 2) == "\"]")
		{
			path = path.substr(9, path.length() - 11);
		}
		if (path.substr(0, 2) == ".\\")
		{
			path = path.substr(2);
		}
		for (size_t i = 0; i < path.length(); ++i)
		{
			if (path[i] == '/') { path[i] = '\\'; }
		}


		string rv;
		rv.reserve(line.size() + pathPrefix.size() + 5);
		if (!first)
		{
			rv = "\t";
		}
		rv += pathPrefix;
		rv += path;
		rv += "(";
		rv += line.substr(firstColonPos + 1, secondColonPos - firstColonPos - 1);
		rv += ")";
		rv += line.substr(secondColonPos);

		return rv;
	}
}

//-----------------------------------------------------------------------------
string VSifyLuaTraceback(
	const string& traceback,
	const string& pathPrefix)
{
	string rv;
	rv.reserve(traceback.size());

	bool first = true;
	size_t begin = 0;
	string line;
	while (ReadLine(begin, traceback, line))
	{
		rv += ConvertLine(line, first, pathPrefix);
		first = false;
	}

	return rv;
}
