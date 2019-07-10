

#include "stdafx.h"

#include "General.h"

uint32 g_Tic;

#ifdef WIN32

#else
	void(* resetFunc) (void) = 0; //declare reset function @ address 0
#endif
