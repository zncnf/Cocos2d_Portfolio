#include "Monster.h"

Monster::Monster(Layer* layer) {

	cache->addSpriteFramesWithFile("Monster/grinSnail.plist");

	_layer = layer;

	_monster = Sprite::createWithSpriteFrameName("grinSnail_stand_0.png");
	_monster->setPosition(cuey->rand(100, 1890), 720);
	
	_rect = Sprite::createWithTexture(nullptr, _monster->boundingBox());
	_monster->addChild(_rect, -1);
	_rect->setAnchorPoint(Vec2(0, 0));
	_rect->setColor(Color3B::RED);
	_rect->setOpacity(100);
	_rect->setVisible(false);

	_layer->addChild(_monster);

	_jPow = 0;
	_phase = 0;

	_isFollow = false;
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
		Vector<SpriteFrame*> frame;
		if (_isFollow) {
			for (int i = 0; i < 5; i++) {
				frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("grinSnail_move_%d.png", i)));
			}
			_monster->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f))));
			_state = MOVE;
			if (player->getPlayer()->getPositionX() < _monster->getPositionX()) {
				setWay(false);
			}
			else {
				setWay(true);
			}
		}
		else {
			switch (cuey->rand(0, 1)) {
			case 0:
				_monster->setSpriteFrame("grinSnail_stand_0.png");
				_state = STAND;
				break;
			case 1:
				for (int i = 0; i < 5; i++) {
					frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("grinSnail_move_%d.png", i)));
				}
				_monster->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f))));
				_state = MOVE;
				if (cuey->rand(0, 1000) < 500) {
					setWay(false);
				}
				else {
					setWay(true);
				}
				break;
			}
		}
		setPhase(-1);
		_monster->runAction(Sequence::create(
			DelayTime::create(2),
			CallFunc::create(CC_CALLBACK_0(Monster::setPhase, this, 3)),
			nullptr));
		break;
	}
	
	if (_state == MOVE) {
		if (_monster->getPositionX() > 20) {
			if (_way == LEFT) _monster->setPositionX(_monster->getPositionX() - 1);
		}
		if (_monster->getPositionX() < 1960) {
			if (_way == RIGHT) _monster->setPositionX(_monster->getPositionX() + 1);
		}
	}
}

void Monster::setWay(bool way)
{
	_way = (WAY)way;
	_monster->setFlippedX(way);
	_rect->setFlippedX(way);
}
