#pragma once
#include "Cuey.h"
#include "Player.h"

#define PTM_RATIO 32

class Monster : public Scene {
public:
	enum MOB {
		ÃÊ·Ï´ÞÆØÀÌ = 0,
		ÆÄ¶õ´ÞÆØÀÌ,
		»¡°£´ÞÆØÀÌ
	};
private:
	enum PHASE {
		´ë±â,
		È¸Àü,
		³«ÇÏ,
		ÂøÁö,
		¸ð¼Ç
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
	Animate* _moveAnimate;
	Animate* _dieAnimate;

	PHASE _phase;

	MOB _mob;
	int _standCount, _moveCount, _hitCount, _dieCount;
	char* _code;
	float _atk, _hp, _hpm, _delay, _speed;
	float _jPow;

	bool _isFollow, _isHitTrue, _isRemove;

	WAY _way;
	STATE _state;

public:
	Monster(Layer* layer);
	~Monster();
	
	Sprite* getMonster() { return _monster; }
	Rect getRect() { return Rect(_monster->boundingBox().getMinX(), _monster->boundingBox().getMidY(),
								_monster->getContentSize().width, _monster->getContentSize().height); }

	float getAtk() { return _atk; }
	float getHp() { return _hp; }
	float getHpm() { return _hpm; }
	float getDelay() { return _delay; }
	float getSpeed() { return _speed; }

	bool getIsFollow() { return _isFollow; }
	bool getIsHitTrue() { return _isHitTrue; }
	bool getIsDead() { return _state == DEAD ? true : false; }
	bool getIsRemove() { return _isRemove; }

	void setPhase(PHASE n) { _phase = n; }
	void setState(STATE n) { _state = n; }
	void setFollow() { _isFollow = true; }
	void setHit(float damage) { 
		_hp -= damage;
		setPhase(¸ð¼Ç);
		_state = HIT;
	}

	void viewRect(bool view) { _rect->setVisible(view); }
	
	void tick();

private:
	void setWay(bool way);
	void setRemove() { _isRemove = true; }
	void setHitEffect() { player->getSkill()->playNormalHit(_monster->getPosition()); }
	
};