#pragma once
#include "Cuey.h"
#include "Player.h"

#define PTM_RATIO 32

class Monster : public Scene {
private:
	enum PHASE {
		대기,
		회전,
		낙하,
		착지,
		모션
	};
	enum WAY {
		LEFT = 0,
		RIGHT = 1
	};
	enum STATE {
		STAND,
		MOVE,
		HIT,
		HITEND,
		DEAD
	};
	Layer* _layer;

	Sprite* _monster;
	Sprite* _rect;
	Action* _rotate;

	PHASE _phase;

	char* _code;
	float _atk, _hp, _hpm, _delay;
	float _jPow;

	bool _isFollow, _isHitTrue;

	WAY _way;
	STATE _state;

public:
	Monster(Layer* layer);
	~Monster();
	
	Sprite* getMonster() { return _monster; }
	Rect getRect() { return Rect(_monster->boundingBox().getMinX(), _monster->boundingBox().getMidY(),
								_monster->getContentSize().width, _monster->getContentSize().height); }
	bool getIsFollow() { return _isFollow; }
	bool getIsHitTrue() { return _isHitTrue; }

	void setPhase(PHASE n) { _phase = n; }
	void setFollow() { _isFollow = true; }
	void setHit(float damage) { 
		_hp -= damage;
		setPhase(모션);
		_state = HIT;
	}

	void viewRect(bool view) { _rect->setVisible(view); }
	
	void tick();

private:
	void setWay(bool way);
	
};