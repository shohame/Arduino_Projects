#include "StdAfx.h"
#include "General.h"
#include "Char_BM.h"
#include "Led_Matrix.h"


const  Line_Bit  CharBM_arr[][CHAR_HEIGHT] PROGMEM = CHAR_BITMAP_ARR;



Char_BM::Char_BM(void)
{
	m_A_idx = _A_INDEX;
	m_0_idx = _0_INDEX;
}


