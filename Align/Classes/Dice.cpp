#include "Dice.h"
#include "cocos2d.h"
#include "GameColors.h"

USING_NS_CC;

GameBoard* Dice::m_gameBoardInstance{ nullptr };

Dice::Dice(int playerID)
	: m_imageView(ImageView::create("images/elipse.png"))
	, m_currentPosition(nullptr)
	, m_diceOnBoard(false)
	, m_playerID(playerID)
{
	m_imageView->setTouchEnabled(true);
	m_imageView->addTouchEventListener(CC_CALLBACK_2(Dice::diceTouched, this));
	if (m_playerID == 0)
	{
		m_imageView->setColor(GameColors::m_player_1_DiceColor);
	}
	else
	{
		m_imageView->setColor(GameColors::m_player_2_DiceColor);
	}
}
Dice::~Dice()
{
	m_imageView->removeFromParent();
}

void Dice::diceTouched(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		m_gameBoardInstance->diceTouch(this);
	}
}
void Dice::moveDice(Vec2 position)
{
	auto moveTo = MoveTo::create(0.3f, position);
	m_imageView->runAction(moveTo);
}

void Dice::placeInGameBoard(Node* parent)
{
	parent->addChild(m_imageView);
}

void Dice::setGameBoardInstance()
{
	m_gameBoardInstance = GameBoard::getInstance();
}
void Dice::setCurrentPosition(Position* position)
{
	m_diceOnBoard = true;
	m_currentPosition = position;
}
void Dice::setPosition(Vec2 position)
{
	m_imageView->setPosition(position);
//	moveDice(position);
}
void Dice::moveToNewPosition()
{
	m_currentPosition->makePositionVacant();
}

Vec2 Dice::getSize()
{
	return m_imageView->getContentSize();
}
void Dice::setSize(float size)
{
	m_imageView->setScale(size);
}

int Dice::getPlayerID()
{
	return m_playerID;
}
bool Dice::isDiceInEdge()
{
	return m_currentPosition->isPositionInEdge();
}
bool Dice::isDiceIsBlocked()
{
	return m_currentPosition->isAllConnectedPositionHasDice();
}
bool Dice::isDiceOnBoard()
{
	return m_diceOnBoard;
}

void Dice::highlightDice()
{
	m_imageView->setColor(GameColors::m_DiceHighlightColor);
}
void Dice::dehighlightDice()
{
	if (m_playerID == 0)
	{
		m_imageView->setColor(GameColors::m_player_1_DiceColor);
	}
	else
	{
		m_imageView->setColor(GameColors::m_player_2_DiceColor);
	}
}
bool Dice::highlightPossibleDestinations()
{
	return m_currentPosition->highlightVacantConnectedPositions();
}
void Dice::dehighlightPossibleDestinations()
{
	m_currentPosition->dehighlightConnectedPositions();
}
