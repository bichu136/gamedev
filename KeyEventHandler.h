#pragma once
#include"PlayableCharacter.h"
//this class will change playable state.
class KeyEventHandler
{
public:
	void KeyState(BYTE* keyStates, PlayableCharacter* player);
	void OnKeyUp(int KeyCode, PlayableCharacter* player);
	void OnKeyDown(int KeyCode, PlayableCharacter* player);
};

