#include "Position.h"
#include "cocos2d.h"

USING_NS_CC;

GameBoard* Position::m_gameBoardInstance{ nullptr };

Position::Position(ImageView* imgView)
	:	m_imageView(imgView)
	,	m_diceOnPosition(nullptr)
	,	m_highlighted(false)
{
	m_imageView->setTouchEnabled(true);
	m_imageView->addTouchEventListener(CC_CALLBACK_2(Position::positionTouched, this));
}

void Position::positionTouched(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		m_gameBoardInstance->positionTouch(this);
	}
}

void Position::assignAssosiateEdge(Edge* edge)
{
	m_assosiateEdges.push_back(edge);
}
void Position::assignConnectedPositions(vector<Position*> connectedPositions)
{
	m_connectedPositions = connectedPositions;
}

void Position::setGameBoardInstance()
{
	m_gameBoardInstance = GameBoard::getInstance();
}
void Position::setDiceOnPosition(Dice* dice)
{
	Vec2 pos = m_imageView->getPosition();
	m_imageView->setTouchEnabled(false);
	m_diceOnPosition = dice;
	dice->setCurrentPosition(this);
	dice->setPosition(pos);
}
void Position::makePositionVacant()
{
	for (int i = 0; i < m_assosiateEdges.size(); i++)
	{
		m_assosiateEdges.at(i)->m_edgeFormed = false;
	}
	m_diceOnPosition = nullptr;
	m_imageView->setTouchEnabled(true);
}

bool Position::hasDice()
{
	if (m_diceOnPosition == nullptr)
	{
		return false;
	}
	return true;
}
bool Position::isHighlighted()
{
	return m_highlighted;
}
bool Position::isPositionInEdge()
{
	for (int i = 0; i < m_assosiateEdges.size(); i++)
	{
		if (m_assosiateEdges.at(i)->m_edgeFormed)
		{
			return true;
		}
	}
	return false;
}
bool Position::isAllConnectedPositionHasDice()
{
	for (int i = 0; i < m_connectedPositions.size(); i++)
	{
		if (!m_connectedPositions.at(i)->hasDice())
		{
			return false;
		}
	}
	return true;
}
int Position::getCurrentPlayerID()
{
	return m_diceOnPosition->getPlayerID();
}
int Position::totalFormedEdges()
{
	int edges = 0;

	for (int i = 0; i < m_assosiateEdges.size(); i++)
	{
		if (m_assosiateEdges.at(i)->isEdgeFormed())
		{
			edges++;
		}
	}

	return edges;
}

void Position::highlightPosition()
{
	m_highlighted = true;
	m_imageView->setColor(GameColors::m_HighlightColor);
}
void Position::dehighlightPosition()
{
	m_highlighted = false;
	m_imageView->setColor(GameColors::m_PositionColor);
}
bool Position::highlightVacantConnectedPositions()
{
	bool retValue = false;
	for (int i = 0; i < m_connectedPositions.size(); i++)
	{
		if (!m_connectedPositions.at(i)->hasDice())
		{
			m_connectedPositions.at(i)->highlightPosition();
			retValue = true;
		}
	}
	return retValue;
}
void Position::dehighlightConnectedPositions()
{
	for (int i = 0; i < m_connectedPositions.size(); i++)
	{
		m_connectedPositions.at(i)->dehighlightPosition();
	}
}
void Position::dehighlightAssosiateEdge()
{
	for (int i = 0; i < m_assosiateEdges.size(); i++)
	{
		if (m_assosiateEdges.at(i)->isEdgeHighlighted())
		{
			m_assosiateEdges.at(i)->dehighlightEdge();
			return;
		}
	}
}
