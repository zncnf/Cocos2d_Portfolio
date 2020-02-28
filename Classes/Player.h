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
	Vector<Animate*> _stand, _walk;

	string _name;
	int _lv, _exp, _expm, _gold;
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
	Rect getRect() { return Rect(_player->getPositionX() - 15, _player->getPositionY() - 36, 30, 72); }
	Skill* getSkill() { return _skill; }
	bool getIsAttack() { return _isAttack; }
	bool getIsHit() { return _isHit; }
	bool getWay() { return _way; }

	Item* getItem() { return _item.back(); }
};