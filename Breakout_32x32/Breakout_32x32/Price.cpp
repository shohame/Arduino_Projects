#include "stdafx.h"
#include "General.h"
#include "Brick.h"
#include "MovingBrick.h"
#include "Display.h"
#include "Led_Matrix.h"
#include "Price.h"

Price::Price(void)
{
	Init();
}

void Price::Init(void)
{
	m_Loc_s.m_w = PRICE_DEFAULT_WIDTH;
	m_Loc_s.m_h = PRICE_DEFAULT_HEIGHT;
	m_V_s.m_X = 0;
	m_V_s.m_Y = PRICE_DEFAULT_SPEED;
	m_Loc_s.m_X = -1;
	m_Loc_s.m_Y = -1;
	m_Acceleration = 0;
	m_MB_Type = eMB_Price;
}

void Price::Init(int8 a_x, int8 a_y, ePriceType a_Type)
{
	Init();

	m_Loc_s.m_X = a_x;
	m_Loc_s.m_Y = a_y;
	m_eType = a_Type;
}


Price::~Price(void)
{
}


void Price::MarkBrickOnMatrix()
{
	for(int8 y=0; y<DIG_HEIGHT; y++)
	{
		for(int8 x=0; x<DIG_WIDTH; x++)
		{
				int8 Line = pgm_read_word_near((int8*)&Digit_arr[m_eType][y]);

				if((Line>>x) & 1)
				{
					LM_SetPoint( (int8)m_Loc_s.m_X + x, (int8)m_Loc_s.m_Y + y, 1);
				}
		}
	}

}