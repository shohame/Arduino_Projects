#ifndef __BREAKOUT_32X32_H
#define __BREAKOUT_32X32_H

void RestartGame();
void Setup();
void Loop();

#ifdef WIN32	
int32 Main(int32 argc, _TCHAR* argv[]);
#endif

#endif	//	#ifndef __BREAKOUT_32X32_H

