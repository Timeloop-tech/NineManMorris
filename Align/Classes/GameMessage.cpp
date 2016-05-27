#include "GameMessage.h"

GameMessage::GameMessage()
{

}

GameMessage* GameMessage::createGameMessage(Node* parentContainer)
{
	GameMessage* msg = new GameMessage();
	if (msg && msg->init(parentContainer))
	{
		return msg;
	}
	return nullptr;
}

bool GameMessage::init(Node* parentContainer)
{
	m_msgBox = static_cast<TextBMFont*>(parentContainer->getChildByName("Message"));
	m_msgBox->setOpacity(0);	
	return true;
}

void GameMessage::showGameMessage(const std::string msg)
{
	m_msgBox->setString(msg);
	cocos2d::Vector<FiniteTimeAction*> actions;

	auto fadeIn = FadeIn::create(1.0f);
	actions.pushBack(fadeIn);

	auto delay = DelayTime::create(3.0f);
	actions.pushBack(delay);

	auto fadeOut = FadeOut::create(1.0f);
	actions.pushBack(fadeOut);

	//	auto callFunc = CallFunc::create(CC_CALLBACK_0(GameBoard::effectCompleted, this));
	//	actions.pushBack(callFunc);

	auto seq = Sequence::create(actions);
	
	m_msgBox->runAction(seq);
}