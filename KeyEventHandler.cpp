#include "KeyEventHandler.h"
#include "GlobalDefine.h"
#include <dinput.h>
void KeyEventHandler::KeyState(BYTE* keyStates, PlayableCharacter* player)
{
	//TODO: create switch case for every action.
	
	if ((keyStates[DIK_LEFTARROW] & 0x80) > 0) {
		if ((keyStates[DIK_A] & 0x80)) {
			player->run(LEFT);
		}
		else {
			player->walk(LEFT);
		}
		

	}
	else {
		if ((keyStates[DIK_RIGHTARROW] & 0x80) > 0) {
			if ((keyStates[DIK_A] & 0x80)) {
				player->run(RIGHT);
			}
			else {
				player->walk(RIGHT);
			}
		}
		else {
			player->slowDown();
		}
	}
	
	
	//player->walk();
	//player->brake();
}

void KeyEventHandler::OnKeyUp(int KeyCode, PlayableCharacter* player)
{
	//TODO: create switch case for every action.
	switch (KeyCode) {
		case DIK_S:
			player->releaseJump();
			break;
		/*case DIK_A:
			player->slowDown();
			break;*/
	}
}
void KeyEventHandler::OnKeyDown(int KeyCode, PlayableCharacter* player)
{
	//TODO: create switch case for every action.
	switch (KeyCode) {
	case DIK_S:
		player->jump();
		break;
	case DIK_A:
		player->tryToAttack();
	case DIK_7:
		player->setPowerUplevel(SMALL);
		break;
	case DIK_8:
		player->setPowerUplevel(BIG);
		break;
	case DIK_9:
		player->setPowerUplevel(FIRE);
		break;
	case DIK_0:
		player->setPowerUplevel(TANUKI);
		break;
	/*case DIK_LEFTARROW:
		player->walk(LEFT);
		break;
	case DIK_RIGHTARROW:
		player->walk(RIGHT);
		break;*/
	}
	
	
	
}

