#include "Player.h"
#include "cocos2d.h"

USING_NS_CC;

Player::Player()
	:	m_diceOnBoard(0)
{
}

Dice* Player::diceToPlaceOnBoard()
{
	CCLOG("Ask player for a dice");
	m_diceOnBoard++;
	if (m_dices.at(m_diceOnBoard - 1) != nullptr)
		CCLOG("Player returns dice");
	return m_dices.at(m_diceOnBoard - 1);
} 
void Player::assignDice(Dice* dice)
{
	m_dices.push_back(dice);
}
void Player::removeDice(Dice* dice)
{
	for (int i = 0; i < m_diceOnBoard; i++)
	{
		if (m_dices.at(i) == dice)
		{
			m_diceOnBoard--;
			dice->moveToNewPosition();
			m_dices.erase(m_dices.begin() + i);
			delete dice;
			dice = nullptr;
		}
	}
}

int Player::diceOnBoard()
{
	return m_diceOnBoard;
}
bool Player::isAllDiceArePlaced()
{
	if (m_dices.size() == m_diceOnBoard)
	{
		return true;
	}
	return false;
}
bool Player::isAllDiceInEdge()
{
	for (int i = 0; i < m_diceOnBoard; i++)
	{
		if (!m_dices.at(i)->isDiceInEdge())
		{
			return false;
		}
	}
	return true;
}
bool Player::isAllDiceAreBlocked()
{
	if (m_diceOnBoard == 0)
	{
		return false;
	}
	for (int i = 0; i < m_diceOnBoard; i++)
	{
		if (!m_dices.at(i)->isDiceIsBlocked())
		{
			return false;
		}
	}
	return true;
}
bool Player::isPlayerInFlyingMode()
{
	if (m_diceOnBoard == Edge::m_numberOfEdgeMembers)
	{
		return true;
	}
	return false;
}