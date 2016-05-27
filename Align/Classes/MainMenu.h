#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "BoardManager.h"

using namespace cocos2d;
using namespace std;

class MainMenu : public cocos2d::Layer
{
	BoardType			m_selectedBoard;
	vector<Layout*>		m_boards;
	Node*				m_buttonMenu;
	Layout*				m_boardMenu;

	virtual bool init();
	void playButtonClicked(Ref* pSender);
	void chooseBoardButtonClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void newBoardClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void switchLayout(Node* layoutFrom, Node* layoutTo);
	CREATE_FUNC(MainMenu);

public:
	static cocos2d::Scene* createScene();
};
#endif // __MAIN_MENU_H__