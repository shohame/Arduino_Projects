#include "StdAfx.h"
#include "General.h"
#include "Led_Matrix.h"
#include "Char_BM.h"


const  Line_Bit  CharBM_arr[][CHAR_HEIGHT] PROGMEM =
	{
		#include "Char_BM_RAW.h"
	};



Char_BM::Char_BM(void)
{
	m_A_idx = _A_INDEX;
	m_0_idx = _0_INDEX;
	m_P_idx = _P_INDEX;
	m_UN_idx = _UN_INDEX;
}

//#include <string>
uint8 Char_BM::WriteStr(char a_pChar[], int8 a_X, int8 a_Y)
{
	uint8 Len = strlen(a_pChar);
	for(int8 C=0; C< Len; C++)
	{
		if ( a_pChar[C] == ' ' )
		{
			a_X += 3;
		}
		else
		{
			a_X += WriteChar( a_pChar[C],  a_X,  a_Y);
		}
	}
	return a_X;
}


uint8 Char_BM::WriteChar(uint8 a_Char, int8 a_X, int8 a_Y)
{
	int8 Width =  GetDigitOrLetterWidth(a_Char);	
	for(int8 y=0; y<CHAR_HEIGHT; y++)
	{
		uint8 Line = GetDigitOrLetterLine(a_Char, y);
		for(int8 x=0; x<Width; x++)
		{
			LM_SetPoint( a_X + x, a_Y + y ,(Line>>x) & 1);
		}
	}
	return Width + 1;
}

uint8 Char_BM::GetDigitOrLetterLine(uint8 a_Char, uint8 a_Line)
{
	uint8 CharIdx = m_UN_idx;

	if (a_Char<10)
	{
		CharIdx = m_0_idx + a_Char;
	}
	else if (a_Char>='0' && a_Char<='9')
	{
		CharIdx = m_0_idx + (a_Char - '0');
	}
	else if (a_Char>='a' && a_Char<='z')
	{
		CharIdx = m_A_idx + (a_Char - 'a');
	}
	else if (a_Char>='A' && a_Char<='Z')
	{
		CharIdx = m_A_idx + (a_Char - 'A');
	}

	uint8 Line = pgm_read_word_near((int8*)&CharBM_arr[CharIdx][a_Line]);
	
	return Line;
}

uint8 Char_BM::GetDigitOrLetterWidth(uint8 a_Char)
{
	int8 Width = 0;

	for (int8 y=0; y<CHAR_HEIGHT; y++)
	{
		uint8 Line = GetDigitOrLetterLine(a_Char, y);
		int8 W = 0;
		while (Line!=0)
		{
			W++;
			Line = Line >> 1;
		}
		Width = MAX (Width, W);
	}
	return Width;
}


uint8 Char_BM::GetPriceLine(uint8 a_PriceIdx, uint8 a_Line)
{
	uint8 CharIdx = m_UN_idx;

	if (a_PriceIdx >= 0 && a_PriceIdx <= 4)
	{
		CharIdx = m_P_idx + a_PriceIdx;
	}

	uint8 Line = pgm_read_word_near((int8*)&CharBM_arr[CharIdx][a_Line]);
	return Line;

}
	 
	 
