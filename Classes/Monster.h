#pragma once
#include "Cuey.h"
#include "Player.h"

#define PTM_RATIO 32

class Monster : public Scene {
private:

	Layer* _layer;

	Sprite* _monster;
	Action* _rotate;

	int _phase;

	float _atk, _hp, _hpm, _delay;
	float _jPow;

public:
	Monster(Layer* layer);
	~Monster();
	
	Sprite* getMonster() { return _monster; }
	
	void tick();
};