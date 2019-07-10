
#include "stdafx.h"
#include "General.h"
#include "SnakePath.h"
#include "UI_Input.h"
#include "Led_Matrix.h"


int8 Nx = 32;
int8 Ny = 32;

stKeyStatus g_KeyStat_1;
stKeyStatus g_KeyStat_2;
UI_Input g_UI;



const stPoint P1s = {21, 22};
const stPoint P2s = {10, 22};

stPoint P1 = P1s;
stPoint P2 = P2s;

int8 g_Di1 = 0;  // direction of 1	
int8 g_Di2 = 0;  // direction of 1	

#define MAX_P_IN_ARR 100

stPoint P1_arr[MAX_P_IN_ARR];
stPoint P2_arr[MAX_P_IN_ARR];
int16 P12idx = 0;

int8 GameOver = 0;
int T_Delay;

int g_isFree_1;
int g_isFree_2;





stPoint Dir_arr[4] = {{0,-1}, {1,0}, {0,1}, {-1,0}}; // Up, Right, Down, Left


void GC_ResetGame()
{
	P1 = P1s;
	P2 = P2s;	

	g_Di1 = 0;  // direction of 1	
	g_Di2 = 0;  // direction of 2	
	
	P12idx = 0;
	GameOver = 0;
	T_Delay = 100;
	
	LM_Clear();
	g_UI.GetKeyStatus(&g_KeyStat_1, &g_KeyStat_2);
	DELAY (500);
	g_UI.GetKeyStatus(&g_KeyStat_1, &g_KeyStat_2);

	
}



void Switch_Direction(stKeyStatus *a_pKeyStat, int8* a_pDir)
{
	if (a_pKeyStat->m_L)
	{
		*a_pDir = 3;
	}
	if (a_pKeyStat->m_R)
	{
		*a_pDir = 1;
	}
	if (a_pKeyStat->m_U)
	{
		*a_pDir = 0;
	}
	if (a_pKeyStat->m_D)
	{
		*a_pDir = 2;
	}

}

int Test_if_Free_and_Set(stPoint* pP)
{
	if (pP->m_X<0 || pP->m_X >= N_X || pP->m_Y<0 || pP->m_Y >= N_Y)
	{
		return 0;
	}

	if (LM_GetPoint(pP->m_X, pP->m_Y))
	{
		return 0;
	}
	else
	{
		LM_SetPoint(pP->m_X, pP->m_Y, 1);
		return 1;
	}
}


void delay_and_change_dir_goto_next_step(int D)
{

	int8 oldDi1 = g_Di1;
	int8 oldDi2 = g_Di2;

	TIC_mS();
	while(TOC_mS()<D)
	{
		g_UI.GetKeyStatus(&g_KeyStat_1, &g_KeyStat_2);

		Switch_Direction(&g_KeyStat_1, &g_Di1);
		Switch_Direction(&g_KeyStat_2, &g_Di2);
	
	}
	
	P1.m_X += Dir_arr[g_Di1].m_X;
	P1.m_Y += Dir_arr[g_Di1].m_Y;
	g_isFree_1 = Test_if_Free_and_Set(&P1);

	if (g_isFree_1 == 0)
	{
		P1.m_X -= Dir_arr[g_Di1].m_X;
		P1.m_Y -= Dir_arr[g_Di1].m_Y;
		g_Di1 = oldDi1;
		P1.m_X += Dir_arr[g_Di1].m_X;
		P1.m_Y += Dir_arr[g_Di1].m_Y;
		g_isFree_1 = Test_if_Free_and_Set(&P1);
	}

	P2.m_X += Dir_arr[g_Di2].m_X;
	P2.m_Y += Dir_arr[g_Di2].m_Y;
	g_isFree_2 = Test_if_Free_and_Set(&P2);

	if (g_isFree_2 == 0)
	{
		P2.m_X -= Dir_arr[g_Di2].m_X;
		P2.m_Y -= Dir_arr[g_Di2].m_Y;
		g_Di2 = oldDi2;
		P2.m_X += Dir_arr[g_Di2].m_X;
		P2.m_Y += Dir_arr[g_Di2].m_Y;
		g_isFree_2 = Test_if_Free_and_Set(&P2);
	}
}



void DoGameOver(int a_isFree_1, int a_isFree_2)
{
	for(int i=0; i<P12idx-1; i++)
	{
		if (a_isFree_1==0)
		{
			LM_SetPoint(P1_arr[i].m_X, P1_arr[i].m_Y, 0);
		}
		if (a_isFree_2==0)
		{
			LM_SetPoint(P2_arr[i].m_X, P2_arr[i].m_Y, 0);
		}
		LM_PC_DSP_Display_Matrix();
		DELAY(30);
	}
}


void GC_Loop()
{
	
	GC_ResetGame();
	Test_if_Free_and_Set(&P1);
	Test_if_Free_and_Set(&P2);

	while (GameOver == 0)
	{
		
		LM_PC_DSP_Display_Matrix();
		delay_and_change_dir_goto_next_step(T_Delay);

		if (P12idx<MAX_P_IN_ARR)
		{
			P1_arr[P12idx] = P1;
			P2_arr[P12idx] = P2;
			P12idx++;

		}

		if (g_isFree_1 == 0 || g_isFree_2 == 0)
		{
			GameOver = 1;
			
		}
	}
	
	DoGameOver(g_isFree_1, g_isFree_2);
}

