#ifndef __GAMEBOARD_SCENE_H__
#define __GAMEBOARD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Dice.h"
#include "Player.h"
#include "Position.h"
#include "GameMessage.h"
#include "BoardConfiguration.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class Player;
class Dice;
class Position;

enum class ClickSetting : int
{
	Position_ON_Dice_OFF = 0,
	Position_OFF_Dice_ON = 1,
	Position_ON_Dice_ON = 2,
	Position_OFF_Dice_OFF = 3
};

class GameBoard : public cocos2d::Layer 
{
	Node*				m_rootNode;
	Node*				m_centerContainer;
	vector<Player*>		m_players;
	vector<Position*>	m_positions;
	Position*			m_recentTouchedPosition;
	Dice*				m_recentTouchedDice;
	GameMessage*		m_message;
	int					m_numberOfDiceForEachPlayer;
	int					m_currentPlayerID;
	int					m_opponentPlayerID;
	int					m_totalFormedEdges;
	int					m_phaseOfGame;
	bool				m_clickOnDice;
	bool				m_clickOnPosition;
	bool				m_destinationsHighlighted;
	bool				m_lastDicePlaced;
	bool				m_firstTurn;
	static GameBoard*	m_instance;

	GameBoard(BoardConfiguration* boardConfig);
	static GameBoard* create(BoardConfiguration* boardConfig);
	virtual bool init(BoardConfiguration* boardConfig);

	void createDiceForPlayers();

	void removeDice();
	void chooseDiceToMove();
	void dehighlightDiceAndPosition();
	void goToSecondPhase();

	void changePlayerTurn();
	void setClickSetting(ClickSetting settings);

public:
	static cocos2d::Scene* createScene(BoardConfiguration* boardConfig);
	static GameBoard* getInstance();

	void positionTouch(Position* position);
	void diceTouch(Dice* dice);
};

#endif // __GAMEBOARD_SCENE_H__
