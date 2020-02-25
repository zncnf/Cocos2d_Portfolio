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
	Sprite* _rect;
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
	Rect getRect() { return Rect(_monster->boundingBox().getMinX(), _monster->boundingBox().getMidY(),
								_monster->getContentSize().width, _monster->getContentSize().height); }
	bool getIsFollow() { return _isFollow; }

	void setFollow() { _isFollow = true; }

	void viewRect(bool view) { _rect->setVisible(view); }
	
	void tick();

private:

	void setPhase(int n) { _phase = n; }
	void setWay(bool way);
	
};