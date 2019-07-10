#include "stdafx.h"
#include "General.h"
#include "Led_Matrix.h"
#include "Brick.h"
#include "MovingBrick.h"
#include "Stick.h"
#include "Ball.h"
#include "Fire.h"
#include "Price.h"
#include "Display.h"
#include "BrickArrTemp.h"
#include "Bricks.h"
#include "UI_Input.h"
#include "Globe.h"

#include "Breakout.h"

Bricks g_Bricks;
UI_Input g_UI_In;
int8 Level = 1;

void RestartGame()
{
	Level = 0;
	g_Bricks.m_Disply.ResetGame();
	g_Bricks.ClearAllBricksBallsWalls();
	LM_Clear();
	TIC_mS();
}

int Arr[] = {1,2,3,4,5,6};


void Setup()
{
	GET_RAMDOM_SEED();
	SERIAL_BEGIN(9600);
	DELAY(1000);
	LM_Setup();
	RestartGame();
}

void Loop()
{
	Bricks *pBricks = &g_Bricks; 
	int16 Toc = (int16)TOC_mS();
	Toc = MIN(Toc, MAX_FRAME_TIME);
	if (pBricks->m_BrickArr.m_Count == 0)
	{
		DELAY(500);
		Level ++;
		pBricks->InitLevel(Level);
	}
	if (pBricks->m_BallArr.m_Count==0)
	{
		DELAY(500);
		if (pBricks->m_Disply.m_Life == 0) // Game Over
		{
			DELAY(1000);		
			RestartGame();
		}
		else
		{
			pBricks->m_Disply.m_Life--;
			pBricks->m_BallArr.Add(16,28, (float)3, (float)-6.0);
			pBricks->m_Stick.ChangeStickType(eStickRegular);
		}
 	}

	TIC_mS();
  
	pBricks->MoveAllBalls(Toc);
	pBricks->MoveAllPrices(Toc);
	pBricks->MoveAllFires(Toc);

	LM_Clear();
	pBricks->MarkBricksOnMatrix();
	pBricks->m_Disply.MarkOnMatrix(Toc);
	LM_PC_DSP_Display_Matrix();
	
	stKeyStatus P1_s, P2_s;

	g_UI_In.GetKeyStatus(&P1_s, &P2_s);

	if ( P1_s.m_R)
		pBricks->m_Stick.m_Loc_s.m_X += 0.9f;
	if (  P1_s.m_L)
		pBricks->m_Stick.m_Loc_s.m_X -= 0.9f;
	if (P1_s.m_U && pBricks->m_Stick.m_Type == eStickFire)
	{
		int8 x = ROUND_CORD_TO_U8(pBricks->m_Stick.m_Loc_s.m_X + ((pBricks->m_Stick.m_Loc_s.m_w - 1)/2));
		int8 y = ROUND_CORD_TO_U8(pBricks->m_Stick.m_Loc_s.m_Y - 1);
		pBricks->m_FireArr.Add(x, y, (float)0, (float)FIRE_DEFAULT_SPEED); 
	}

	if (P1_s.m_U && P1_s.m_D && P1_s.m_L && P1_s.m_R)
	{
		resetFunc();
	}


}
#ifdef WIN32	
int32 Main(int32 argc, _TCHAR* argv[])
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


