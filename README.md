### VSifyLuaTraceback
VSifyLuaTraceback enchants Lua's debug.traceback() result to enable jumping into exact Lua source code position shown in Visual Studio's Output Window.

#### Sample input:

```
.\a\b.lua:2: Error in b.lua
stack traceback:
	[C]: in function 'error'
	.\a\b.lua:2: in function 'B'
	test.lua:7: in function 'step'
	[string "lib/UnitTest.lua"]:88: in function 'TestType'
	test.lua:11: in main chunk
	[C]: ?
```

#### Sample output(using "C:\Test\" as pathPrefix):

```
C:\Test\a\b.lua(2): Error in b.lua
stack traceback:
	[C]: in function 'error'
	C:\Test\a\b.lua(2): in function 'B'
	C:\Test\test.lua(7): in function 'step'
	C:\Test\lib\UnitTest.lua(88): in function 'TestType'
	C:\Test\test.lua(11): in main chunk
	[C]: ?
```
