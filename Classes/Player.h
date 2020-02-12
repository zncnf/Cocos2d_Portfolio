#pragma once
#include "cocos_framework.h"
#include "Item.h"

class Player : public Scene
{
private:
	static Player* Instance;
	Player();

	string _name;
	int _lv, _exp, _expm, _gold;
	vector<Item*> _item;

public:
	static Player* getInstance();
	Item* getItem() { return _item.back(); }
};