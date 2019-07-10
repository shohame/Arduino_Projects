#ifndef __FIRE_H
#define __FIRE_H

#define FIRE_DEFAULT_WIDTH		1
#define	FIRE_DEFAULT_HEIGHT		1
#define	FIRE_DEFAULT_SPEED		-10		// 3 Pixel / Sec


class Fire : public MovingBrick
{
public:

	Fire(void);
	~Fire(void);
	void Init();
	void Init(int8 a_x, int8 a_y, float32 a_Vx, float32 a_Vy);


};




#endif	//	#ifndef __FIRE_H


