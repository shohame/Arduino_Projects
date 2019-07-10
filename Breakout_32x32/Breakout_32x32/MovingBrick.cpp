#include "StdAfx.h"
#include <math.h>
#include "General.h"
#include "Brick.h"
#include "MovingBrick.h"


void MovingBrick::Init(int8 a_x, int8 a_y, float32 a_Vx, float32 a_Vy)
{
	m_Loc_s.m_X = a_x;
	m_Loc_s.m_Y = a_y;
	m_V_s.m_X = a_Vx;
	m_V_s.m_Y = a_Vy;
}

void MovingBrick::ChangeAngleBy(float32 a_dAngle)
{

	float32 A = sqrt(POW2(m_V_s.m_X) + POW2(m_V_s.m_Y));
	float32 ang = RAD2DEG(atan2(m_V_s.m_Y, m_V_s.m_X));

	ang += a_dAngle;

	ang = MIN(-90 + MAX_ANGLE, ang);
	ang = MAX(-90 - MAX_ANGLE, ang);

	m_V_s.m_X = A * (float32)cos(  DEG2RAD(ang) );
	m_V_s.m_Y = A * (float32)sin(  DEG2RAD(ang) );

}

int8 MovingBrick::FindCollision(Brick a_Brick_arr[], int8 a_BrickCount, stBrickTouchProp* a_pTouchProp)
{
	int8 i = -1;
	
	for (i=0; i<a_BrickCount; i++)
	{
		WhereBrickTouchMe(&a_Brick_arr[i], a_pTouchProp);
		if (a_pTouchProp->m_isTouch)
		{
			return i;
		}
	}
	return -1;
}


void MovingBrick::SetSpeed(stVector* a_pV)
{
	m_V_s.m_X = a_pV->m_X;
	m_V_s.m_Y = a_pV->m_Y;
}

void MovingBrick::SetSpeed(float32 a_Vx, float32 a_Vy)
{
	m_V_s.m_X = a_Vx;
	m_V_s.m_Y = a_Vy;
}

void MovingBrick::Move(int16 a_dT_mSec)
{
	if (ABS(m_V_s.m_Y) < 1.5)
	{
		m_V_s.m_Y += 0.5;
	}

	m_Loc_s.m_X +=  m_V_s.m_X * (float32)a_dT_mSec / 1000.0f;
	m_Loc_s.m_Y +=  m_V_s.m_Y * (float32)a_dT_mSec / 1000.0f;

	float32 SpeedFactor = 1.0f + ((float32)m_Acceleration) * (float32)a_dT_mSec / 1000.0f / 1000.0f;

	m_V_s.m_X *= SpeedFactor;
	m_V_s.m_Y *= SpeedFactor;
}


void MovingBrick::Bounce(int8 a_Direction, float32 a_Depth = 0)
{
	if (a_Direction == HORIZONTAL)
	{
		m_Loc_s.m_Y -= fSIGN( m_V_s.m_Y ) * 2.0f * a_Depth; 		
		m_V_s.m_Y = -m_V_s.m_Y;
	}

	if (a_Direction == VERTICAL)
	{
		m_Loc_s.m_X -= fSIGN( m_V_s.m_X ) * a_Depth; 		
		m_V_s.m_X = -m_V_s.m_X;
	}
}


