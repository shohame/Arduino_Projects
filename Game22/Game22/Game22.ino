#include "stdafx.h"
#include "General.h"
#include "Main.h"

void setup()
{
	Setup();
}

void loop()
{
	Loop();
}

#ifdef WIN32	
int32 _tmain(int32 argc, _TCHAR* argv[])
{
   HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);

	Setup();
	while(1)
	{
		Loop();
	}
	return 0;
}
#endif


