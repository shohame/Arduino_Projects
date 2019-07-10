#ifndef __BREAK_ARR_TEMP_H
#define __BREAK_ARR_TEMP_H


template <class T, int8 MAX_COUNT>
class BrickArrTemp
{
public:
	int8	m_MaxCount;	
	int8	m_Count;
	T		m_Brick_a[MAX_COUNT];
	int8	m_IterIdx;

	BrickArrTemp()
	{
		m_MaxCount = MAX_COUNT;
		m_Count = 0;
	}

	~BrickArrTemp(){}

	void ClearAll()
	{
		m_Count = 0;
		m_IterIdx = 0;
	}

	void Add()
	{
		if (m_Count<m_MaxCount)
		{
			m_Brick_a[m_Count].Init();
			m_Count++;
		}
	}

	void Add(int8 a_x, int8 a_y)
	{
		if (m_Count<m_MaxCount)
		{
			m_Brick_a[m_Count].Init(a_x,   a_y);
			m_Count++;
		}
	}

	void Add(int8 a_x, int8 a_y, float32 a_Vx, float32 a_Vy)
	{
		if (m_Count<m_MaxCount)
		{
			m_Brick_a[m_Count].Init(a_x, a_y, a_Vx, a_Vy);
			m_Count++;
		}
	}

	void Add(int8 a_x, int8 a_y, int8 a_w, int8 a_h)
	{
		if (m_Count<m_MaxCount)
		{
			m_Brick_a[m_Count].Init(a_x, a_y,  a_w,  a_h);
			m_Count++;
		}
	}

	void Add(int8 a_x, int8 a_y, ePriceType a_Type)
	{
		if (m_Count<m_MaxCount)
		{
			m_Brick_a[m_Count].Init(a_x, a_y,  a_Type);
			m_Count++;
		}
	}

	void Remove(uint8 a_BrickIdx)
	{
		if ( (a_BrickIdx >= 0) && (a_BrickIdx < m_Count) )
		{
			m_Brick_a[a_BrickIdx] = m_Brick_a[m_Count-1];
			m_Count--;

		}
	}

	void MarkBrickArrOnMatrix()
	{
		T* pBrick;

		IterBegin();
		while((pBrick = IterNext()) != NULL)
		{
			pBrick->MarkBrickOnMatrix();
		}
	}


	void IterBegin()
	{
		m_IterIdx = m_Count;
	}

	T* IterNext()
	{
		if (m_IterIdx>0)
		{
			m_IterIdx--;
			return(&m_Brick_a[m_IterIdx]);
		}
		else
		{
			return(NULL);
		}
	}

	void IterRemove()
	{
		Remove(m_IterIdx);
	}

};

#endif	//	#ifndef __BREAK_H

