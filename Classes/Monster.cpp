#include "Monster.h"

Monster::Monster(Layer* layer) {

	cuey->cache()->addSpriteFramesWithFile("Monster/grinSnail.plist");

	_layer = layer;

	_monster = Sprite::createWithSpriteFrameName("grinSnail_stand_0.png");
	_monster->setPosition(cuey->rand(10, 1960), 720);
	//_monster->setAnchorPoint(Vec2(0, 0));
	_layer->addChild(_monster);

	_jPow = 0;
	_phase = 0;

	_way = LEFT;
	_state = STAND;
}

Monster::~Monster()
{
	_layer->removeChild(_monster);
}

void Monster::tick()
{
	switch (_phase) {
	case 0:
		_rotate = RepeatForever::create(RotateBy::create(0.5, Vec3(0, 0, cuey->rand(180, 720))));
		_monster->runAction(_rotate);
		setPhase(1);
		break;
	case 1:
		_jPow += 0.1f;
		_monster->setPositionY(_monster->getPositionY() - _jPow);
		if (_monster->getPositionY() < 170) {
			_monster->setPositionY(170);
			setPhase(2);
		}
		break;
	case 2:
		_monster->cleanup();
		_monster->setRotation3D(Vec3(0, 0, (int)_monster->getRotation3D().z % 360));
		_monster->runAction(Spawn::create(
			RotateTo::create(0.4, Vec3(0, 0, _monster->getRotation3D().z > 180 ? 0 : 720)),
			JumpBy::create(0.5, Vec2(cuey->rand(-70, 70), 0), 70, 1),
			Sequence::create(
				DelayTime::create(1),
				CallFunc::create(CC_CALLBACK_0(Monster::setPhase, this, 3)),
				nullptr),
			nullptr));
		setPhase(-1);
		break;
	case 3:
		_monster->cleanup();
		switch (cuey->rand(0, 3)) {
		case 0:
			_monster->setSpriteFrame("grinSnail_stand_0.png");
			_state = STAND;
			break;
		case 1:
			Vector<SpriteFrame*> frame;

			for (int i = 0; i < 5; i++) {
				frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("grinSnail_move_%d.png", i)));
			}
			_monster->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f))));
			_state = MOVE;
			break;
		}
		setPhase(-1);
		this->runAction(Sequence::create(
			DelayTime::create(1),
			CallFunc::create(CC_CALLBACK_0(Monster::setPhase, this, 3)),
			nullptr));
		break;
	}
	if (_state == MOVE) {
		if (_way == LEFT) _monster->setPositionX(_monster->getPositionX() - 1);
		else _monster->setPositionX(_monster->getPositionX() + 1);
	}
}
