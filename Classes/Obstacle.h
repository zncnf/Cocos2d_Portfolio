#pragma once
#include "Cuey.h"
#include "Player.h"

#define PI 3.141592

class Obstacle : public Scene {
private:
	enum STATE {
		NONE,
		STAND,
		ROTATE,
		MOVE_STRAIGHT,
		MOVE_GUIDED,
		ATTACK
	};

	Layer* _layer;
	Layer* _player;

	Sprite* _obstacle;
	Sprite* _rect;
	String _name;
	STATE _state;
	float _speed;
	int _attackCount;
	int _hitCount;

	bool _isRemove;

public:
	Obstacle(String name);

	void setMissile();

	void setLine();

	void setLaser();

	void setHit();

	void tick();

	void setState(STATE state) { _state = state; }
	void setRemove() {
		_obstacle->setVisible(false);
		_rect->setVisible(false);
		_state = NONE;
		_isRemove = true;
	};
	Sprite* getSprite() { return _obstacle; }
	Rect getRect() { return _rect->getBoundingBox(); }
	bool getIsSectRect();
	bool getIsRemove() { return _isRemove; }
	float getDistance(Vec2 pt, Vec2 pt2) { return sqrtf(pow(pt.x - pt2.x, 2) + pow(pt.y - pt2.y, 2)); }
	float getAngle(Vec2 pt, Vec2 pt2) { return acosf((pt.x - pt2.x) / getDistance(pt, pt2)) * (pt.y > pt2.y ? -1 : 1); }

	bool getIsAttack() { return _state == ATTACK ? true : false; }
};