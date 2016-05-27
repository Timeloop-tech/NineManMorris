#include "Edge.h"
#include "cocos2d.h"
#include "GameColors.h"

USING_NS_CC;

int Edge::m_numberOfEdgeMembers{ 0 };

Edge::Edge(ImageView* imageView)
	: m_imageView(imageView)
{
	m_edgeFormed = false;
	m_edgeHighlighted = false;
}

void Edge::assignEdgeMember(Position* position)
{
	this->m_edgeMembers.push_back(position);
}

bool Edge::isEdgeFormed()
{
	if (isAllEdgeMembersHasDice())
	{
		int a = m_edgeMembers.at(0)->getCurrentPlayerID();
		int b = m_edgeMembers.at(1)->getCurrentPlayerID();
		int c = m_edgeMembers.at(2)->getCurrentPlayerID();

		if (a == b && b == c)
		{
			highlightEdge();
			m_edgeFormed = true;
			return true;
		}		
	}
	return false;
}
bool Edge::isAllEdgeMembersHasDice()
{
	for (int i = 0; i < 3; i++)
	{
		if (!m_edgeMembers.at(i)->hasDice())
		{
			return false;
		}
	}
	return true;
}
bool Edge::isEdgeHighlighted()
{
	return m_edgeHighlighted;
}

void Edge::highlightEdge()
{
	m_edgeHighlighted = true;
	for (int i = 0; i < 3; i++)
	{
		m_edgeMembers.at(i)->highlightPosition();
	}
	m_imageView->setColor(GameColors::m_HighlightColor);
}
void Edge::dehighlightEdge()
{
	m_edgeHighlighted = false;
	for (int i = 0; i < 3; i++)
	{
		m_edgeMembers.at(i)->dehighlightPosition();
	}
	m_imageView->setColor(GameColors::m_EdgeColor);
}
