#ifndef __BOARD_MANAGER_H_
#define __BOARD_MANAGER_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Position.h"
#include "BoardConfiguration.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class Position;

enum class BoardType
{
	firstBoard,
	secondBoard
};

class BoardManager : public cocos2d::Layer
{
	BoardManager(BoardType boardType);

	BoardConfiguration*			m_boardConfig;
	BoardType					m_boardType;
	Node*						m_rootNode;
	Node*						m_centerContainer;
	Node*						m_boardLayout;
	vector<Position*>			m_positions;
	int							m_numberOfDiceForEachPlayer;
	int							m_numberOfPositions;
	int							m_numberOfEdges;

	virtual bool init(BoardType boardType);

	void setPositions();
	void assignConnectedPositionsForFirstBoard();
	void assignConnectedPositionsForSecondBoard();

	void setEdges();
	void createEdgesForFirstBoard();
	void createEdgesForSecondBoard();

public:
	static BoardManager* create(BoardType boardType);
	void startGame();
};

#endif // __BOARD_MANAGER_H_