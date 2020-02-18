#pragma once
#include "Cuey.h"

#define PTM_RATIO 32

class Monster : public Scene {
private:

	b2World* _world;

	b2Body* _body;
	Layer* _layer;

	Sprite* _monster;

	float _atk, _hp, _hpm, _delay;

public:
	Monster(Layer* layer, b2World* world);
	~Monster();
	
	Sprite* getMonster() { return _monster; }
	
	void tick();
};