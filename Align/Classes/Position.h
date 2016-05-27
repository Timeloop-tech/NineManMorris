#ifndef __POSITION_H__
#define __POSITION_H__

#include "cocos2d.h"
#include "Dice.h"
#include "Edge.h"
#include "GameColors.h"
#include "GameBoard.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class Dice;

class Edge;

class GameBoard;

class Position
{
	ImageView*				m_imageView;
	Dice*					m_diceOnPosition;
	vector<Position*>		m_connectedPositions;
	vector<Edge*>			m_assosiateEdges;
	bool					m_highlighted;
	static GameBoard*		m_gameBoardInstance;

	void positionTouched(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

public:

	Position(ImageView* imgView);

	void assignAssosiateEdge(Edge* edge);
	void assignConnectedPositions(vector<Position*> connectedPositions);

	static void setGameBoardInstance();
	void setDiceOnPosition(Dice* dice);
	void makePositionVacant();

	bool hasDice();
	bool isHighlighted();
	bool isPositionInEdge();
	bool isAllConnectedPositionHasDice();
	int getCurrentPlayerID();
	int totalFormedEdges();

	void highlightPosition();
	void dehighlightPosition();
	bool highlightVacantConnectedPositions();
	void dehighlightConnectedPositions();
	void dehighlightAssosiateEdge();
};

#endif // __POSITION_H__