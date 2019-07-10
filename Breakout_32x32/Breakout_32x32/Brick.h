#ifndef __BREAK_H
#define __BREAK_H

#define NO_TOUCH	0
#define HORIZONTAL 	1
#define VERTICAL	2

typedef struct stLoc_name
{
	float32	m_X;
	float32	m_Y;
	int8	m_w;
	int8	m_h;
}stLoc;


#define	BREAK_DEFAULT_WIDTH		3
#define	BREAK_DEFAULT_HEIGHT	2

typedef struct sBrickTouchProp
{
	int8 m_isTouch;
	int8 m_Direction;
	float32 m_Depth;
	int8 m_dAngle; // just when ball hit the stick - to change the angle!
}stBrickTouchProp;



class Brick
{

public:
	stLoc m_Loc_s;	

	Brick(void);
	~Brick(void);

	void Init();
	void Init(int8 a_x, int8 a_y);
	void Init(int8 a_x, int8 a_y, int8 a_w, int8 a_h);

	void SetPos(int8 a_x, int8 a_y);
	void WhereBrickTouchMe (Brick * a_pBrick, stBrickTouchProp* a_pTouchProp);
	void SetLoc(int8 a_x, int8 a_y, int8 a_w, int8 a_h);

	void MarkBrickOnMatrix();

};

#endif	//	#ifndef __BREAK_H

