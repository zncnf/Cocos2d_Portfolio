#pragma once
#include "cocos_framework.h"

class Item : public Scene
{
	int _buyGold;

public:
	Item();


	int getBuyGold() { return _buyGold; }
	int appendBuyGold(int gold) { _buyGold += gold; }
};