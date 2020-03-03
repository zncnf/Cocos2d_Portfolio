#pragma once
#include "Cuey.h"
#include "Item.h"
#include "Equip.h"
#include "Skill.h"

#define player Player::getInstance()

class Player : public Scene
{
private:
	static Player* Instance;
	Player();

	Layer* _layer;
	Layer* _player;
	Sprite* _rect;
	Sprite *_body, *_head, *_arm, *_rhand, *_lhand;
	Sprite* _expBar;
	Vector<Animate*> _stand, _walk;

	string _name;
	float _lv, _exp, _expm, _gold;
	float _atk, _life, _speed;
	vector<Item*> _item;
	Equip* _equip;
	Skill* _skill;

	vector<int> _mobInRange;

	int _isStand, _isLeft, _isRight, _isJump, _isHit;
	bool _isDead, _isFoot, _isAttack, _way;
	float _jPow;

public:
	static Player* getInstance();
	
	void setLayer(Layer* layer);

	void setStand();
	void setFoot();
	void setWalk();
	void setJump();
	void setAttack();
	void setAttack_Frame(int frame);
	void setRange(int n);
	void setHit();
	void setHitCount(int n);
	void setDead();
	void setWay(bool way);

	void appendExp(int exp) {
		_exp += exp;
		_expBar->cleanup();
		_expBar->runAction(ScaleTo::create(0.5f, _exp/_expm, 1));
		//_expBar->setScaleX(player->getExp() / player->getExpm());
		if (_exp >= _expm) {
			levelUp();
		}
	}
	void levelUp();


	void viewRect(bool view) { 
		_rect->setVisible(view);
		_skill->viewRect(view);
	}

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void tick();

	Layer* getPlayer() { return _player; }
	bool getIsLeft() { return _isLeft == 2 ? true : false; }
	bool getIsRight() { return _isRight == 2 ? true : false; }
	bool getIsDead() { return _isDead; }
	Rect getRect() { return Rect(_player->getPositionX() - 15, _player->getPositionY() - 36, 30, 72); }
	Equip* getEquip() { return _equip; }
	Skill* getSkill() { return _skill; }
	bool getIsAttack() { return _isAttack; }
	bool getIsHit() { return _isHit; }
	bool getWay() { return _way; }
	int getMobRangeSize() { return _mobInRange.size(); }
	float getLv() { return _lv; }
	float getExp() { return _exp; }
	float getExpm() { return _expm; }
	float getGold() { return _gold; }

	float getNormalDamage() { return (_atk + _equip->getMountWeaponAtk()) * _skill->getNormalAtkf(); }
	float getBaseAtk() { return _atk; }
	float getBaseLife() { return _life; }
	float getBaseSpeed() { return _speed; }

	Item* getItem() { return _item.back(); }
};