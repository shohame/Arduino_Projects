#include "StdAfx.h"
#include "General.h"
#include "Char_BM.h"
#include "Brick.h"
#include "MovingBrick.h"
#include "Ball.h"
#include "Price.h"
#include "Fire.h"
#include "Stick.h"
#include "Display.h"
#include "BrickArrTemp.h"
#include "GameControl.h"


GameControl::GameControl(void)
{
	ClearAllBricksBallsWalls();
}
GameControl::~GameControl(void)
{
}

void GameControl::MarkBricksOnMatrix()
{
	m_BrickArr.	MarkBrickArrOnMatrix();
	m_BallArr.	MarkBrickArrOnMatrix();
	m_WallArr.	MarkBrickArrOnMatrix();
	m_PriceArr.	MarkBrickArrOnMatrix();
	m_FireArr.	MarkBrickArrOnMatrix();

	m_Stick.MarkBrickOnMatrix();
}


void GameControl::MoveAllBalls(int16 a_dT_mSec)
{
	int8 BrickID;
	BallArr* pBrickArr = &m_BallArr;
	Ball *pBrick;


	pBrickArr->IterBegin();
	while((pBrick = pBrickArr->IterNext()) != NULL)
	{
		pBrick->Move(a_dT_mSec);

		if (pBrick->m_Loc_s.m_Y >= 30) // if ball missed stick and fell down
		{
			pBrickArr->IterRemove();
			continue;
		}

		BrickID = pBrick->FindBallCollision(m_WallArr.m_Brick_a, m_WallArr.m_Count);
		BrickID = pBrick->FindBallCollision(m_BrickArr.m_Brick_a , m_BrickArr.m_Count);
		if (BrickID>=0)
		{
			if (RAND_INT(0, GIVE_PRICE_RATE) == 0)
			{
				ePriceType PriceType = (ePriceType) ((int8)eLarge +(int8)RAND_INT(0, PRICE_TYPE_COUNT));
				m_PriceArr.Add(	ROUND_CORD_TO_U8(m_BrickArr.m_Brick_a[BrickID].m_Loc_s.m_X), 
								ROUND_CORD_TO_U8(m_BrickArr.m_Brick_a[BrickID].m_Loc_s.m_Y), PriceType);
			}
			m_BrickArr.Remove(BrickID);	// Remove just if BrickID>=0 !
			m_Disply.AddScore(125);
		}
		pBrick->Where_I_TouchStick(&m_Stick);
	}
}

void GameControl::MoveAllFires(int16 a_dT_mSec)
{
	int8 BrickID;
	FireArr* pBrickArr = &m_FireArr;
	Fire *pBrick;
	stBrickTouchProp TouchProp_s;
	pBrickArr->IterBegin();
	while((pBrick = pBrickArr->IterNext()) != NULL)
	{
		pBrick->Move(a_dT_mSec);
		
		BrickID = pBrick->FindCollision(m_WallArr.m_Brick_a, m_WallArr.m_Count, &TouchProp_s);
		if (BrickID>=0)
		{
			m_FireArr.IterRemove();
		}

		BrickID = pBrick->FindCollision(m_BrickArr.m_Brick_a, m_BrickArr.m_Count, &TouchProp_s);
		if (BrickID>=0)
		{
			if (RAND_INT(0, GIVE_PRICE_RATE) == 0)
			{
				ePriceType PriceType = (ePriceType) ((int8)eLarge +(int8)RAND_INT(0, PRICE_TYPE_COUNT));
				m_PriceArr.Add(	ROUND_CORD_TO_U8(m_BrickArr.m_Brick_a[BrickID].m_Loc_s.m_X), 
								ROUND_CORD_TO_U8(m_BrickArr.m_Brick_a[BrickID].m_Loc_s.m_Y), PriceType);
			}
			m_BrickArr.Remove(BrickID);	// Remove just if BrickID>=0 !
			m_FireArr.IterRemove();
			m_Disply.AddScore(125);
		}
	}
}

void GameControl::MoveAllPrices(int16 a_dT_mSec)
{
	PriceArr* pBrickArr = &m_PriceArr;
	Price *pBrick;
	stBrickTouchProp TouchProp_s;


	pBrickArr->IterBegin();
	while((pBrick = pBrickArr->IterNext()) != NULL)
	{
		pBrick->Move(a_dT_mSec);
		if(pBrick->m_Loc_s.m_Y > 30)
		{
			pBrickArr->IterRemove();
			continue;
		}
		pBrick->FindCollision(&m_Stick, 1, &TouchProp_s);
		if (TouchProp_s.m_isTouch)
		{	
			GetThePrice(pBrick->m_eType, ROUND_CORD_TO_U8(pBrick->m_Loc_s.m_X), ROUND_CORD_TO_U8(pBrick->m_Loc_s.m_Y));
			pBrickArr->IterRemove();
			continue;
		}
	}
}


void GameControl::GetThePrice(ePriceType a_eType, int8 a_x, int8 a_y)
{
	switch(a_eType)
	{
		case(eLarge):
		{
			m_Stick.ChangeStickType(eStickLarge);
			break;
		}
		case(eSmall):
		{
			m_Stick.ChangeStickType(eStickSmall);
			break;
		}
		case(eThree):
		{
			m_BallArr.Add(a_x, a_y, (int8)2, (int8)-4	);
			m_BallArr.Add(a_x, a_y, (int8)-2, (int8)-3);
			m_BallArr.Add(a_x, a_y, (int8)0, (int8)-7	);
			break;
		}
		case(eBall):
		{
			if (m_Disply.m_Life<9)
				m_Disply.m_Life++;
			break;
		}
		case(eFire):
		{
			m_Stick.ChangeStickType(eStickFire);
			break;
		}
	}
}

