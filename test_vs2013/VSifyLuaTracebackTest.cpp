#include "stdafx.h"
#include "../VSifyLuaTraceback.h"
#include <iostream>

using namespace std;

int _tmain()
{
	string tb =
		".\\a\\b.lua:2: Error in b.lua\n"
		"stack traceback:\n"
		"\t[C]: in function 'error'\n"
		"\t.\\a\\b.lua:2: in function 'B'\n"
		"\ttest.lua:7: in function 'step'\n"
		"\t[string \"lib/UnitTest.lua\"]:88: in function 'TestType'\n"
		"\ttest.lua:11: in main chunk\n"
		"\t[C]: ?\n"
		"\n";

	cout << endl << "Input:" << endl << tb << endl << endl;
	cout << "Output:" << endl << VSifyLuaTraceback(tb, "c:\\Test\\");
	return 0;
}

