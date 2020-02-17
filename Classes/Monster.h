#pragma once
#include "Cuey.h"

class Monster : public Scene {
private:
	
	SpriteFrameCache* _cache;

	Layer* _layer;

	Sprite* _monster;

	float _atk, _hp, _hpm, _delay;
	float _jPow;

public:
	Monster(Layer* layer);
	~Monster();
	
	Sprite* getMonster() { return _monster; }
	
	void tick();
};