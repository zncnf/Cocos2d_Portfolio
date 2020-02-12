#pragma once
#include "cocos_framework.h"
#include "Item.h"

class Player : public Scene
{
private:
	static Player* Instance;
	Player();

	SpriteFrameCache* _cache;
	Sprite* _player;
	Animate *_stand, *_move, *_hit, *_die;

	string _name;
	int _lv, _exp, _expm, _gold;
	vector<Item*> _item;


public:
	static Player* getInstance();
	
	void setLayer(Layer* layer);

	Item* getItem() { return _item.back(); }
};