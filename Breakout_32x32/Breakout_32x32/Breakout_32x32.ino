#include "stdafx.h"
#include "General.h"
#include "Breakout.h"



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
	Main(argc, argv);
}
#endif


