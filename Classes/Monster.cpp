#include "Monster.h"

Monster::Monster(Layer* layer) {

	cache->addSpriteFramesWithFile("Monster/grinSnail.plist");

	_layer = layer;

	_code = "grinSnail";

	_monster = Sprite::createWithSpriteFrameName(StringUtils::format("%s_stand_0.png", _code));
	_monster->setPosition(cuey->rand(100, 1890), 720);
	
	_rect = Sprite::createWithTexture(nullptr, _monster->boundingBox());
	_monster->addChild(_rect, -1);
	_rect->setAnchorPoint(Vec2(0, 0));
	_rect->setColor(Color3B::RED);
	_rect->setOpacity(100);
	_rect->setVisible(false);

	_layer->addChild(_monster);

	_jPow = 0;
	_phase = ȸ��;

	_isFollow = false;
	_isHitTrue = false;
	_way = LEFT;
	_state = STAND;
}

Monster::~Monster()
{
	_layer->removeChild(_monster);
}

void Monster::tick()
{
	Vector<SpriteFrame*> frame;
	switch (_phase) {
	case ȸ��:
		_rotate = RepeatForever::create(RotateBy::create(0.5, Vec3(0, 0, cuey->rand(180, 720))));
		_monster->runAction(_rotate);
		setPhase(����);
		break;
	case ����:
		_jPow += 0.1f;
		_monster->setPositionY(_monster->getPositionY() - _jPow);
		if (_monster->getPositionY() < 170) {
			_monster->setPositionY(170);
			setPhase(����);
		}
		break;
	case ����:
		_monster->cleanup();
		_monster->setRotation3D(Vec3(0, 0, (int)_monster->getRotation3D().z % 360));
		_monster->runAction(Spawn::create(
			RotateTo::create(0.4, Vec3(0, 0, _monster->getRotation3D().z > 180 ? 0 : 720)),
			JumpBy::create(0.5, Vec2(cuey->rand(-70, 70), 0), 70, 1),
			Sequence::create(
				DelayTime::create(1),
				CallFunc::create(CC_CALLBACK_0(Monster::setPhase, this, ���)),
				nullptr),
			nullptr));
		setPhase(���);
		break;
	case ���:
		_isHitTrue = true;
		_monster->cleanup();
		switch (_state) {
		case HIT:
			_isFollow = true;
			_state = HITEND;
			_monster->runAction(Spawn::create(
				RotateTo::create(0.4, Vec3(0, 0, player->getWay() ? 720 : -720)),
				JumpBy::create(0.5, Vec2(player->getWay() ? 40 : -40, 0), 40, 1),
				nullptr));
			setPhase(���);
			break;
		case HITEND:
			_state = MOVE;
			setPhase(���);
			break;
		default:
			if (_isFollow) {
				for (int i = 0; i < 5; i++) {
					frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_move_%d.png", _code, i)));
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
					_monster->setSpriteFrame(StringUtils::format("%s_stand_0.png", _code));
					_state = STAND;
					break;
				case 1:
					for (int i = 0; i < 5; i++) {
						frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_move_%d.png", _code, i)));
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
			setPhase(���);
			_monster->runAction(Sequence::create(
				DelayTime::create(2),
				CallFunc::create(CC_CALLBACK_0(Monster::setPhase, this, ���)),
				nullptr));
		}
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
