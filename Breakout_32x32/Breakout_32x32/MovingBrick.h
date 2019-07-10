#ifndef __MOVING_BRICK_H
#define __MOVING_BRICK_H


//#define	BALL_DEFAULT_WIDTH	2
//#define	BALL_DEFAULT_HEIGHT	2
//#define	BALL_DEFAULT_ACCSELERATION	30  // mili Percent / Sec

#define MAX_ANGLE (75)

#define	eMB_Unknow	 0
#define	eMB_Ball	 1
#define	eMB_Fire	 2
#define	eMB_Price	 3


class MovingBrick : public Brick
{
public:
	void Init(int8 a_x, int8 a_y, float32 a_Vx, float32 a_Vy);

	uint8 m_MB_Type;
	stVector   m_V_s;		// velocity
	int8 m_Acceleration;	// +10 percent for each 100 sec 

	void Move(int16 a_dT_mSec);
	void SetSpeed(stVector* a_pV);
	void SetSpeed(float32 a_Vx, float32 a_Vy);

	int8 FindCollision(Brick a_Brick_arr[], int8 a_BrickCount, stBrickTouchProp* a_pTouchPr);
	void ChangeAngleBy(float32 a_dAngle);
	void Bounce(int8 a_Direction, float32 a_Depth );



};

#endif // #ifndef __BALL_H
