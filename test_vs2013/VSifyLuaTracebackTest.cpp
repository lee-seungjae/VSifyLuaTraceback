#include "stdafx.h"
#include "../VSifyLuaTraceback.h"
#include <iostream>
#include <cassert>

using namespace std;

void test(const string& input, const string& expected)
{
	string output = VSifyLuaTraceback(input, "c:\\Test\\");

	cout << endl << "Input:" << endl << input << endl << endl;
	cout << "Output:" << endl << output << endl << endl;

	assert(output == expected);
}

int _tmain()
{
	// basic test
	test(
		".\\a\\b.lua:2: Error in b.lua\n"
		"stack traceback:\n"
		"\t[C]: in function 'error'\n"
		"\t.\\a\\b.lua:2: in function 'B'\n"
		"\ttest.lua:7: in function 'step'\n"
		"\t[string \"lib/UnitTest.lua\"]:88: in function 'TestType'\n"
		"\ttest.lua:11: in main chunk\n"
		"\t[C]: ?\n"
		,
		"c:\\Test\\a\\b.lua(2): Error in b.lua\n"
		"stack traceback:\n"
		"	[C]: in function 'error'\n"
		"	c:\\Test\\a\\b.lua(2): in function 'B'\n"
		"	c:\\Test\\test.lua(7): in function 'step'\n"
		"	c:\\Test\\lib\\UnitTest.lua(88): in function 'TestType'\n"
		"	c:\\Test\\test.lua(11): in main chunk\n"
		"	[C]: ?\n"
		);

	// nested: 2
	test(
		".\\a\\b.lua:5: $.\\a\\b.lua:2: Error in b.lua",
		"c:\\Test\\a\\b.lua(2): Error in b.lua"
		);

	// nested: 3
	test(
		".\\a\\b.lua:15: $.\\a\\b.lua:5: $.\\a\\b.lua:2: Error in b.lua",
		"c:\\Test\\a\\b.lua(2): Error in b.lua"
		);

	// looks like nested error position, but actually it isn't
	test(
		".\\a\\b.lua:15: $",
		"c:\\Test\\a\\b.lua(15): $"
		);

	return 0;
}

