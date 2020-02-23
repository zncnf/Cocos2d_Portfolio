#pragma once
#include "Cuey.h"
#include "Player.h"

#define PTM_RATIO 32

class Monster : public Scene {
private:
	enum WAY {
		LEFT = 0,
		RIGHT = 1
	};
	enum STATE {
		STAND,
		MOVE,
		HIT,
		DEAD
	};
	Layer* _layer;

	Sprite* _monster;
	Action* _rotate;

	int _phase;

	float _atk, _hp, _hpm, _delay;
	float _jPow;

	bool _isFollow;

	WAY _way;
	STATE _state;

public:
	Monster(Layer* layer);
	~Monster();
	
	Sprite* getMonster() { return _monster; }
	
	void tick();

private:

	void setPhase(int n) { _phase = n; }
};