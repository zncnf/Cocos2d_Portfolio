#pragma once
#include "Cuey.h"
#include "Player.h"

class Monster : public Scene {
public:
	enum MOB {
		�ʷϴ����� = 0,
		����,
		���̳�_����,
		���̷���,
		ħ����_�ϻ���,
		������_����
	};
private:
	enum PHASE {
		���,
		ȸ��,
		����,
		����,
		���
	};
	enum WAY {
		LEFT = 0,
		RIGHT = 1
	};
	enum STATE {
		STAND,
		MOVE,
		ATTACK,
		HIT,
		HITEND,
		DEAD
	};
	Layer* _layer;
	Layer* _hpBarLayer;

	Sprite* _monster;
	Sprite* _rect;
	Sprite* _hpBar;
	Label* _damageNumber;
	Action* _rotate;
	Animate* _moveAnimate;
	Animate* _dieAnimate;

	Item* _item;

	PHASE _phase;

	MOB _mob;
	int _standCount, _moveCount, _attackCount, _hitCount, _dieCount;
	char* _code;
	float _atk, _def, _hp, _hpm, _delay, _speed, _gold, _exp;
	float _jPow;
	float _hitDamage;

	bool _isFollow, _isAttack, _isHitTrue, _isRemove, _isAllKill;

	WAY _way;
	STATE _state;

public:
	Monster(Layer* layer, MOB mob);
	~Monster();

	Sprite* getMonster() { return _monster; }
	Rect getRect() {
		return Rect(_monster->boundingBox().getMinX(), _monster->boundingBox().getMinY(),
			_monster->getContentSize().width, _monster->getContentSize().height);
	}
	Item* getItem() { return _item; }

	float getAtk() { return _atk; }
	float getHp() { return _hp; }
	float getHpm() { return _hpm; }
	float getDelay() { return _delay; }
	float getSpeed() { return _speed; }

	int getGold() { return (int)(cuey->rand(0.8, 1.0) * _gold); }

	bool getIsFollow() { return _isFollow; }
	bool getIsHitTrue() { return _isHitTrue; }
	bool getIsAttackTrue() { return _hp > 0 ? true : false; }
	bool getIsAllKill() { return _isAllKill; }
	bool getIsMove() { return _state == MOVE ? true : false; }
	bool getIsDead() { return _state == DEAD ? true : false; }
	bool getIsRemove() { return _isRemove; }
	bool getIsAttack() { return _isAttack; }

	void setIsAllKill() { _isAllKill = true;}
	void setPhase(PHASE n) { _phase = n; }
	void setState(STATE n) { _state = n; }
	void setFollow() { _isFollow = true; }
	void setHit(int damage) { 
		_hitDamage = damage > _def ? damage - _def : 1;
		_hp -= _hitDamage;
		_hpBar->setScaleX(_hp < 0 ? 0 :_hp / _hpm);
		setPhase(���);
		_state = HIT;
	}
	void setHp(int n) { _hp = n; }

	void viewRect(bool view) { _rect->setVisible(view); }
	
	void tick();

private:
	void setWay(bool way);
	void setRemove() { 
		_isRemove = true;
		_hpBarLayer->setVisible(false);
		_monster->setVisible(false);
	}
	void setHitEffect() { 
		AudioEngine::play2d(StringUtils::format("Sound/%s_hit.mp3", _code), false, 1.0f);
		player->getSkill()->playNormalHit(_monster->getPosition()); 
		_damageNumber->cleanup();
		_damageNumber->setAnchorPoint(Vec2(0.5f, 0.0f));
		_damageNumber->setPosition(Vec2(_monster->getPositionX(), _monster->getPositionY() + 50));
		_damageNumber->setString(StringUtils::format("%d", (int)_hitDamage));
		_damageNumber->setScale(1.7);
		//_damageNumber->setVisible(false);
		
		_damageNumber->runAction(Sequence::create(
			Spawn::create(
				JumpBy::create(0.7, Vec2(cuey->rand(-100, 100), cuey->rand(30, 35)), 50, 1),
				ScaleBy::create(0.7, 0),
				nullptr), 
			nullptr)
		);
		_hpBarLayer->setVisible(true);
	}
	
};