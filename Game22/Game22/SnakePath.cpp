#include "stdafx.h"
#include "General.h"

#include "SnakePath.h"



void SnakePath::Reset(void)
{ 
	m_Ps = { -1,-1 };
	m_Pe = { -1,-1 };
	m_Index = -2;
}

eDirection  SnakePath::GetDirection(stPoint a_P)
{
	if (a_P.m_X > m_Pe.m_X) return eDirR;
	if (a_P.m_X < m_Pe.m_X) return eDirL;
	if (a_P.m_Y > m_Pe.m_Y) return eDirD;
	if (a_P.m_Y < m_Pe.m_Y) return eDirU;
	return eDirNone;
}

void SnakePath::AddPoint(stPoint a_P)
{
	eDirection NewDirection;
	if (m_Index == -2)
{
		m_Ps = a_P;
		m_Pe = a_P;
		m_Index++;
		return;
	}

	NewDirection = GetDirection(a_P);
	
	if ( NewDirection == eDirNone )	
		return;
	
	if ( ((uint8)NewDirection != m_Path[m_Index].m_Dir) || (m_Index == -1) )
	{
		m_Index++;
		m_Path[m_Index].m_Dir = NewDirection;
		m_Path[m_Index].m_Len = 1;
	}
	else
	{
		m_Path[m_Index].m_Len++;
	}
	m_Pe = a_P;

}


void SnakePath::IterReset(void)
{
	m_IterIndex = -1; 
	m_IterPath.m_Dir = -1; 
	m_IterPath.m_Len = -1;
}

void SnakePath::IterUpdatePc(eDirection a_Dir)
{
	if (a_Dir == eDirR) 	m_IterPc.m_X--;
	if (a_Dir == eDirL) 	m_IterPc.m_X++;
	if (a_Dir == eDirD) 	m_IterPc.m_Y--;
	if (a_Dir == eDirU) 	m_IterPc.m_Y++;
}


int8 SnakePath::IterGetNext(stPoint *a_pP)
{
	if (m_IterIndex == -1)
	{
		m_IterPc = m_Pe;
		m_IterIndex = m_Index;
		m_IterPath = m_Path[m_IterIndex];

		*a_pP = m_IterPc;
	return 1;
}
	IterUpdatePc((eDirection)m_IterPath.m_Dir);
	
	m_IterPath.m_Len--;
	
	if (m_IterPath.m_Len == 0)
	{
		if (m_IterIndex==0)
		{
			return 0;
		}
		else
		{
			m_IterIndex--;
			m_IterPath = m_Path[m_IterIndex];
		}
	}
	*a_pP = m_IterPc;
}









