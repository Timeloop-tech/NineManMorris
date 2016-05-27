#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Dice.h"

using namespace std;

class Dice;

class Player
{
	int					m_diceOnBoard;
	vector<Dice*>		m_dices;

public:
	Player();

	Dice* diceToPlaceOnBoard();
	void assignDice(Dice* dice);
	void removeDice(Dice* dice);

	int diceOnBoard();
	bool isAllDiceArePlaced();
	bool isAllDiceInEdge();
	bool isAllDiceAreBlocked();
	bool isPlayerInFlyingMode();
};

#endif // __PLAYER_H__