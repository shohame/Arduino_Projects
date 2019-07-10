#include "StdAfx.h"
#include "General.h"
#include "Brick.h"
#include "MovingBrick.h"
#include "Stick.h"
#include "LED_Matrix.h"

Stick::Stick(void)
{
	Init();
}

void Stick::Init(void)
{
	m_Loc_s.m_w = STICK_DEFAULT_WIDTH;
	m_Loc_s.m_h = STICK_DEFAULT_HEIGHT;
	m_Loc_s.m_X = STICK_DEFAULT_X + 0;
	m_Loc_s.m_Y = STICK_DEFAULT_Y;
}

Stick::~Stick(void)
{
}

void Stick::ChangeStickType(eStickType a_StickType)
{
	m_Type = a_StickType;
	int8 w = m_Loc_s.m_w;

	switch (m_Type)
	{
		case(eStickRegular):
		{
			m_Loc_s.m_w = STICK_DEFAULT_WIDTH;
			break;
		}
		case(eStickLarge):
		{
			m_Loc_s.m_w = STICK_DEFAULT_WIDTH + 2;
			break;
		}
		case(eStickSmall):
		{
			m_Loc_s.m_w = STICK_DEFAULT_WIDTH - 2;
			break;
		}
		default:
			{}
	}

	m_Loc_s.m_X -= (m_Loc_s.m_w - w)/2;


}


void Stick::MarkBrickOnMatrix(void)
{
	if (m_Type==eStickFire)
	{
		int8 x = ROUND_CORD_TO_U8(m_Loc_s.m_X + (m_Loc_s.m_w - 1)/2);
		int8 y = ROUND_CORD_TO_U8(m_Loc_s.m_Y - 1);
		LM_SetPoint(x, y, 1);
	}
	Brick::MarkBrickOnMatrix();
}




