#include "stdafx.h"

#include "General.h"
#include "Led_Matrix.h"
#include "Globe.h"

const uint8 g_LedStatus[50][16 * 8] PROGMEM = 
		#include "Globe_Data.h" 


void CopyImage2LedStatus(uint8 * a_pI)
{
	for(uint8 My = 0; My<4; My++)
	{
		for(uint8 L=0; L<8; L++)
		{
			for(uint8 Mx = 0; Mx<4; Mx++)
			{
				uint8 Line = pgm_read_word_near(&a_pI[Mx+L*4+My*4*8]);
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

void Draw_Globe()
{
	int16 i,j;
	LM_PC_DSP_Display_Matrix();


	DELAY(1000);
	for(j=0; j<2; j++)
	{
		for (i=0; i<50; i++)
		{
			CopyImage2LedStatus((uint8*)g_LedStatus[i]);
			LM_PC_DSP_Display_Matrix();
			DELAY(50);
		}
	}
}