void GameControl::ClearAllBricksBallsWalls()
{
	m_BrickArr.	ClearAll();
	m_BallArr.	ClearAll();
	m_WallArr.	ClearAll();	
	m_PriceArr.	ClearAll();	
	m_FireArr.	ClearAll();
}



void GameControl::InitLeve_Clear()
{
	ClearAllBricksBallsWalls();

	m_Stick.ChangeStickType(eStickRegular);

	m_WallArr.Add(32,-1, (int8)1, (int8)34);	// Right wall
	m_WallArr.Add(-1,-1, (int8)1, (int8)34);	// Left wall
	m_WallArr.Add(0,6,(int8)32, (int8)1);		// Top wall
	m_WallArr.Add(24,0,(int8)1, (int8)6);		// Score / Life divader 
}

void GameControl::AddLineOfBricks(int8 a_x0, int8 a_y0, int8 a_Count)
{
	for(int8 x=0; x<a_Count; x++)
	{
		m_BrickArr.Add(a_x0 + x*(BREAK_DEFAULT_WIDTH+1), a_y0);
	}
}


void GameControl::InitLevel(int8 a_Level)
{
	InitLeve_Clear();

	switch(a_Level)
	{
	case 1:
		AddLineOfBricks(0, 8, 8);
		AddLineOfBricks(2, 11, 7);
		break;
		break;
	case 2:
		AddLineOfBricks(0, 8, 8);
		AddLineOfBricks(2, 11, 7);
		AddLineOfBricks(0, 14, 8);
		AddLineOfBricks(2, 17, 7);
		break;
	case 3:
		m_WallArr.Add(8, 12, (int8)1, (int8)14);
		m_WallArr.Add(22, 12, (int8)1, (int8)14);
		m_WallArr.Add(8, 25, (int8)15, (int8)1);
		m_BrickArr.Add(8, 10);
		m_BrickArr.Add(11, 10);
		m_BrickArr.Add(14, 10);
		m_BrickArr.Add(17, 10);
		m_BrickArr.Add(20, 10);
		m_BrickArr.Add(10, 14);
		m_BrickArr.Add(18, 18);
		break;
	case 4:
		m_WallArr.Add(3, 10, (int8)1, (int8)14);
		m_WallArr.Add(4, 13, (int8)7, (int8)2);
		m_WallArr.Add(26, 10, (int8)1, (int8)14);
		m_WallArr.Add(19, 13, (int8)7, (int8)2);
		m_WallArr.Add(14, 11, (int8)2, (int8)14);
		m_WallArr.Add(9, 17, (int8)12, (int8)2);
		m_BrickArr.Add(20, 21);
		m_BrickArr.Add(7, 21);
		m_BrickArr.Add(11, 13);
		m_BrickArr.Add(16, 13);
		m_BrickArr.Add(6, 9);
		m_BrickArr.Add(21, 9);
		break;
	case 5:
		m_WallArr.Add(0, 17, (int8)6, (int8)1);
		m_WallArr.Add(10, 17, (int8)11, (int8)1);
		m_WallArr.Add(26, 17, (int8)6, (int8)1);
		m_WallArr.Add(15, 9, (int8)1, (int8)17);
		m_BrickArr.Add(3, 10);
		m_BrickArr.Add(9, 14);
		m_BrickArr.Add(4, 19);
		m_BrickArr.Add(9, 22);
		m_BrickArr.Add(20, 10);
		m_BrickArr.Add(26, 14);
		m_BrickArr.Add(21, 19);
		m_BrickArr.Add(26, 22);
		break;
	case 6:
		AddLineOfBricks(0, 8, 8);
		AddLineOfBricks(2, 15, 7);

		m_WallArr.Add(0, 12, (int8)11, (int8)1);
		m_WallArr.Add(21, 12, (int8)11, (int8)1);
		break;

	case 7:
		AddLineOfBricks(0, 8,  8);
		AddLineOfBricks(2, 11, 7);

		m_WallArr.Add(0, 16, (int8)17, (int8)1);	
		m_WallArr.Add(22 ,16,(int8)6 , (int8)1);	
		m_WallArr.Add(0, 23, (int8)9,	(int8)1);	
		m_WallArr.Add(15, 23, (int8)13, (int8)1);	
		break;
	case 8:
		AddLineOfBricks(0, 8,  8);

		m_BrickArr.Add(3, 21);
		m_BrickArr.Add(26, 21);

		m_WallArr.Add(0,	13,	(int8)12,	(int8)1);	
		m_WallArr.Add(17,	13,	(int8)7,	(int8)1);	
		m_WallArr.Add(11,	17,	(int8)6,	(int8)1);	
		m_WallArr.Add(0,	21,	(int8)3,	(int8)2);	
		m_WallArr.Add(6,	21,	(int8)20,	(int8)2);	
		m_WallArr.Add(29,	21,	(int8)3,	(int8)2);	

		break;

	}
	m_BallArr.Add(16,28, (float)3.0, (float)-6.1);
}

