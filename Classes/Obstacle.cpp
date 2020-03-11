#include "Obstacle.h"

Obstacle::Obstacle(String name)
{
	_layer = (Layer*)player->getPlayer()->getParent();
	_player = player->getPlayer();

	cache->addSpriteFramesWithFile("Obstacle/미사일.plist");
	cache->addSpriteFramesWithFile("Obstacle/레이저.plist");
	cache->addSpriteFramesWithFile("Obstacle/유도 미사일.plist");

	_obstacle =  Sprite::createWithSpriteFrameName(StringUtils::format("%s_attack_0.png", name.getCString()));
	_rect = Sprite::createWithTexture(nullptr, _obstacle->boundingBox());

	_name = name;
	_state = NONE;
	_isRemove = false;
	_speed = 1.0f;

	_obstacle->setPosition(cuey->rand(100, 1890), 720);

	if (name.compare("미사일") == 0) {
		_attackCount = 3;
		_hitCount = 5;
		setMissile();
		_state = MOVE_STRAIGHT;
	}
	if (name.compare("레이저") == 0) {
		_obstacle->setScaleX(3.0f);
		_attackCount = 7;
		_hitCount = -1;
		setLine();
		_state = ROTATE;
	}
	if (name.compare("유도 미사일") == 0) {
		_attackCount = 2;
		_hitCount = 8;
		_speed = 2.0f;
		setMissile();
		_state = MOVE_GUIDED;
	}	
}

void Obstacle::setMissile()
{
	_obstacle->setRotation(getAngle(_player->getPosition(), _obstacle->getPosition()) * 57.2);
	_obstacle->setFlippedX(true);
	_obstacle->setFlippedY(true);
	_layer->addChild(_obstacle);

	_rect = Sprite::createWithTexture(nullptr, Rect(0,0, 20, 20));
	_rect->setVisible(false);
	_rect->setColor(Color3B::RED);
	_rect->setOpacity(150);
	_layer->addChild(_rect);

	Vector<SpriteFrame*> frame;

	for (int i = 0; i <= _attackCount; i++) {
		frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_attack_%d.png", _name.getCString(), i)));
	}
	
	_obstacle->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1f))));

}

void Obstacle::setLine()
{
	_obstacle->setPosition(_player->getPositionX() + cuey->rand(-400, 400), 720);
	_obstacle->setVisible(false);
	_layer->addChild(_obstacle);

	_rect = Sprite::createWithTexture(nullptr, _obstacle->boundingBox());
	_rect->setPosition(_obstacle->getPosition());
	_rect->setScaleY(0.2f);
	_rect->setColor(Color3B::RED);
	_rect->setOpacity(150);
	_layer->addChild(_rect);

	_obstacle->runAction(Sequence::create(
		DelayTime::create(1),
		CallFunc::create(CC_CALLBACK_0(Obstacle::setState, this, STAND)),
		DelayTime::create(1),
		CallFunc::create(CC_CALLBACK_0(Obstacle::setLaser, this)),
		nullptr
	));
}

void Obstacle::setLaser()
{
	_obstacle->cleanup();

	_rect->setVisible(false);
	_obstacle->setVisible(true);

	Vector<SpriteFrame*> frame;

	for (int i = 0; i <= _attackCount; i++) {
		frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_attack_%d.png", _name.getCString(), i)));
	}

	_obstacle->runAction(Spawn::create(
		Sequence::create(
			CallFunc::create(CC_CALLBACK_0(Obstacle::setState, this, ATTACK)),
			DelayTime::create(0.3f),
			CallFunc::create(CC_CALLBACK_0(Obstacle::setState, this, NONE)),
			nullptr),
		Sequence::create(
			Animate::create(Animation::createWithSpriteFrames(frame, 0.1f)),
			CallFunc::create(CC_CALLBACK_0(Obstacle::setRemove, this)),
			nullptr),
		nullptr));
}

void Obstacle::setHit()
{
	_obstacle->cleanup();

	_obstacle->setPositionY(_obstacle->getPositionY() - 20);
	_obstacle->setZOrder(20);

	_state = NONE;

	Vector<SpriteFrame*> frame;

	for (int i = 0; i <= _hitCount; i++) {
		frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_hit_%d.png", _name.getCString(), i)));
	}

	_obstacle->runAction(Sequence::create(
		Repeat::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1f)), 1),
		CallFunc::create(CC_CALLBACK_0(Obstacle::setRemove, this)),
		nullptr));
}

