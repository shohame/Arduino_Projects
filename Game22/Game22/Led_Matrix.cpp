#include "stdafx.h"
#include "General.h"
#include "LED_Matrix.h"


#ifdef WIN32
#else
	#include "LedControl_HW.h"
	#include "SPI.h"
	LedControl_HW lc=LedControl_HW(10,16);
#endif


int8 Matrix[N_Y][N_X/8];


void LM_Setup()
{
#ifdef WIN32
#else
/*	for(int8 M = 0; M < 4*(N_Y/8)*(N_X/8); M++)
	{
		lc.shutdown(M,true);
		lc.setIntensity(M,4);
		lc.clearDisplay(M);
	}
*/	
  DELAY(1000);
  lc.LC_ClearLeds_notLedStatus();
  lc.LC_ClearLedStatus();
  lc.LC_ClearLeds_notLedStatus();
	for(int8 M = 0; M < (N_Y/8)*(N_X/8); M++)
	{
		lc.shutdown(M,false);
		lc.setIntensity(M,4);
 	}
  lc.LC_ClearLeds_notLedStatus();
#endif
}

void LM_SetPoint(int8 a_x, int8 a_y, int8 a_Val)
{
	if ( a_y>=0 && a_y<N_Y && a_x>=0 && a_x<N_X)
	{
		int8 Xi, Xb;

		Xi = a_x/8;
		Xb = a_x%8;

		
		if (a_Val==0)
		{
			Matrix[a_y][Xi] &= ((1<<Xb)^0xff);
		}
		else
		{
			Matrix[a_y][Xi] |= (1<<Xb);
		}
	}
}

int8 LM_GetPoint(int8 a_x, int8 a_y)
{
	int8 Xi, Xb;
	Xi = a_x/8;
	Xb = a_x%8;

	return((Matrix[a_y][Xi]>>Xb)&1);
}

void LM_Clear()
{
	int8 x,y;

	for(y=0; y<N_Y; y++)
	{
		for(x=0; x<N_X; x++)
		{
			LM_SetPoint(x, y, 0);
		}
	}
}

void LM_CopyImage2Matrix(uint8 * a_pI)
{
  for(uint8 My = 0; My<4; My++)
  {
    for(uint8 L=0; L<8; L++)
    {
      for(uint8 Mx = 0; Mx<4; Mx++)
      {
        int16 Line = pgm_read_word_near(&a_pI[Mx+L*4+My*4*8]);
        for(uint8 P=0; P<8; P++)
        {  
			if ( (Line & (1<<P))  > 0)   
			{
				LM_SetPoint(Mx*8 + P, My*8 + L, 1 );      
			}
			else
			{
				LM_SetPoint(Mx*8 + P, My*8 + L, 0 );     
			}
        }
      }
    }
  }
}

#ifdef WIN32

void gotoxy(int16 x, int16 y)
{
	COORD pos = {x, y};
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hC, pos);
}



#include <iostream>

void LM_PC_DSP_Display_Matrix()
{
	int8 x,y;
	HANDLE hSTD = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(0,0);

	for(y=0; y<N_Y; y++)
	{
		for(x=0; x<N_X; x++)
		{
			if (LM_GetPoint(x, y))
			{
				SetConsoleTextAttribute(hSTD,(8<<4)+4);
				std::cout << "@";
				//printf("@");
			}
			else
			{
				SetConsoleTextAttribute(hSTD,(8<<4)+7);
				std::cout << "@"; 
				// printf("@");
			}
		}
		printf("\n");
	}
}
#else
void LM_PC_DSP_Display_Matrix()
{
	int8 x,y;

	
	for(y=0; y<N_Y; y++)
	{
		for(x=0; x<N_X; x++)
		{
			lc.LC_SetPoint_on_LedStatus(x, y, LM_GetPoint(x,y) );
		}
	}
	lc.LC_UpdateLeds();
}
#endif
