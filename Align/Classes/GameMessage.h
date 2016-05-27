#ifndef __GAME_MESSAGE_HPP__
#define __GAME_MESSAGE_HPP__

#define PHASE_1_START "PHASE 1: place your DICE turn by turn on vacant POSITIONS."
#define WANT_TO_REMOVE_YOUR_OWN_DICE "You have to remove DICE of opponent not your own."
#define DICE_IN_EDGE "This DICE is in EDGE, You can't remove it."
#define DICE_NOT_ON_BOARD "This DICE is NOT yet placed on board."
#define REMOVE_DICE_OF_OPPONENT "Great! Now Remove DICE of an opponent player."
#define CANT_REMOVE_SECOND_DICE "You can't remove second DICE, as remaining all DICES are in Edge."
#define REMOVE_ONE_MORE "Remove one more DICE."
#define PHASE_2_START "PHASE 2: Now select your DICE to move it to an adjacent POSITION."
#define FLYING_MODE_ACTIVE "You are in FLYING mode now onwards."
#define ALL_DICE_IN_EDGE "All DICES of opponent is in EDGE."
#define ALL_DICE_ARE_BLOCKED "Not even single DICE is able to MOVE."
#define INSUFFIEINT_DICE "No suffient DICE are remains to form a EDGE."

#include "stdio.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class GameMessage
{
	TextBMFont*		m_msgBox;

	GameMessage();

	virtual bool init(Node* parentContainer);

public:
	static GameMessage* createGameMessage(Node* parentContainer);
	void showGameMessage(const std::string msg);
};

#endif // __GAME_Message_HPP__