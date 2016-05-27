#ifndef _BOARD_CONFIGURATION_
#define _BOARD_CONFIGURATION_

#include <stdio.h>
#include "Position.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class Position;

struct BoardConfiguration
{
	Node*					parentContainer;
	Node*					centerContainer;
	int						numberOfDiceForEachPlayer;
	vector<Position*>		positions;
};

#endif // _BOARD_CONFIGURATION_
