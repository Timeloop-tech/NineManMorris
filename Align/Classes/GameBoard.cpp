#include "GameBoard.h"
#include "cocos2d.h"
#include "BoardConfiguration.h"

USING_NS_CC;

GameBoard* GameBoard::m_instance{ nullptr };

GameBoard::GameBoard(BoardConfiguration* boardConfig)
	:	m_rootNode(boardConfig->parentContainer)
	,	m_centerContainer(boardConfig->centerContainer)
	,	m_numberOfDiceForEachPlayer(boardConfig->numberOfDiceForEachPlayer)
	,	m_positions(boardConfig->positions)
	,   m_message(GameMessage::createGameMessage(m_centerContainer))
	,	m_recentTouchedPosition(nullptr)
	,	m_recentTouchedDice(nullptr)
	,	m_currentPlayerID(0)
	,	m_opponentPlayerID(1)
	,	m_totalFormedEdges(0)
	,	m_phaseOfGame(1)
	,	m_destinationsHighlighted(false)
	,	m_lastDicePlaced(false)
	,	m_firstTurn(true)
{
		m_players.push_back(new Player());
		m_players.push_back(new Player());
		m_message->showGameMessage(PHASE_1_START);
}

Scene* GameBoard::createScene(BoardConfiguration* boardConfig)
{
	auto scene = Scene::create();
	auto layer = GameBoard::create(boardConfig);
	scene->addChild(layer);
	return scene;
}
GameBoard* GameBoard::create(BoardConfiguration* boardConfig)
{
	GameBoard* pRet = new(std::nothrow) GameBoard(boardConfig);
	if (pRet && pRet->init(boardConfig))
	{
		m_instance = pRet;
		pRet->autorelease();
		Position::setGameBoardInstance();
		Dice::setGameBoardInstance();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool GameBoard::init(BoardConfiguration* boardConfig)
{
	if (!Layer::init())
	{
		return false;
	}
	addChild(m_rootNode);
	createDiceForPlayers();
	setClickSetting(ClickSetting::Position_ON_Dice_OFF);
	setKeypadEnabled(true);
	return true;
}

GameBoard* GameBoard::getInstance()
{
	return m_instance;
}

void GameBoard::createDiceForPlayers()
{
	Vec2 pos;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Dice* dice = new Dice(0);
	Vec2 diceSize = dice->getSize();
	int distance = 1.2 * diceSize.y;
	int startFrom = distance * 4;
	delete dice;

	for (int i = 0; i < m_numberOfDiceForEachPlayer; i++)
	{
		Dice* dice = new Dice(0);
		pos = Vec2(-visibleSize.width / 2, startFrom - (i * distance));
		dice->setPosition(pos);
		dice->setSize(0.9);
		dice->placeInGameBoard(m_centerContainer);
		m_players.at(0)->assignDice(dice);
	}
	for (int i = 0; i < m_numberOfDiceForEachPlayer; i++)
	{
		Dice* dice = new Dice(1);
		Vec2 diceSize = dice->getSize();
		pos = Vec2(visibleSize.width / 2, startFrom - (i * distance));
		dice->setPosition(pos);
		dice->setSize(0.9);
		dice->placeInGameBoard(m_centerContainer);
		m_players.at(1)->assignDice(dice);
	}
}

void GameBoard::positionTouch(Position* position)
{
	if (m_clickOnPosition)
	{
		m_recentTouchedPosition = position;
		CCLOG("Position_touch_1");
		m_totalFormedEdges = 0;
		if (m_phaseOfGame == 1)
		{
			CCLOG("Position_touch_2");
			Dice* dice = m_players.at(m_currentPlayerID)->diceToPlaceOnBoard();
			m_recentTouchedPosition->setDiceOnPosition(dice);
			CCLOG("Position_touch_3");
		}
		else if (m_recentTouchedPosition->isHighlighted())
		{
			dehighlightDiceAndPosition();
			m_recentTouchedDice->moveToNewPosition();
			m_recentTouchedPosition->setDiceOnPosition(m_recentTouchedDice);
		}
		else
		{
			return;
		}
		CCLOG("Position_touch_4");
		m_totalFormedEdges = m_recentTouchedPosition->totalFormedEdges();
		CCLOG("Position_touch_5");

		if (m_totalFormedEdges > 0)
		{
			if (!m_players.at(m_opponentPlayerID)->isAllDiceInEdge())
			{
				m_message->showGameMessage(REMOVE_DICE_OF_OPPONENT);
				setClickSetting(ClickSetting::Position_OFF_Dice_ON);
			}
			else
			{
				m_message->showGameMessage(ALL_DICE_IN_EDGE);
				m_totalFormedEdges = 0;
				m_recentTouchedPosition->dehighlightAssosiateEdge();
				changePlayerTurn();
			}
		}
		else
		{
			if (m_firstTurn)
			{
				if (m_players.at(m_currentPlayerID)->diceOnBoard() == 2)
				{
					if (m_currentPlayerID == 1)
					{
						m_firstTurn = false;
					}
					changePlayerTurn();
				}
			}
			else
			{
				changePlayerTurn();
			}
			if (m_phaseOfGame == 2)
			{
				if (m_players.at(m_currentPlayerID)->isAllDiceAreBlocked())
				{
					if (!m_players.at(m_currentPlayerID)->isPlayerInFlyingMode())
					{
						m_message->showGameMessage(ALL_DICE_ARE_BLOCKED);
						setClickSetting(ClickSetting::Position_OFF_Dice_OFF);
					}
				}
			}
		}
		if (m_phaseOfGame == 1)
		{
			if (m_players.at(1)->isAllDiceArePlaced())
			{
				m_lastDicePlaced = true;

				if (m_totalFormedEdges == 0)
				{
					goToSecondPhase();
				}
			}
		}
	}
}
void GameBoard::diceTouch(Dice* dice)
{
	if (m_clickOnDice)
	{
		if (m_totalFormedEdges > 0)
		{
			m_recentTouchedDice = dice;
			removeDice();
		}
		else if (m_phaseOfGame == 2)
		{
			if (m_destinationsHighlighted)
			{
				dehighlightDiceAndPosition();
			}
			m_recentTouchedDice = dice;
			chooseDiceToMove();
		}
	}
}

void GameBoard::removeDice()
{
	if (m_recentTouchedDice->getPlayerID() == m_opponentPlayerID)
	{
		if (m_recentTouchedDice->isDiceOnBoard())
		{
			if (!m_recentTouchedDice->isDiceInEdge())
			{
				m_recentTouchedPosition->dehighlightAssosiateEdge();
				m_players.at(m_opponentPlayerID)->removeDice(m_recentTouchedDice);

				if (m_phaseOfGame == 2)
				{
					if (m_players.at(m_opponentPlayerID)->isPlayerInFlyingMode())
					{
						m_message->showGameMessage(FLYING_MODE_ACTIVE);
					}
					else if (m_players.at(m_opponentPlayerID)->diceOnBoard() < Edge::m_numberOfEdgeMembers)
					{
						m_message->showGameMessage(INSUFFIEINT_DICE);
						setClickSetting(ClickSetting::Position_OFF_Dice_OFF);
						return;
					}
				}
				if (m_totalFormedEdges == 2)
				{
					if (m_players.at(m_opponentPlayerID)->isAllDiceInEdge())
					{
						m_message->showGameMessage(CANT_REMOVE_SECOND_DICE);
						if (m_phaseOfGame == 1)
						{
							setClickSetting(ClickSetting::Position_ON_Dice_OFF);
						}
						else
						{
							setClickSetting(ClickSetting::Position_ON_Dice_ON);
						}
						changePlayerTurn();
					}
					else
					{
						m_message->showGameMessage(REMOVE_ONE_MORE);
						m_totalFormedEdges--;
					}
				}
				else
				{
					m_totalFormedEdges--;
					if (m_phaseOfGame == 1)
					{
						setClickSetting(ClickSetting::Position_ON_Dice_OFF);
					}
					else
					{
						setClickSetting(ClickSetting::Position_ON_Dice_ON);
					}
					changePlayerTurn();
				}
				if (m_lastDicePlaced)
				{
					if (m_totalFormedEdges == 0)
					{
						goToSecondPhase();
					}
				}
			}
			else
			{
				m_message->showGameMessage(DICE_IN_EDGE);
			}
		}
		else
		{
			m_message->showGameMessage(DICE_NOT_ON_BOARD);
		}
	}
	else
	{
		m_message->showGameMessage(WANT_TO_REMOVE_YOUR_OWN_DICE);
	}
}
void GameBoard::chooseDiceToMove()
{
	if (m_recentTouchedDice->getPlayerID() == m_currentPlayerID)
	{
		if (m_players.at(m_currentPlayerID)->isPlayerInFlyingMode())
		{
			m_recentTouchedDice->highlightDice();

			//highlight all vacant destinations.
			for (int i = 0; i < m_positions.size(); i++)
			{
				if (!m_positions.at(i)->hasDice())
				{
					m_positions.at(i)->highlightPosition();
				}
			}
			m_destinationsHighlighted = true;
		}
		else if (m_recentTouchedDice->highlightPossibleDestinations())
		{
			m_recentTouchedDice->highlightDice();
			m_destinationsHighlighted = true;
		}
	}
	else
	{
		// kindly choose your own dice.. not others..
	}
}
void GameBoard::dehighlightDiceAndPosition()
{
	m_recentTouchedDice->dehighlightDice();
	if (m_players.at(m_currentPlayerID)->isPlayerInFlyingMode())
	{
		for (int i = 0; i < m_positions.size(); i++)
		{
			if (!m_positions.at(i)->hasDice())
			{
				m_positions.at(i)->dehighlightPosition();
			}
		}
	}
	else
	{
		m_recentTouchedDice->dehighlightPossibleDestinations();
	}
	m_destinationsHighlighted = false;
}

void GameBoard::goToSecondPhase()
{
	m_phaseOfGame = 2;
	if (m_players.at(m_currentPlayerID)->isAllDiceAreBlocked())
	{
		m_message->showGameMessage(ALL_DICE_ARE_BLOCKED);
		setClickSetting(ClickSetting::Position_OFF_Dice_OFF);
	}
	else
	{
		m_message->showGameMessage(PHASE_2_START);
	}
	setClickSetting(ClickSetting::Position_ON_Dice_ON);
	m_lastDicePlaced = false;
}

void GameBoard::changePlayerTurn()
{
	int temp = m_currentPlayerID;
	m_currentPlayerID = m_opponentPlayerID;
	m_opponentPlayerID = temp;
}
void GameBoard::setClickSetting(ClickSetting settings)
{
	switch (settings)
	{
	case ClickSetting::Position_ON_Dice_OFF:
		m_clickOnPosition = true;
		m_clickOnDice = false;
		break;
	case ClickSetting::Position_OFF_Dice_ON:
		m_clickOnPosition = false;
		m_clickOnDice = true;
		break;
	case ClickSetting::Position_ON_Dice_ON:
		m_clickOnPosition = true;
		m_clickOnDice = true;
		break;
	case ClickSetting::Position_OFF_Dice_OFF:
		m_clickOnPosition = false;
		m_clickOnDice = false;
		break;
	}
}

/*
void GameBoard::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event event)
{

}
*/