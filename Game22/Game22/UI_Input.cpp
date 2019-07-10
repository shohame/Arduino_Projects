#include "stdafx.h"
#include "General.h"
#include "UI_Input.h"

UI_Input::UI_Input(void)
{
#ifndef WIN32
	pinMode(PIN_KEY_L, INPUT_PULLUP);
	pinMode(PIN_KEY_R, INPUT_PULLUP);
	pinMode(PIN_KEY_U, INPUT_PULLUP);
	pinMode(PIN_KEY_D, INPUT_PULLUP);

	pinMode(PIN_PLAYER_1, OUTPUT);
	pinMode(PIN_PLAYER_2, OUTPUT);

	digitalWrite(PIN_PLAYER_1, 1);
	digitalWrite(PIN_PLAYER_2, 1);
#endif
}


UI_Input::~UI_Input(void)
{
}

#ifdef WIN32
void UI_Input::GetKeyStatus(stKeyStatus* a_pKS_Player1, stKeyStatus* a_pKS_Player2)
{
	a_pKS_Player1->m_L = GetAsyncKeyState(VK_LEFT)		?	1 : 0;
	a_pKS_Player1->m_R = GetAsyncKeyState(VK_RIGHT)		?	1 : 0;
	a_pKS_Player1->m_U = GetAsyncKeyState(VK_UP)		?	1 : 0;
	a_pKS_Player1->m_D = GetAsyncKeyState(VK_DOWN)		?	1 : 0;
	a_pKS_Player2->m_L = GetAsyncKeyState('a' + 0x41 - 'a')			?	1 : 0; 
	a_pKS_Player2->m_R = GetAsyncKeyState('d' + 0x41 - 'a')			?	1 : 0; 
	a_pKS_Player2->m_U = GetAsyncKeyState('w' + 0x41 - 'a')			?	1 : 0;
	a_pKS_Player2->m_D = GetAsyncKeyState('s' + 0x41 - 'a')			?	1 : 0;	
}
#else

void GetKeyStatus_sub(stKeyStatus* a_pKS_Player)
{
	a_pKS_Player->m_L = !digitalRead(PIN_KEY_L);
	a_pKS_Player->m_R = !digitalRead(PIN_KEY_R);
	a_pKS_Player->m_U = !digitalRead(PIN_KEY_U);
	a_pKS_Player->m_D = !digitalRead(PIN_KEY_D);
}

void GetKeyStatus_Debug(stKeyStatus* a_pKS_Player1, stKeyStatus* a_pKS_Player2)
{
#if DO_DEBUG

	SERIAL_PRINT("Player 1: ");
	
	if (a_pKS_Player1->m_L) SERIAL_PRINT("L");
	if (a_pKS_Player1->m_R) SERIAL_PRINT("R");
	if (a_pKS_Player1->m_U) SERIAL_PRINT("U");
	if (a_pKS_Player1->m_D) SERIAL_PRINT("D");
	SERIAL_PRINTLN();

	SERIAL_PRINT("Player 2: ");

	if (a_pKS_Player2->m_L) SERIAL_PRINT("L");
	if (a_pKS_Player2->m_R) SERIAL_PRINT("R");
	if (a_pKS_Player2->m_U) SERIAL_PRINT("U");
	if (a_pKS_Player2->m_D) SERIAL_PRINT("D");

	SERIAL_PRINTLN();
#endif
}

void UI_Input::GetKeyStatus(stKeyStatus* a_pKS_Player1, stKeyStatus* a_pKS_Player2)
{
	digitalWrite(PIN_PLAYER_1, 0);
	digitalWrite(PIN_PLAYER_2, 1);

	GetKeyStatus_sub(a_pKS_Player1);

	digitalWrite(PIN_PLAYER_1, 1);
	digitalWrite(PIN_PLAYER_2, 0);

	GetKeyStatus_sub(a_pKS_Player2);

	digitalWrite(PIN_PLAYER_1, 1);
	digitalWrite(PIN_PLAYER_2, 1);

	GetKeyStatus_Debug(a_pKS_Player1, a_pKS_Player2);

}
#endif