void Obstacle::tick()
{
	if (_obstacle->getRotation() > 360) _obstacle->setRotation(_obstacle->getRotation() - 360);
	if(_obstacle->getRotation() < 0) _obstacle->setRotation(_obstacle->getRotation() + 360);
	float a = getAngle(_player->getPosition(), _obstacle->getPosition());
	switch (_state) {
	case NONE:break;
	case STAND:break;
	case ROTATE: 
		_obstacle->setRotation(getAngle(_obstacle->getPosition(), _player->getPosition()) * 57.2);
		_rect->setRotation(_obstacle->getRotation());
		break;
	case MOVE_STRAIGHT:
		_obstacle->setPosition(_obstacle->getPositionX() + cosf(_obstacle->getRotation() / 57.2) * 3,
			_obstacle->getPositionY() - sinf(_obstacle->getRotation() / 57.2) * 3);
		_rect->setPosition(_obstacle->getRotation() < 90 ? _obstacle->boundingBox().getMaxX() - 30 : _obstacle->boundingBox().getMinX() + 30,
			_obstacle->boundingBox().getMinY() + 30);
		if (player->getRect().intersectsRect(_rect->getBoundingBox())) {
			player->setHit();
			setHit();
		}
		if (_rect->getBoundingBox().getMinY() < 150) setHit();
		break;
	case MOVE_GUIDED:
		if (a > PI) {
			if (a - PI < _obstacle->getRotation() / 57.2 && a > _obstacle->getRotation() / 57.2) {
				_obstacle->setRotation(_obstacle->getRotation() + 0.2f);
			}
			else {
				_obstacle->setRotation(_obstacle->getRotation() - 0.2f);
			}
		}
		else {
			if (a + PI > _obstacle->getRotation() / 57.2 && a < _obstacle->getRotation() / 57.2) {
				_obstacle->setRotation(_obstacle->getRotation() - 0.2f);
			}
			else {
				_obstacle->setRotation(_obstacle->getRotation() + 0.2f);
			}
		}
		_rect->setRotation(_obstacle->getRotation());

		_speed += 0.01f;

		_obstacle->setPosition(_obstacle->getPositionX() + cosf(_obstacle->getRotation() / 57.2) * _speed,
			_obstacle->getPositionY() - sinf(_obstacle->getRotation() / 57.2) * _speed);
		_rect->setPosition(_obstacle->getRotation() < 90 ? _obstacle->boundingBox().getMaxX() - 30 : _obstacle->boundingBox().getMinX() + 30,
			_obstacle->boundingBox().getMinY() + 30);

		if (player->getRect().intersectsRect(_rect->getBoundingBox())) {
			_obstacle->setPosition(_obstacle->getPositionX() + cosf(_obstacle->getRotation() / 57.2) * 200,
				_obstacle->getPositionY() - sinf(_obstacle->getRotation() / 57.2) * 200);
			player->setHit();
			setHit();
		}
		else if (_rect->getBoundingBox().getMinY() < 150) {
			_obstacle->setPosition(_obstacle->getPositionX() + cosf(_obstacle->getRotation() / 57.2) * 200,
				_obstacle->getPositionY() - sinf(_obstacle->getRotation() / 57.2) * 200);
			setHit();
		}
		break;
	case ATTACK:break;
	}
}

bool Obstacle::getIsSectRect()
{
	//선충돌
	for (int i = 0; i < 1000; i++) {
		if (player->getRect().containsPoint(Vec2(getRect().getMinX() + getRect().size.width / 1000 * i, 
			_obstacle->getRotation() / 57.2 < PI*1.5f ? getRect().getMaxY() - getRect().size.height / 1000 * i : getRect().getMinY() + getRect().size.height / 1000 * i))) {
			_state = NONE;
			return true;
		}
	}

	//Rect temp = Rect(getRect().getMinX() + getRect().size.height * 13 / 238 / 3 * 0.2f, _player->getPositionX() > _obstacle->getPositionX() ? getRect().getMaxY() : getRect().getMinY(), getRect().size.height * 13 / 238 / 3 * 0.7f, 1);
	//for (int i = 0; i < 1000; i++) {
	//	//952,52
	//	//238, 13 height / 238, width / 13 height * 13  = width * 238 : 13
	//	_player->getPositionX() > _obstacle->getPositionX() ?
	//		temp.setRect(getRect().getMinX() + getRect().size.width / 1000 * i - player->getRect3().size.width / 2 + getRect().size.height * 13 / 238 / 3 * 0.15f, getRect().getMaxY() - getRect().size.height / 1000 * i, getRect().size.height * 13 / 238 / 3 * 0.7f, 1) :
	//		temp.setRect(getRect().getMinX() + getRect().size.width / 1000 * i - player->getRect3().size.width / 2 + getRect().size.height * 13 / 238 / 3 * 0.15f, getRect().getMinY() + getRect().size.height / 1000 * (i + 1), getRect().size.height * 13 / 238 / 3 * 0.7f, 1);
	//	if (temp.intersectsRect(player->getRect3())) {
	//		log("pr : %d(%d), %d(%d)\ttr : %d(%d), %d(%d)", (int)player->getRect3().getMinX(), (int)player->getRect3().size.width, (int)player->getRect3().getMinY(), (int)player->getRect3().size.height,
	//			(int)temp.getMinX(), (int)temp.size.width, (int)temp.getMinY(), (int)temp.size.height);
	//		_state = NONE;
	//		return true;
	//	}
	//}
	return false;
}