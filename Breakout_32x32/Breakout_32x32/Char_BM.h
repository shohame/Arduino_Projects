
#ifndef __CHAR_BM_H
#define __CHAR_BM_H

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


#define CHAR_HEIGHT 5


// extern const  Line_Bit  CharBM_arr[][5] ;

#define _A_INDEX 0
#define _0_INDEX 26
#define _P_INDEX (_0_INDEX+10)
#define _UN_INDEX (_P_INDEX+5)


class Char_BM
{
public:
	int8  m_A_idx;
	int8  m_0_idx;
	int8  m_P_idx;
	int8  m_UN_idx;

	Char_BM(void);
	~Char_BM(void){};
	uint8 WriteStr(char a_Char[], int8 a_X, int8 a_Y);
	uint8 WriteChar(uint8 a_Char, int8 a_X, int8 a_Y);
	uint8 GetDigitOrLetterLine(uint8 a_Char, uint8 a_Line);
	uint8 GetDigitOrLetterWidth(uint8 a_Char);
	uint8 GetPriceLine(uint8 a_PriceIdx, uint8 a_Line); 



};

#endif //__CHAR_BM_H


