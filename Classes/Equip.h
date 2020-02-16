#pragma once
#include "cocos_framework.h"

class Equip : public Scene
{
private:
	SpriteFrameCache* _cache;

	Sprite *icon, *iconRaw;
	Sprite *_body, *_arm;
	String _name;
	float _atk;
	float _life;
	float _speed;
public:
	Equip();
};