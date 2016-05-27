#ifndef __DICE_H__
#define __DICE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Position.h"
#include "GameBoard.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class Position;

class GameBoard;

class Dice
{
	ImageView*			m_imageView;
	Position*			m_currentPosition;
	bool				m_diceOnBoard;
	int					m_playerID;
	static GameBoard*	m_gameBoardInstance;

	void diceTouched(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void moveDice(Vec2 position);

public:

	Dice(int playerID);
	~Dice();

	void placeInGameBoard(Node* parent);

	static void setGameBoardInstance();
	void setCurrentPosition(Position* position);
	void setPosition(Vec2 position);
	void moveToNewPosition();

	Vec2 getSize();
	void setSize(float size);

	int getPlayerID();
	bool isDiceInEdge();
	bool isDiceIsBlocked();
	bool isDiceOnBoard();

	void highlightDice();
	void dehighlightDice();
	bool highlightPossibleDestinations();
	void dehighlightPossibleDestinations();
};

#endif // __DICE_H__