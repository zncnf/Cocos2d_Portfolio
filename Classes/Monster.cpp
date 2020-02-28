#include "Monster.h"

Monster::Monster(Layer* layer) {
	_layer = layer;

	_mob = 초록달팽이;

	switch (_mob) {
	case 초록달팽이:
		cache->addSpriteFramesWithFile("Monster/grinSnail.plist");
		_code = "grinSnail";
		_standCount = 0;
		_moveCount = 4;
		_hitCount = 0;
		_dieCount = 9;
		_atk = 10;
		_hp = _hpm = 10;
		_delay = 0;
		_speed = 1;
		break;
	}


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
	_phase = 회전;

	_isFollow = false;
	_isHitTrue = false;
	_isRemove = false;
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
	case 회전:
		_rotate = RepeatForever::create(RotateBy::create(0.5, Vec3(0, 0, cuey->rand(180, 720))));
		_monster->runAction(_rotate);
		setPhase(낙하);
		break;
	case 낙하:
		_jPow += 0.1f;
		_monster->setPositionY(_monster->getPositionY() - _jPow);
		if (_monster->getPositionY() < 170) {
			_monster->setPositionY(170);
			setPhase(착지);
		}
		break;
	case 착지:
		_monster->cleanup();
		_monster->setRotation3D(Vec3(0, 0, (int)_monster->getRotation3D().z % 360));
		_monster->runAction(Spawn::create(
			RotateTo::create(0.4, Vec3(0, 0, _monster->getRotation3D().z > 180 ? 0 : 720)),
			JumpBy::create(0.5, Vec2(cuey->rand(-70, 70), 0), 70, 1),
			Sequence::create(
				DelayTime::create(0.5),
				CallFunc::create(CC_CALLBACK_0(Monster::setPhase, this, 모션)),
				nullptr),
			nullptr));
		setPhase(대기);
		break;
	case 모션:
		_isHitTrue = true;
		_monster->cleanup();
		switch (_state) {
		case HIT:
			_isFollow = true;
			_state = MOVE;
			for (int i = 0; i <= (_moveCount >= 3 ? 3 : _moveCount); i++) {
				frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_move_%d.png", _code, i)));
			}
			_monster->runAction(Spawn::create(
				Animate::create(Animation::createWithSpriteFrames(frame, 0.2f)),
				Sequence::create(
					DelayTime::create(0.6f),
					CallFunc::create(CC_CALLBACK_0(Monster::setHitEffect, this)),
					CallFunc::create(CC_CALLBACK_0(Monster::setState, this, HITEND)),
					Spawn::create(
						RotateTo::create(0.4, Vec3(0, 0, player->getWay() ? 720 : -720)),
						JumpBy::create(0.5, Vec2(player->getWay() ? 40 : -40, 0), 40, 1),
						nullptr),
					CallFunc::create(CC_CALLBACK_0(Monster::setPhase, this, 모션)),
					nullptr),
				nullptr));
			setPhase(대기);
			break;
		case HITEND:
			if (_hp <= 0) {
				_hp = 0;
				_state = DEAD;
			}
			else {
				_state = MOVE;
				setPhase(모션);
			}
			break;
		case DEAD:
			switch (_mob) {
			case 초록달팽이:
				_monster->setPositionY(_monster->getPositionY() + 4);
				break;
			}
			for (int i = 0; i <=  _dieCount; i++) {
				frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_die_%d.png", _code, i)));
			}
			_monster->runAction(Sequence::create(
				Animate::create(Animation::createWithSpriteFrames(frame, 0.1f)),
				CallFunc::create(CC_CALLBACK_0(Monster::setRemove, this)),
				nullptr));
			setPhase(대기);
			break;
		default:
			if (_isFollow) {
				for (int i = 0; i <= _moveCount; i++) {
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
					for (int i = 0; i <= _moveCount; i++) {
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
			setPhase(대기);
			_monster->runAction(Sequence::create(
				DelayTime::create(2),
				CallFunc::create(CC_CALLBACK_0(Monster::setPhase, this, 모션)),
				nullptr));
		}
		break;
	}
	if (_monster->getPositionX() < 20) {
		_monster->setPositionX(20);
	}
	if (_monster->getPositionX() > 1960) {
		_monster->setPositionX(1960);
	}

	if (_state == MOVE) {
		if (_way == LEFT) _monster->setPositionX(_monster->getPositionX() - _speed);
		if (_way == RIGHT) _monster->setPositionX(_monster->getPositionX() + _speed);
	}
}

void Monster::setWay(bool way)
{
	_way = (WAY)way;
	_monster->setFlippedX(way);
	_rect->setFlippedX(way);
}
