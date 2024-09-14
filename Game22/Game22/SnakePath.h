#ifndef __SNAKE_PATH_H
#define __SNAKE_PATH_H

#define SP_ARR_LEN	100

typedef struct  sPoint
{
	int8 m_X;
	int8 m_Y;
}stPoint;

class Path
{
public:
	uint8 m_Dir : 2;
	uint8 m_Len : 6;
};

class SnakePath
{
	stPoint		m_Ps; // starting point
	stPoint		m_Pe; // end point
	Path m_Path[SP_ARR_LEN];
	int16		m_Index;
	eDirection GetDirection(stPoint a_P);
public:
	void Reset() ;

	void	AddPoint(stPoint a_P);

	Path	m_IterPath;
	int16	m_IterIndex;
	stPoint	m_IterPc;

	void IterReset() ;
	int8 IterGetNext(stPoint *a_pP)	;
	void IterUpdatePc(eDirection a_Dir);
};







#endif // __SNAKE_PATH_H