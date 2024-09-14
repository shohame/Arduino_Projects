#ifndef __UI_INPUT_H
#define __UI_INPUT_H

#define PIN_KEY_L	5
#define PIN_KEY_R	3
#define PIN_KEY_U	2
#define PIN_KEY_D	4


#define PIN_PLAYER_1	7
#define PIN_PLAYER_2	8


typedef struct stKeyStatus_name
{
	int8 m_L;	
	int8 m_R;
	int8 m_U;
	int8 m_D;
}stKeyStatus;

class UI_Input
{
public:
	UI_Input(void);
	~UI_Input(void);

	void GetKeyStatus(stKeyStatus* a_pKS_Player1, stKeyStatus* a_pKS_Player2);
};




#endif	//	#ifndef __UI_INPUT_H
