
#include "stdafx.h"
#include "General.h"
#include "Led_Matrix.h"
#include "GameControl.h"
#include "Main.h"

#ifdef WIN32	
void RestartGame()
{
	GC_ResetGame();
}
#endif


void Setup()
{
	LM_Setup();
	LM_Clear();
	GC_ResetGame();
}

void Loop()
{
	while(1)
	{
		GC_Loop();
	}
}


