#include "BoardManager.h"
#include "cocos2d.h"
#include "Dice.h"
#include "Edge.h"
#include "GameBoard.h"

USING_NS_CC;

BoardManager::BoardManager(BoardType boardType)
	: m_boardType(boardType)
{
	m_boardConfig = new BoardConfiguration();
}
BoardManager* BoardManager::create(BoardType boardType)
{
	BoardManager* pRet = new BoardManager(boardType);
	if (pRet && pRet->init(boardType))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL; 
		return NULL; 
	}
}
bool BoardManager::init(BoardType boardType)
{
	// Common For all Boards..
	m_rootNode = CSLoader::createNode("GameBoard.csb");
	m_centerContainer = static_cast<Node*>(m_rootNode->getChildByName("centerContainer"));

	switch (boardType)
	{
		case BoardType::firstBoard:
			m_boardLayout = CSLoader::createNode("BoardLayout_1.csb");
			m_numberOfDiceForEachPlayer = 9;
			m_numberOfPositions = 26;
			m_numberOfEdges = 16;
			break;
		case BoardType::secondBoard:
			m_boardLayout = CSLoader::createNode("BoardLayout_2.csb");
			m_numberOfDiceForEachPlayer = 9;
			m_numberOfPositions = 24;
			m_numberOfEdges = 16;
			break;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_boardLayout->setPosition(Vec2(-visibleSize.width / 2 - origin.x, -visibleSize.height / 2 - origin.y));
	m_centerContainer->addChild(m_boardLayout);
	setPositions();
	setEdges();

	return true;
}

void BoardManager::setPositions()
{
	std::string ref_name;
	Value value;
	Node* positions = static_cast<Node*>(m_boardLayout->getChildByName("positions"));
	for (int i = 0; i < m_numberOfPositions; i++)
	{
		ref_name = "pos";
		value = i;
		ref_name.append(value.asString());
		m_positions.push_back(new Position(static_cast<ImageView*>(positions->getChildByName(ref_name))));
	}
	// assigning connected positions..
	switch (m_boardType)
	{
		case BoardType::firstBoard:
			assignConnectedPositionsForFirstBoard();
			break;
		case BoardType::secondBoard:
			assignConnectedPositionsForSecondBoard();
			break;
	}
}
void BoardManager::assignConnectedPositionsForFirstBoard()
{
	for (int i = 0; i < m_numberOfPositions; i++)
	{
		std::vector<Position*> connectedPosition;
		switch (i)
		{
		case 0:
			connectedPosition.push_back(m_positions.at(1));
			connectedPosition.push_back(m_positions.at(7));
			break;
		case 1:
			connectedPosition.push_back(m_positions.at(0));
			connectedPosition.push_back(m_positions.at(2));
			connectedPosition.push_back(m_positions.at(9));
			break;
		case 2:
			connectedPosition.push_back(m_positions.at(1));
			connectedPosition.push_back(m_positions.at(3));
			break;
		case 3:
			connectedPosition.push_back(m_positions.at(2));
			connectedPosition.push_back(m_positions.at(4));
			connectedPosition.push_back(m_positions.at(11));
			break;
		case 4:
			connectedPosition.push_back(m_positions.at(3));
			connectedPosition.push_back(m_positions.at(5));
			break;
		case 5:
			connectedPosition.push_back(m_positions.at(4));
			connectedPosition.push_back(m_positions.at(6));
			connectedPosition.push_back(m_positions.at(13));
			break;
		case 6:
			connectedPosition.push_back(m_positions.at(5));
			connectedPosition.push_back(m_positions.at(7));
			break;
		case 7:
			connectedPosition.push_back(m_positions.at(0));
			connectedPosition.push_back(m_positions.at(6));
			connectedPosition.push_back(m_positions.at(15));
			break;
		case 8:
			connectedPosition.push_back(m_positions.at(9));
			connectedPosition.push_back(m_positions.at(15));
			break;
		case 9:
			connectedPosition.push_back(m_positions.at(1));
			connectedPosition.push_back(m_positions.at(8));
			connectedPosition.push_back(m_positions.at(10));
			connectedPosition.push_back(m_positions.at(16));
			break;
		case 10:
			connectedPosition.push_back(m_positions.at(9));
			connectedPosition.push_back(m_positions.at(11));
			break;
		case 11:
			connectedPosition.push_back(m_positions.at(3));
			connectedPosition.push_back(m_positions.at(10));
			connectedPosition.push_back(m_positions.at(12));
			connectedPosition.push_back(m_positions.at(21));
			break;
		case 12:
			connectedPosition.push_back(m_positions.at(11));
			connectedPosition.push_back(m_positions.at(13));
			break;
		case 13:
			connectedPosition.push_back(m_positions.at(5));
			connectedPosition.push_back(m_positions.at(12));
			connectedPosition.push_back(m_positions.at(14));
			connectedPosition.push_back(m_positions.at(25));
			break;
		case 14:
			connectedPosition.push_back(m_positions.at(13));
			connectedPosition.push_back(m_positions.at(15));
			break;
		case 15:
			connectedPosition.push_back(m_positions.at(7));
			connectedPosition.push_back(m_positions.at(8));
			connectedPosition.push_back(m_positions.at(14));
			connectedPosition.push_back(m_positions.at(20));
			break;
		case 16:
			connectedPosition.push_back(m_positions.at(9));
			connectedPosition.push_back(m_positions.at(17));
			break;
		case 17:
			connectedPosition.push_back(m_positions.at(16));
			connectedPosition.push_back(m_positions.at(18));
			break;
		case 18:
			connectedPosition.push_back(m_positions.at(17));
			connectedPosition.push_back(m_positions.at(19));
			break;
		case 19:
			connectedPosition.push_back(m_positions.at(18));
			connectedPosition.push_back(m_positions.at(20));
			break;
		case 20:
			connectedPosition.push_back(m_positions.at(15));
			connectedPosition.push_back(m_positions.at(19));
			break;
		case 21:
			connectedPosition.push_back(m_positions.at(11));
			connectedPosition.push_back(m_positions.at(22));
			break;
		case 22:
			connectedPosition.push_back(m_positions.at(21));
			connectedPosition.push_back(m_positions.at(23));
			break;
		case 23:
			connectedPosition.push_back(m_positions.at(22));
			connectedPosition.push_back(m_positions.at(24));
			break;
		case 24:
			connectedPosition.push_back(m_positions.at(23));
			connectedPosition.push_back(m_positions.at(25));
			break;
		case 25:
			connectedPosition.push_back(m_positions.at(13));
			connectedPosition.push_back(m_positions.at(24));
			break;
		}
		m_positions.at(i)->assignConnectedPositions(connectedPosition);
	}
}
void BoardManager::assignConnectedPositionsForSecondBoard()
{
	for (int i = 0; i < m_numberOfPositions; i++)
	{
		std::vector<Position*> connectedPosition;
		switch (i)
		{
		case 0:
			connectedPosition.push_back(m_positions.at(1));
			connectedPosition.push_back(m_positions.at(9));
			break;
		case 1:
			connectedPosition.push_back(m_positions.at(0));
			connectedPosition.push_back(m_positions.at(2));
			connectedPosition.push_back(m_positions.at(4));
			break;
		case 2:
			connectedPosition.push_back(m_positions.at(1));
			connectedPosition.push_back(m_positions.at(14));
			break;
		case 3:
			connectedPosition.push_back(m_positions.at(4));
			connectedPosition.push_back(m_positions.at(10));
			break;
		case 4:
			connectedPosition.push_back(m_positions.at(1));
			connectedPosition.push_back(m_positions.at(3));
			connectedPosition.push_back(m_positions.at(5));
			connectedPosition.push_back(m_positions.at(7));
			break;
		case 5:
			connectedPosition.push_back(m_positions.at(4));
			connectedPosition.push_back(m_positions.at(13));
			break;
		case 6:
			connectedPosition.push_back(m_positions.at(7));
			connectedPosition.push_back(m_positions.at(11));
			break;
		case 7:
			connectedPosition.push_back(m_positions.at(4));
			connectedPosition.push_back(m_positions.at(6));
			connectedPosition.push_back(m_positions.at(8));
			break;
		case 8:
			connectedPosition.push_back(m_positions.at(7));
			connectedPosition.push_back(m_positions.at(12));
			break;
		case 9:
			connectedPosition.push_back(m_positions.at(0));
			connectedPosition.push_back(m_positions.at(10));
			connectedPosition.push_back(m_positions.at(21));
			break;
		case 10:
			connectedPosition.push_back(m_positions.at(3));
			connectedPosition.push_back(m_positions.at(9));
			connectedPosition.push_back(m_positions.at(11));
			connectedPosition.push_back(m_positions.at(18));
			break;
		case 11:
			connectedPosition.push_back(m_positions.at(6));
			connectedPosition.push_back(m_positions.at(10));
			connectedPosition.push_back(m_positions.at(15));
			break;
		case 12:
			connectedPosition.push_back(m_positions.at(8));
			connectedPosition.push_back(m_positions.at(13));
			connectedPosition.push_back(m_positions.at(17));
			break;
		case 13:
			connectedPosition.push_back(m_positions.at(5));
			connectedPosition.push_back(m_positions.at(12));
			connectedPosition.push_back(m_positions.at(14));
			connectedPosition.push_back(m_positions.at(20));
			break;
		case 14:
			connectedPosition.push_back(m_positions.at(2));
			connectedPosition.push_back(m_positions.at(13));
			connectedPosition.push_back(m_positions.at(23));
			break;
		case 15:
			connectedPosition.push_back(m_positions.at(11));
			connectedPosition.push_back(m_positions.at(16));
			break;
		case 16:
			connectedPosition.push_back(m_positions.at(15));
			connectedPosition.push_back(m_positions.at(17));
			connectedPosition.push_back(m_positions.at(19));
			break;
		case 17:
			connectedPosition.push_back(m_positions.at(12));
			connectedPosition.push_back(m_positions.at(16));
			break;
		case 18:
			connectedPosition.push_back(m_positions.at(10));
			connectedPosition.push_back(m_positions.at(19));
			break;
		case 19:
			connectedPosition.push_back(m_positions.at(16));
			connectedPosition.push_back(m_positions.at(18));
			connectedPosition.push_back(m_positions.at(20));
			connectedPosition.push_back(m_positions.at(22));
			break;
		case 20:
			connectedPosition.push_back(m_positions.at(13));
			connectedPosition.push_back(m_positions.at(19));
			break;
		case 21:
			connectedPosition.push_back(m_positions.at(9));
			connectedPosition.push_back(m_positions.at(22));
			break;
		case 22:
			connectedPosition.push_back(m_positions.at(19));
			connectedPosition.push_back(m_positions.at(21));
			connectedPosition.push_back(m_positions.at(23));
			break;
		case 23:
			connectedPosition.push_back(m_positions.at(14));
			connectedPosition.push_back(m_positions.at(22));
			break;
		}
		m_positions.at(i)->assignConnectedPositions(connectedPosition);
	}
}

void BoardManager::setEdges()
{
	Edge::m_numberOfEdgeMembers = 3;

	switch (m_boardType)
	{
		case BoardType::firstBoard:
			createEdgesForFirstBoard();
			break;
		case BoardType::secondBoard:
			createEdgesForSecondBoard();
			break;
	}

}
void BoardManager::createEdgesForFirstBoard()
{
	std::string ref_name;
	Value value;
	Node* connenctingEdges = static_cast<Node*>(m_boardLayout->getChildByName("connenctingEdges"));
	Position *pos0, *pos1, *pos2;
	for (int i = 0; i < m_numberOfEdges; i++)
	{
		ref_name = "connenctingEdge";
		value = i;
		ref_name.append(value.asString());
		Edge* edge = new Edge(static_cast<ImageView*>(connenctingEdges->getChildByName(ref_name)));
		switch (i)
		{
		case 0:
			pos0 = m_positions.at(0);
			pos1 = m_positions.at(1);
			pos2 = m_positions.at(2);
			break;
		case 1:
			pos0 = m_positions.at(2);
			pos1 = m_positions.at(3);
			pos2 = m_positions.at(4);
			break;
		case 2:
			pos0 = m_positions.at(4);
			pos1 = m_positions.at(5);
			pos2 = m_positions.at(6);
			break;
		case 3:
			pos0 = m_positions.at(6);
			pos1 = m_positions.at(7);
			pos2 = m_positions.at(0);
			break;
		case 4:
			pos0 = m_positions.at(8);
			pos1 = m_positions.at(9);
			pos2 = m_positions.at(10);
			break;
		case 5:
			pos0 = m_positions.at(10);
			pos1 = m_positions.at(11);
			pos2 = m_positions.at(12);
			break;
		case 6:
			pos0 = m_positions.at(12);
			pos1 = m_positions.at(13);
			pos2 = m_positions.at(14);
			break;
		case 7:
			pos0 = m_positions.at(14);
			pos1 = m_positions.at(15);
			pos2 = m_positions.at(8);
			break;
		case 8:
			pos0 = m_positions.at(16);
			pos1 = m_positions.at(17);
			pos2 = m_positions.at(18);
			break;
		case 9:
			pos0 = m_positions.at(18);
			pos1 = m_positions.at(19);
			pos2 = m_positions.at(20);
			break;
		case 10:
			pos0 = m_positions.at(21);
			pos1 = m_positions.at(22);
			pos2 = m_positions.at(23);
			break;
		case 11:
			pos0 = m_positions.at(23);
			pos1 = m_positions.at(24);
			pos2 = m_positions.at(25);
			break;
		case 12:
			pos0 = m_positions.at(1);
			pos1 = m_positions.at(9);
			pos2 = m_positions.at(16);
			break;
		case 13:
			pos0 = m_positions.at(3);
			pos1 = m_positions.at(11);
			pos2 = m_positions.at(21);
			break;
		case 14:
			pos0 = m_positions.at(25);
			pos1 = m_positions.at(13);
			pos2 = m_positions.at(5);
			break;
		case 15:
			pos0 = m_positions.at(20);
			pos1 = m_positions.at(15);
			pos2 = m_positions.at(7);
			break;
		}
		edge->assignEdgeMember(pos0);
		edge->assignEdgeMember(pos1);
		edge->assignEdgeMember(pos2);

		pos0->assignAssosiateEdge(edge);
		pos1->assignAssosiateEdge(edge);
		pos2->assignAssosiateEdge(edge);
	}
}
void BoardManager::createEdgesForSecondBoard()
{
	std::string ref_name;
	Value value;
	Node* connenctingEdges = static_cast<Node*>(m_boardLayout->getChildByName("connenctingEdges"));
	Position *pos0, *pos1, *pos2;
	for (int i = 0; i < m_numberOfEdges; i++)
	{
		ref_name = "connenctingEdge";
		value = i;
		ref_name.append(value.asString());
		Edge* edge = new Edge(static_cast<ImageView*>(connenctingEdges->getChildByName(ref_name)));
		switch (i)
		{
		case 0:
			pos0 = m_positions.at(0);
			pos1 = m_positions.at(1);
			pos2 = m_positions.at(2);
			break;
		case 1:
			pos0 = m_positions.at(3);
			pos1 = m_positions.at(4);
			pos2 = m_positions.at(5);
			break;
		case 2:
			pos0 = m_positions.at(6);
			pos1 = m_positions.at(7);
			pos2 = m_positions.at(8);
			break;
		case 3:
			pos0 = m_positions.at(9);
			pos1 = m_positions.at(10);
			pos2 = m_positions.at(11);
			break;
		case 4:
			pos0 = m_positions.at(12);
			pos1 = m_positions.at(13);
			pos2 = m_positions.at(14);
			break;
		case 5:
			pos0 = m_positions.at(15);
			pos1 = m_positions.at(16);
			pos2 = m_positions.at(17);
			break;
		case 6:
			pos0 = m_positions.at(18);
			pos1 = m_positions.at(19);
			pos2 = m_positions.at(20);
			break;
		case 7:
			pos0 = m_positions.at(21);
			pos1 = m_positions.at(22);
			pos2 = m_positions.at(23);
			break;
		case 8:
			pos0 = m_positions.at(0);
			pos1 = m_positions.at(9);
			pos2 = m_positions.at(21);
			break;
		case 9:
			pos0 = m_positions.at(3);
			pos1 = m_positions.at(10);
			pos2 = m_positions.at(18);
			break;
		case 10:
			pos0 = m_positions.at(6);
			pos1 = m_positions.at(11);
			pos2 = m_positions.at(15);
			break;
		case 11:
			pos0 = m_positions.at(16);
			pos1 = m_positions.at(19);
			pos2 = m_positions.at(22);
			break;
		case 12:
			pos0 = m_positions.at(1);
			pos1 = m_positions.at(4);
			pos2 = m_positions.at(7);
			break;
		case 13:
			pos0 = m_positions.at(8);
			pos1 = m_positions.at(12);
			pos2 = m_positions.at(17);
			break;
		case 14:
			pos0 = m_positions.at(5);
			pos1 = m_positions.at(13);
			pos2 = m_positions.at(20);
			break;
		case 15:
			pos0 = m_positions.at(2);
			pos1 = m_positions.at(14);
			pos2 = m_positions.at(23);
			break;
		}
		edge->assignEdgeMember(pos0);
		edge->assignEdgeMember(pos1);
		edge->assignEdgeMember(pos2);

		pos0->assignAssosiateEdge(edge);
		pos1->assignAssosiateEdge(edge);
		pos2->assignAssosiateEdge(edge);
	}
}

void BoardManager::startGame()
{
	m_boardConfig->parentContainer = m_rootNode;
	m_boardConfig->centerContainer = m_centerContainer;
	m_boardConfig->numberOfDiceForEachPlayer = m_numberOfDiceForEachPlayer;
	m_boardConfig->positions = m_positions;

	auto director = Director::getInstance();
	auto scene = GameBoard::createScene(m_boardConfig);
	director->replaceScene(scene);
}