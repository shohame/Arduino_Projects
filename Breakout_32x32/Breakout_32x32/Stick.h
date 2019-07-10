#ifndef __STICK_H
#define __STICK_H


#define	STICK_DEFAULT_WIDTH		7
#define	STICK_DEFAULT_HEIGHT	1
#define	STICK_DEFAULT_X			13
#define	STICK_DEFAULT_Y			31

enum eStickType 
{
	eStickRegular,
	eStickLarge,
	eStickSmall,
	eStickFire
};



class Stick : public Brick
{
public:
	eStickType m_Type;
	Stick(void);
	void Init();

	~Stick(void);
	void MarkBrickOnMatrix(void);
	void ChangeStickType(eStickType a_StickType);
};


#endif	//	#ifndef __STICK_H

