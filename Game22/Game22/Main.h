#ifndef __Main_H
#define __Main_H

void RestartGame();
void Setup();
void Loop();

#ifdef WIN32	
int32 Main(int32 argc, _TCHAR* argv[]);
#endif

#endif	//	#ifndef __BREAKOUT_32X32_H

