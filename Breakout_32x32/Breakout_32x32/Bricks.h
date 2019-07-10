#ifndef __BREAKS_H
#define __BREAKS_H

//#include "BrickArrTemp.h"

#define MAX_NUM_OF_BREAKS		((8)*4)
#define MAX_NUM_OF_BALLS		(10)
#define MAX_NUM_OF_WALLS		(10)
#define MAX_NUM_OF_PRICE		(5)
#define MAX_NUM_OF_FIRE			(10)

typedef BrickArrTemp<Brick, MAX_NUM_OF_BREAKS>	BrickArr;
typedef BrickArrTemp<Ball,	MAX_NUM_OF_BALLS>	BallArr;
typedef BrickArrTemp<Brick, MAX_NUM_OF_WALLS>	WallArr;
typedef BrickArrTemp<Price,	MAX_NUM_OF_PRICE>	PriceArr;
typedef BrickArrTemp<Fire,	MAX_NUM_OF_FIRE>	FireArr;


#define GIVE_PRICE_RATE		5  // for each 5 bricks give 1 price

class Bricks
{
public:
	Bricks(void);
	~Bricks(void);

	Display	m_Disply;

	BallArr		m_BallArr;
	BrickArr	m_BrickArr;
	WallArr		m_WallArr;
	PriceArr	m_PriceArr;
	FireArr		m_FireArr;

	Stick	m_Stick;

	void MoveAllBalls(int16 a_dT_mSec);
	void MoveAllPrices(int16 a_dT_mSec);
	void MoveAllFires(int16 a_dT_mSec);
	void GetThePrice(ePriceType a_eType, int8 a_x, int8 a_y);

	void MarkBricksOnMatrix();
	
	void ClearAllBricksBallsWalls();
	void AddLineOfBricks(int8 a_x0, int8 a_y0, int8 a_Count);
	void InitLevel(int8 a_Level);


private:
	void InitLeve_Clear();
};
#endif // #ifndef __BREAKS_H
