#include "Monster.h"

Monster::Monster(Layer* layer) {

	cuey->cache()->addSpriteFramesWithFile("Monster/grinSnail.plist");

	_layer = layer;

	_monster = Sprite::createWithSpriteFrameName("grinSnail_stand_0.png");
	_monster->setPosition(cuey->rand(10, 1960), 720);
	//_monster->setAnchorPoint(Vec2(0, 0));
	_layer->addChild(_monster);

	_rotate = RepeatForever::create(RotateBy::create(0.5, Vec3(0, 0, cuey->rand(180, 720))));

	_monster->runAction(_rotate);

	_jPow = 0;

	_phase = 0;
}

Monster::~Monster()
{
	_layer->removeChild(_monster);
}

void Monster::tick()
{
	switch (_phase) {
	case 0:
		_jPow += 0.1f;
		_monster->setPositionY(_monster->getPositionY() - _jPow);
		if (_monster->getPositionY() < 170) {
			_monster->setPositionY(170);
			_phase = 1;
		}
		break;
	case 1:
		_monster->cleanup();
		_monster->setRotation3D(Vec3(0, 0, (int)_monster->getRotation3D().z % 360));
		_monster->runAction(Spawn::create(
			RotateTo::create(0.4, Vec3(0, 0, _monster->getRotation3D().z > 180 ? 0 : 720)),
			JumpBy::create(0.5, Vec2(cuey->rand(-50, 50), 0), 50, 1),
			nullptr));
		_phase = 2;
		break;
	}
	
}
