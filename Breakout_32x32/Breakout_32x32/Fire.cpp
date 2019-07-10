#include "stdafx.h"
#include "General.h"
#include "Brick.h"
#include "MovingBrick.h"
//#include "Display.h"
//#include "Led_Matrix.h"
#include "Fire.h"


Fire::Fire(void)
{
	Init();
}

void Fire::Init(void)
{
	m_Loc_s.m_w = FIRE_DEFAULT_WIDTH;
	m_Loc_s.m_h = FIRE_DEFAULT_HEIGHT;
	m_V_s.m_X = 0;
	m_V_s.m_Y = 0;
	m_Loc_s.m_X = -1;
	m_Loc_s.m_Y = -1;
	m_Acceleration = 0;
	m_MB_Type = eMB_Fire;
}
void Fire::Init(int8 a_x, int8 a_y, float32 a_Vx, float32 a_Vy)
{
	Init();
	MovingBrick::Init(a_x, a_y, a_Vx, a_Vy);
}

Fire::~Fire(void)
{
}


