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
	Path m_Path[SP_ARR_LEN];
	int16		m_Index;

	void Reset() ;

	void AddPoint(int8 a_Direction);

	Path	m_IterPath;
	int16	m_IterIndex;

	void IterReset() ;
	int8 IterGetNext(stPoint *a_pP)	;
};







#endif // __SNAKE_PATH_H