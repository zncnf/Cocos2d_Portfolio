#pragma once
#include "Cuey.h"
#include "Item.h"
#include "Equip.h"
#include "Skill.h"
#include "Pet.h"

#define player Player::getInstance()

class Player : public Scene
{
private:
	static Player* Instance;
	Player();

	Layer* _layer;
	Layer* _player;
	Layer* _expLayer;
	Layer* _lifeLayer;
	Label* _lifeLabel;
	Sprite *_rect, *_rect2;
	Sprite *_body, *_head, *_arm, *_rhand, *_lhand;
	Sprite* _expBar;
	Vector<Animate*> _stand, _walk;
	Animate* _levelUP;

	string _name;
	float _lv, _exp, _expm, _gold;
	float _atk, _life, _lifem, _speed;
	Item* _item;
	Equip* _equip;
	Skill* _skill;
	Pet* _pet;

	vector<int> _mobInRange;

	int _isStand, _isLeft, _isRight, _isJump, _isHit;
	bool _isDead, _isFoot, _isAttack, _way, _isGame;
	float _jPow;
	int _pickUpDelay;

	int _bestTime[3];

public:
	static Player* getInstance();

	void setLayer(Layer* layer, bool game = true);

	void setStand();
	void setFoot();
	void setWalk();
	void setJump();
	void setAttack(bool game = true);
	void setAttack_Frame(int frame);
	void setRange(int n);
	void setHit();
	void setHitCount(int n);
	void setDead();
	void setWay(bool way);
	void setPickUp() { _pickUpDelay = 30; }
	void setBestTime(int n, int time) { _bestTime[n] = time; }

	void appendGold(int gold) {
		_gold += gold;
	}

	void appendExp(int exp) {
		_exp += exp;
		_expBar->cleanup();
		_expBar->runAction(ScaleTo::create(0.5f, _exp/_expm, 1));
		if (_exp >= _expm) {
			levelUp();
		}
	}
	void levelUp();

	void offGame() { 
		_isGame = false;
		_mobInRange.clear();
	}

	void viewRect(bool view) { 
		_rect->setVisible(view);
		_rect2->setVisible(view);
		_skill->viewRect(view);
	}

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void tick();

	Layer* getPlayer() { return _player; }
	bool getIsLeft() { return _isLeft == 2 ? true : false; }
	bool getIsRight() { return _isRight == 2 ? true : false; }
	bool getIsDead() { return _isDead; }
	Rect getRect() { return Rect(_player->getPositionX() - 15, _player->getPositionY() - 49, 30, 72); }
	Rect getRect2() { return Rect(_player->getPositionX() - 500, _player->getPositionY() - 136, 1000, 200); }
	Rect getRect3() { return Rect(_player->getPositionX() - 15, _player->getPositionY() - 5, 30, 10); }
	Item* getItem() { return _item; }
	Equip* getEquip() { return _equip; }
	Skill* getSkill() { return _skill; }
	Pet* getPet() { return _pet; }
	bool getIsAttack() { return _isAttack; }
	bool getIsHit() { return _isHit; }
	bool getIsFoot() { return _isFoot; }
	bool getWay() { return _way; }
	bool getIsPickUp() { return _pickUpDelay == 0 ? true : false; }
	int getMobRangeSize() { return _mobInRange.size(); }
	float getLv() { return _lv; }
	float getExp() { return _exp; }
	float getExpm() { return _expm; }
	float getGold() { return _gold; }
	int getBestTime(int n) { return _bestTime[n]; }

	float getNormalDamage() { 
		float damage = (_atk + _equip->getMountWeaponAtk()) * _skill->getNormalAtkf();
		return damage * cuey->rand(0.8, 1.0);
	}
	float getBaseAtk() { return _atk; }
	float getBaseLife() { return _lifem; }
	float getBaseSpeed() { return _speed; }

	float getAtk() { return _atk + _equip->getMountWeaponAtk(); }
	float getLife() { return _lifem + _equip->getMountArmorLife(); }
	float getSpeed() { return _speed + _equip->getMountShoesSpeed(); }
};