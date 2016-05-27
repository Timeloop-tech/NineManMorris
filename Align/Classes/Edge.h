#ifndef __EDGE_H__
#define __EDGE_H__

#include "cocos2d.h"
#include "Position.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class Position;

class Edge
{
	ImageView*			m_imageView;
	bool				m_edgeHighlighted;
	vector<Position*>	m_edgeMembers;

	bool isAllEdgeMembersHasDice();

public:
	static int			m_numberOfEdgeMembers;
	bool				m_edgeFormed;

	Edge(ImageView* imageView);
	void assignEdgeMember(Position* position);

	bool isEdgeFormed();
	bool isEdgeHighlighted();

	void highlightEdge();
	void dehighlightEdge();
};

#endif // __EDGE_H__