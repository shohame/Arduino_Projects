
#ifndef __GENERAL_H
#define __GENERAL_H

#define MAX_FRAME_TIME 150 // above MAX_FRAME_TIME it will slow the game (just for slow computers not Arduino)
#define DO_DEBUG true

#ifdef DO_DEBUG 
	#include <assert.h>
#endif

#include <math.h>
#include <time.h>

// Data types:
#ifdef WIN32
	typedef	signed		char		int8;
	typedef unsigned	char		uint8;
	typedef signed		short		int16;
	typedef unsigned	short		uint16;
	typedef signed		long		int32;
	typedef unsigned	long		uint32;
	typedef float					float32;
#else // Arduino
	typedef char				int8;
	typedef unsigned	char	uint8;
	typedef				    int		int16;
	typedef unsigned	int		uint16;
	typedef				    long	int32;
	typedef unsigned	long    uint32;
	typedef				    float	float32;

  extern void(* resetFunc) (void);

#endif

extern uint32 g_Tic;

// Includs:
#ifdef WIN32
	#include <Windows.h>
	#include <WinUser.h>
	#include <ctime>
#else // Arduino
  #include <Arduino.h>
  #include <avr/pgmspace.h>
#endif

// Macros:
#ifdef WIN32
	#define resetFunc() RestartGame()
	#define SERIAL_BEGIN(F)
	#define SERIAL_PRINT(F) 
	#define SERIAL_PRINTLN(F) 
	#define TIC_mS()   g_Tic = ((uint32)clock())
	#define TOC_mS()   ((uint32)((clock()-g_Tic)))
	#define DELAY(a) Sleep(a)
	#define PROGMEM
	#define pgm_read_word_near(A) (*A)
	#define RAND_INT(F,T) (( rand() % (T-F) ) + F)
	#define GET_RAMDOM_SEED()	srand((uint32)time(NULL))
#else
	//void resetFunc(void);
	#define SERIAL_BEGIN(F) Serial.begin(F)
	#define SERIAL_PRINT(F) Serial.print(F)
	#define SERIAL_PRINTLN(F) Serial.println(F)
	#define DELAY(a) delay(a)
	#define TIC_mS()   g_Tic=millis()
	#define TOC_mS()   (millis()-g_Tic)
	#define RAND_INT(min,max) random(min, max)
	#define GET_RAMDOM_SEED()		randomSeed(analogRead(0))
#endif

// Comon macros:
#define PI (3.14159265358979f)
#define ROUND_CORD_TO_U8(C) ((int8)floor(0.5f+C))
#define fSIGN(a) ( (a>=0.0f) ? 1.0f : -1.0f ) 
#define ABS(a) ( (a>0) ? (a) : (-a) ) 
#define POW2(a) (a*a)

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

#define RAD2DEG(a) (((float32)(a))*180.0f/PI)
#define DEG2RAD(a) (((float32)(a))*PI/180.0f)

// Comon structures:
typedef struct stVector_name
{
	float32 m_X;
	float32 m_Y;
}stVector;





#endif // #ifndef __GENERAL_H

