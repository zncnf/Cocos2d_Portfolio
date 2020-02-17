#include "Monster.h"

Monster::Monster(Layer* layer) {

	_cache = SpriteFrameCache::getInstance();
	_cache->addSpriteFramesWithFile("Monster/grinSnail.plist");

	_layer = layer;

	_monster = Sprite::createWithSpriteFrameName("grinSnail_stand_0.png");
	_monster->setPosition(cuey->rand(10, 1960), 720);
	_layer->addChild(_monster);
	_jPow = 0;
}

Monster::~Monster()
{
	_layer->removeChild(_monster);
}

void Monster::tick()
{
	//_monster->setPositionY(_monster->getPositionY() - 5);

	_jPow += 0.1f;
	_monster->setPositionY(_monster->getPositionY() - _jPow);

	if (_monster->getPositionY() < 215) {
		_monster->setPositionY(215);
	}
}
