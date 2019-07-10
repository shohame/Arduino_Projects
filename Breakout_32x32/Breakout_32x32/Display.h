#ifndef __SCORE_H
#define __SCORE_H

#define NUM_OF_PRICE 5
#define NUM_OF_DIG	(10 + NUM_OF_PRICE)
#define DIG_WIDTH	3
#define DIG_HEIGHT	5

typedef struct Line_Bit
{
	int8 b0:1;
	int8 b1:1;
	int8 b2:1;
	int8 b3:1;
	int8 b4:1;
	int8 b5:1;
	int8 b6:1;
	int8 b7:1;

}Line_Bit;

extern const  Line_Bit  Digit_arr[NUM_OF_DIG][DIG_HEIGHT] ;

class Display
{
public:
	Display(void);
	~Display(void);

	uint32 m_Score;
	uint32 m_LastDispScore;
	int16  m_Sum_dT;

	int8 m_Life;

	void AddScore(int32 a_Value);
	void ResetGame(void);
	void MarkOnMatrix(int16 a_dT);


	int8 MarkCharOnMatrix(int8 a_CharIdx, int8 a_X0, int8 a_Y0); // return X1 for the next letter (include space)

};






#endif // #ifndef __SCORE_H




