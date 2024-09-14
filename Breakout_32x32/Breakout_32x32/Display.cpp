#include "StdAfx.h"
#include "General.h"
#include "Led_Matrix.h"
#include "Char_BM.h"
#include "Display.h"
#include <math.h>

					
Display::Display(void)
{
}


Display::~Display(void)
{
}


void Display::ResetGame(void)
{
	m_Score = 0;
	m_LastDispScore = 0;
	m_Life = 3;
}

void Display::AddScore(int32 a_Value)
{
	m_Score = m_Score + a_Value;
	m_Sum_dT = 0;
}

void Display::DisplayLevelText(int8 a_Level)
{
	
	char A[] = "LEVEL";
	
	for (int8 y=32; y>-14; y--)
	{
		LM_Clear();
		m_CBM.WriteStr(A, 4,y);
		m_CBM.WriteChar(a_Level ,14 , y + 7);
		LM_PC_DSP_Display_Matrix();
		DELAY(20);
		if (y==10)
		{
			DELAY(2000);
		}
	}
	LM_Clear();
}

void Display::MarkOnMatrix(int16 a_dT)
{
	uint32 tScore;
	int8 x0, y0, Di;
	m_Sum_dT = m_Sum_dT + a_dT; 
	if(m_Sum_dT>2000)
	{
		tScore = m_Score;
		m_Sum_dT = 0;
	}
	else
	{
		int32 dS =(int32) (exp(-(float32)m_Sum_dT/50.0) * (m_Score - m_LastDispScore));
		dS = (m_Score > m_LastDispScore) ? MAX(1, dS) : 0;
		tScore = m_LastDispScore + dS;
	}

	m_LastDispScore = tScore;

	int8 Width = DIG_WIDTH + 1; 
	int8 i, N_Digit = 1;
	if (tScore > 9)			N_Digit = 2;
	if (tScore > 99)		N_Digit = 3;
	if (tScore > 999)		N_Digit = 4;
	if (tScore > 9999)		N_Digit = 5;
	if (tScore > 99999)		N_Digit = 6;
	if (tScore > 999999)	tScore = 999999;
		
	y0 = 0;

	for (i=0; i<N_Digit; i++)
	{
		Di = tScore%10;
		tScore = tScore / 10;

		x0 = (6 - N_Digit) * Width/2 + (N_Digit-1-i)*Width;

		for(int8 y=0; y<DIG_HEIGHT; y++)
		{
			uint8 Line = m_CBM.GetDigitOrLetterLine(Di, y);
			for(int8 x=0; x<DIG_WIDTH; x++)
			{
				LM_SetPoint( x0 + x, y0 + y ,(Line>>x) & 1);
			}
		}
	}
	y0 = 0;
	x0 = 27;
	Di = m_Life;
	for(int8 y=0; y<DIG_HEIGHT; y++)
	{
		uint8 Line = m_CBM.GetDigitOrLetterLine(Di,y);
		for(int8 x=0; x<DIG_WIDTH; x++)
		{
				LM_SetPoint( x0 + x, y0 + y ,(Line>>x) & 1);
		}
	}

	
}
