#pragma once
#include "cocos_framework.h"
#include "Item.h"
#include "Equip.h"

class Player : public Scene
{
private:
	static Player* Instance;
	Player();

	SpriteFrameCache* _cache;

	Layer* _player;
	Sprite *_body, *_head, *_arm, *_rhand, *_lhand;
	Vector<Animate*> _stand, _walk;

	string _name;
	int _lv, _exp, _expm, _gold;
	vector<Item*> _item;
	Equip* _equip;

	int _isStand, _isLeft, _isRight, _isJump;
	bool _isDead, _isFoot, _isRange, _isAttack;
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
	void setHit();
	void setDead();
	void setWay(bool way);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void tick();

	Layer* getPlayer() { return _player; }
	bool getIsLeft() { return _isLeft == 2 ? true : false; }
	bool getIsRight() { return _isRight == 2 ? true : false; }

	Item* getItem() { return _item.back(); }
};