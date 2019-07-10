#ifndef __BALL_H
#define __BALL_H


#define	BALL_DEFAULT_WIDTH	2
#define	BALL_DEFAULT_HEIGHT	2
#define	BALL_DEFAULT_ACCSELERATION	30  // mili Percent / Sec

#define MAX_ANGLE (75)


class Ball : public MovingBrick
{
public:
	Ball(void);
	~Ball(void);

	void Init();
	void Init(int8 a_x, int8 a_y, float32 a_Vx, float32 a_Vy);

	int8 FindBallCollision(Brick a_Brick_arr[], int8 a_BrickCount);
	int8 Where_I_TouchStick (Brick * a_pBrick);



};

#endif // #ifndef __BALL_H