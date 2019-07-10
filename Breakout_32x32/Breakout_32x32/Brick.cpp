#include "StdAfx.h"
#include <math.h>
#include "General.h"
#include "Brick.h"
#include "Led_Matrix.h"


Brick::Brick()
{
	Init();
}

void Brick::Init(void)
{
	m_Loc_s.m_X = -1;
	m_Loc_s.m_Y = -1;
	m_Loc_s.m_w = BREAK_DEFAULT_WIDTH;
	m_Loc_s.m_h = BREAK_DEFAULT_HEIGHT;
}

void Brick::Init(int8 a_x, int8 a_y)
{
	m_Loc_s.m_X = a_x;
	m_Loc_s.m_Y = a_y;
	m_Loc_s.m_w = BREAK_DEFAULT_WIDTH;
	m_Loc_s.m_h = BREAK_DEFAULT_HEIGHT;
}

void Brick::Init(int8 a_x, int8 a_y, int8 a_w, int8 a_h)
{
	m_Loc_s.m_X = a_x;
	m_Loc_s.m_Y = a_y;
	m_Loc_s.m_w = a_w;
	m_Loc_s.m_h = a_h;
}


Brick::~Brick(void)
{
}


 void Brick::MarkBrickOnMatrix()
 {
	for(int8 y=0; y<(int8)m_Loc_s.m_h; y++)
	{
		for(int8 x=0; x<(int8)m_Loc_s.m_w; x++)
		{
			int8 yi = y + ROUND_CORD_TO_U8(m_Loc_s.m_Y);
			int8 xi = x + ROUND_CORD_TO_U8(m_Loc_s.m_X);
			LM_SetPoint(xi,  yi , 1);
		}
	}
 }


void Brick::SetPos(int8 a_x, int8 a_y)
{
	m_Loc_s.m_X = a_x;
	m_Loc_s.m_Y = a_y;
}

void Brick::SetLoc(int8 a_x, int8 a_y, int8 a_w, int8 a_h)
{
	m_Loc_s.m_X = a_x;
	m_Loc_s.m_Y = a_y;
	m_Loc_s.m_w = a_w;
	m_Loc_s.m_h = a_h;
}


void Brick::WhereBrickTouchMe (Brick * a_pBrick, stBrickTouchProp* a_pTouchProp)
{

	stLoc	Y_Loc = a_pBrick->m_Loc_s;
	stLoc	M_Loc = m_Loc_s;

	float32 Y_half_w =  (float32)Y_Loc.m_w / 2.0f;
	float32 M_half_w =  (float32)M_Loc.m_w / 2.0f;
	float32 Y_half_h =  (float32)Y_Loc.m_h / 2.0f;
	float32 M_half_h =  (float32)M_Loc.m_h / 2.0f;

	float32 Y_Cx = Y_Loc.m_X + Y_half_w;
	float32 M_Cx = M_Loc.m_X + M_half_w;
	float32 Y_Cy = Y_Loc.m_Y + Y_half_h;
	float32 M_Cy = M_Loc.m_Y + M_half_h;

	float32 dX  = ( Y_half_w + M_half_w) - abs( Y_Cx - M_Cx); // if dX > 0  ==> Thay can be tuched!
	float32 dY  = ( Y_half_h + M_half_h) - abs( Y_Cy - M_Cy); // if dy > 0  ==> Thay can be tuched!
	


	if ( dX > 0 && dY > 0) // 
	{
		a_pTouchProp->m_isTouch = true;
		a_pTouchProp->m_Depth = (dX<dY) ? dX : dY;
		a_pTouchProp->m_Direction = ( (dX > dY) ? HORIZONTAL : VERTICAL ); // 1 => Tuching the horizontal eage, 2 => Vertical
		a_pTouchProp->m_dAngle = (int8)(45.0 * (M_Cx - Y_Cx) / Y_half_w);
	}
	else
	{
		a_pTouchProp->m_isTouch = false;
		a_pTouchProp->m_Direction = NO_TOUCH;
		a_pTouchProp->m_Depth = 0;
		a_pTouchProp->m_dAngle = 0;
	}
}

