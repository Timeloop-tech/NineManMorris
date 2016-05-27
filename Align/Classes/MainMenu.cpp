#include "MainMenu.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setKeypadEnabled(true);

	Node* rootNode = CSLoader::createNode("MainMenu.csb");
	this->addChild(rootNode);

	Node* centerContainer = static_cast<Node*>(rootNode->getChildByName("centerContainer"));

	m_buttonMenu = static_cast<Node*>(centerContainer->getChildByName("ButtonMenu"));
	m_boardMenu = static_cast<Layout*>(centerContainer->getChildByName("BoardMenu"));

	Button* playButton = static_cast<Button*>(m_buttonMenu->getChildByName("playButton"));
	Button* chooseBoardButton = static_cast<Button*>(m_buttonMenu->getChildByName("chooseBoardButton"));

	m_selectedBoard = BoardType::secondBoard;
	
	Layout* board_1 = static_cast<Layout*>(m_boardMenu->getChildByName("Board_1"));
	m_boards.push_back(board_1);

	Layout* board_2 = static_cast<Layout*>(m_boardMenu->getChildByName("Board_2"));
	m_boards.push_back(board_2);

	for (int i = 0; i < m_boards.size(); i++)
	{
		m_boards.at(i)->addTouchEventListener(CC_CALLBACK_2(MainMenu::newBoardClicked, this));
	}

	playButton->addTouchEventListener(CC_CALLBACK_1(MainMenu::playButtonClicked, this));
	chooseBoardButton->addTouchEventListener(CC_CALLBACK_2(MainMenu::chooseBoardButtonClicked, this));

	return true;
}

void MainMenu::playButtonClicked(Ref* pSender)
{
	BoardManager* boardManager = BoardManager::create(m_selectedBoard);
	boardManager->startGame();
}

void MainMenu::switchLayout(Node* layoutFrom, Node* layoutTo)
{
//	auto fadeIn = FadeIn::create(1.0f);
//	layoutTo->runAction(fadeIn);
	layoutTo->setVisible(true);

//	auto fadeOut = FadeOut::create(1.0f);
//	layoutFrom->runAction(fadeOut);
	layoutFrom->setVisible(false);
}

void MainMenu::chooseBoardButtonClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		switchLayout(m_buttonMenu, m_boardMenu);
	}
}

void MainMenu::newBoardClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		Layout* board = static_cast<Layout*>(pSender);

		for (int i = 0; i < m_boards.size(); i++)
		{
			if (m_boards.at(i) == board)
			{
				switch (i)
				{
				case 0:
					m_selectedBoard = BoardType::firstBoard;
					break;
				case 1:
					m_selectedBoard = BoardType::secondBoard;
					break;
				}
			}
		}
		switchLayout(m_boardMenu, m_buttonMenu);
	}
}