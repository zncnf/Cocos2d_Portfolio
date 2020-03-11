#include "Monster.h"

Monster::Monster(Layer* layer, MOB mob) {
	_layer = (Layer*)player->getPlayer()->getParent();

	_item = new Item;
	_item->setLayer(_layer);

	_mob = mob;

	vector<String> itemString;
	itemString.push_back("µ·");

	random_device rd;
	mt19937 g(rd());

	switch (_mob) {
	case ÃÊ·Ï´ÞÆØÀÌ:
		cache->addSpriteFramesWithFile("Monster/grinSnail.plist");
		_code = "grinSnail";
		_standCount = 0;
		_moveCount = 4;
		_attackCount = -1;
		_hitCount = 0;
		_dieCount = 9;
		_atk = 10;
		_def = 1;
		_hp = _hpm = 10;
		_delay = 0;
		_speed = 1;
		_gold = 10;
		_exp = 3;
		itemString.push_back("´ÞÆØÀÌÀÇ ²®Áú");

		shuffle(itemString.begin(), itemString.end(), g);

		for (int i = 0; i < itemString.size(); i++) {
			if (itemString[i].compare("µ·") == 0) {
				if (cuey->rand(0.0, 1.0) < 0.9) _item->setItem("µ·");
			}
			else {
				if (cuey->rand(0.0, 1.0) < 0.5) _item->setItem(itemString[i]);
			}
		}
		break;
	case µÅÁö:
		cache->addSpriteFramesWithFile("Monster/pig.plist");
		_code = "pig";
		_standCount = 2;
		_moveCount = 2;
		_attackCount = -1;
		_hitCount = 0;
		_dieCount = 11;
		_atk = 10;
		_def = 3;
		_hp = _hpm = 16;
		_delay = 0;
		_speed = 1.5;
		_gold = 20;
		_exp = 5;
		itemString.push_back("µÅÁöÀÇ ¸Ó¸®");

		shuffle(itemString.begin(), itemString.end(), g);

		for (int i = 0; i < itemString.size(); i++) {
			if (itemString[i].compare("µ·") == 0) {
				if (cuey->rand(0.0, 1.0) < 0.9) {
					_item->setItem("µ·");
				}
			}
			else {
				if (cuey->rand(0.0, 1.0) < 0.5) {
					_item->setItem(itemString[i]);
				}
			}
		}
		break;
	case ¸¶ÀÌ³Ê_Á»ºñ:
		cache->addSpriteFramesWithFile("Monster/¸¶ÀÌ³Ê Á»ºñ.plist");
		_code = "¸¶ÀÌ³Ê Á»ºñ";
		_standCount = 2;
		_moveCount = 2;
		_attackCount = 12;
		_hitCount = 0;
		_dieCount = 19;
		_atk = 10;
		_def = 5;
		_hp = _hpm = 30;
		_delay = 0;
		_speed = 1.2;
		_gold = 30;
		_exp = 8;
		itemString.push_back("µÅÁöÀÇ ¸Ó¸®");

		shuffle(itemString.begin(), itemString.end(), g);

		for (int i = 0; i < itemString.size(); i++) {
			if (itemString[i].compare("µ·") == 0) {
				if (cuey->rand(0.0, 1.0) < 0.9) {
					_item->setItem("µ·");
				}
			}
			else {
				if (cuey->rand(0.0, 1.0) < 0.5) {
					_item->setItem(itemString[i]);
				}
			}
		}
		break;
	case ½ºÄÌ·¹°ï:
		cache->addSpriteFramesWithFile("Monster/½ºÄÌ·¹°ï.plist");
		_code = "½ºÄÌ·¹°ï";
		_standCount = 5;
		_moveCount = 3;
		_attackCount = 16;
		_hitCount = 0;
		_dieCount = 17;
		_atk = 10;
		_def = 8;
		_hp = _hpm = 25;
		_delay = 0;
		_speed = 1.5;
		_gold = 35;
		_exp = 10;
		itemString.push_back("µÅÁöÀÇ ¸Ó¸®");

		shuffle(itemString.begin(), itemString.end(), g);

		for (int i = 0; i < itemString.size(); i++) {
			if (itemString[i].compare("µ·") == 0) {
				if (cuey->rand(0.0, 1.0) < 0.9) {
					_item->setItem("µ·");
				}
			}
			else {
				if (cuey->rand(0.0, 1.0) < 0.5) {
					_item->setItem(itemString[i]);
				}
			}
		}
		break;
	case Ä§¹¬ÀÇ_¾Ï»ìÀÚ:
		cache->addSpriteFramesWithFile("Monster/Ä§¹¬ÀÇ ¾Ï»ìÀÚ.plist");
		_code = "Ä§¹¬ÀÇ ¾Ï»ìÀÚ";
		_standCount = 5;
		_moveCount = 5;
		_attackCount = 19;
		_hitCount = 0;
		_dieCount = 15;
		_atk = 10;
		_def = 13;
		_hp = _hpm = 40;
		_delay = 0;
		_speed = 1.7;
		_gold = 40;
		_exp = 15;
		itemString.push_back("µÅÁöÀÇ ¸Ó¸®");

		shuffle(itemString.begin(), itemString.end(), g);

		for (int i = 0; i < itemString.size(); i++) {
			if (itemString[i].compare("µ·") == 0) {
				if (cuey->rand(0.0, 1.0) < 0.9) {
					_item->setItem("µ·");
				}
			}
			else {
				if (cuey->rand(0.0, 1.0) < 0.5) {
					_item->setItem(itemString[i]);
				}
			}
		}
		break;
	case Àý¸ÁÀÇ_³¯°³:
		cache->addSpriteFramesWithFile("Monster/Àý¸ÁÀÇ ³¯°³.plist");
		_code = "Àý¸ÁÀÇ ³¯°³";
		_standCount = 7;
		_moveCount = 7;
		_attackCount = 9;
		_hitCount = 0;
		_dieCount = 10;
		_atk = 10;
		_def = 10;
		_hp = _hpm = 50;
		_delay = 0;
		_speed = 1.4;
		_gold = 20;
		_exp = 20;
		itemString.push_back("µÅÁöÀÇ ¸Ó¸®");

		shuffle(itemString.begin(), itemString.end(), g);

		for (int i = 0; i < itemString.size(); i++) {
			if (itemString[i].compare("µ·") == 0) {
				if (cuey->rand(0.0, 1.0) < 0.9) {
					_item->setItem("µ·");
				}
			}
			else {
				if (cuey->rand(0.0, 1.0) < 0.5) {
					_item->setItem(itemString[i]);
				}
			}
		}
		break;
	}


	_monster = Sprite::createWithSpriteFrameName(StringUtils::format("%s_move_0.png", _code));
	_monster->setPosition(cuey->rand(100, 1890), 720);
	
	_rect = Sprite::createWithTexture(nullptr, _monster->boundingBox());
	_monster->addChild(_rect, -1);
	_rect->setAnchorPoint(Vec2(0, 0));
	_rect->setColor(Color3B::RED);
	_rect->setOpacity(70);
	_rect->setVisible(false);

	_layer->addChild(_monster);

	_hpBarLayer = Layer::create();
	_hpBarLayer->setPosition(_monster->getContentSize().width/2, _monster->getContentSize().height+10);
	_hpBarLayer->setVisible(false);
	_monster->addChild(_hpBarLayer);

	auto _hpBar_back = Sprite::create("Monster/monster_hpbar_back.png");
	_hpBar_back->setPositionX(-_hpBar_back->getContentSize().width / 2);
	_hpBar_back->setAnchorPoint(Vec2(0, 0.5f));
	_hpBarLayer->addChild(_hpBar_back, 1);

	_hpBar = Sprite::create("Monster/monster_hpbar.png");
	_hpBar->setPositionX(-_hpBar->getContentSize().width / 2);
	_hpBar->setAnchorPoint(Vec2(0, 0.5f));
	_hpBarLayer->addChild(_hpBar, 2);

	_damageNumber = Label::createWithCharMap("damage_effect.png", 36, 46, '0');
	_layer->addChild(_damageNumber);

	_jPow = 0;
	_phase = È¸Àü;

	_isFollow = false;
	_isHitTrue = false;
	_isRemove = false;
	_way = LEFT;
	_state = STAND;

	_hitDamage = 0;

}

Monster::~Monster()
{
	_layer->removeChild(_monster);
}

void Monster::tick()
{
	Vector<SpriteFrame*> frame;
	switch (_phase) {
	case È¸Àü:
		_rotate = RepeatForever::create(RotateBy::create(0.5, Vec3(0, 0, cuey->rand(180, 720))));
		_monster->runAction(_rotate);
		setPhase(³«ÇÏ);
		break;
	case ³«ÇÏ:
		_jPow += 0.1f;
		_monster->setPositionY(_monster->getPositionY() - _jPow);
		if (_monster->getPositionY() - _monster->getContentSize().height/2 < 160) {
			_monster->setPositionY(160 + _monster->getContentSize().height / 2);
			setPhase(ÂøÁö);
		}
		break;
	case ÂøÁö:
		_monster->cleanup();
		_monster->setRotation((int)_monster->getRotation3D().z % 360);
		_monster->runAction(Spawn::create(
			RotateTo::create(0.4, Vec3(0, 0, _monster->getRotation3D().z > 180 ? 0 : 720)),
			JumpBy::create(0.5, Vec2(cuey->rand(-70, 70), 0), 70, 1),
			Sequence::create(
				DelayTime::create(0.5),
				CallFunc::create(CC_CALLBACK_0(Monster::setPhase, this, ¸ð¼Ç)),
				nullptr),
			nullptr));
		setPhase(´ë±â);
		break;
	case ¸ð¼Ç:
		_isHitTrue = true;
		_monster->cleanup();
		switch (_state) {
		case HIT:
			_state = MOVE;
			for (int i = 0; i <= (_moveCount >= 3 ? 3 : _moveCount); i++) {
				frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_move_%d.png", _code, i)));
			}
			_monster->setSpriteFrame(StringUtils::format("%s_move_0.png", _code));
			_monster->setAnchorPoint(Vec2(0.5, 0.5));
			_monster->setPositionY(160 + _monster->getContentSize().height / 2);
			_rect->setTextureRect(_monster->getBoundingBox());
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
					CallFunc::create(CC_CALLBACK_0(Monster::setPhase, this, ¸ð¼Ç)),
					nullptr),
				nullptr));
			setPhase(´ë±â);
			break;
		case HITEND:
			if (_hp <= 0) {
				_hp = 0;
				_state = DEAD;
			}
			else {
				_state = MOVE;
				setPhase(¸ð¼Ç);
			}
			_rect->setTextureRect(_monster->getBoundingBox());
			_isFollow = true;
			break;
		case DEAD:
			_item->dropItem(Vec2(_monster->getPositionX(), 160));
			_monster->setAnchorPoint(Vec2(0.5, 0.5));
			_monster->setPositionY(160 + _monster->getContentSize().height / 2);
			_rect->setTextureRect(_monster->getBoundingBox());
			for (int i = 0; i <= _dieCount; i++) {
				frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_die_%d.png", _code, i)));
			}
			_monster->runAction(Sequence::create(
				Animate::create(Animation::createWithSpriteFrames(frame, 0.06f)),
				CallFunc::create(CC_CALLBACK_0(Monster::setRemove, this)),
				nullptr));
			setPhase(´ë±â);
			player->appendExp(_exp);
			break;
		default:
			if (_isFollow) {
				_monster->setSpriteFrame(StringUtils::format("%s_move_0.png", _code));
				_monster->setAnchorPoint(Vec2(0.5, 0));
				_monster->setPositionY(160);
				_rect->setTextureRect(_monster->getBoundingBox());
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
					_monster->setAnchorPoint(Vec2(0.5, 0));
					_monster->setPositionY(160);
					_rect->setTextureRect(_monster->getBoundingBox());
					if (_code == "Ä§¹¬ÀÇ ¾Ï»ìÀÚ") {
						_monster->setPositionY(120);
					}
					for (int i = 0; i <= _standCount; i++) {
						frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d.png", _code, i)));
					}
					_monster->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f))));
					_state = STAND;
					break;
				case 1:
					_monster->setSpriteFrame(StringUtils::format("%s_move_0.png", _code));
					_monster->setAnchorPoint(Vec2(0.5, 0));
					_monster->setPositionY(160);
					_rect->setTextureRect(_monster->getBoundingBox());
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
			setPhase(´ë±â);
			_monster->runAction(Sequence::create(
				DelayTime::create(2),
				CallFunc::create(CC_CALLBACK_0(Monster::setPhase, this, ¸ð¼Ç)),
				nullptr));
		}
		break;
	}

	if (_state == MOVE) {
		if (_way == LEFT) _monster->setPositionX(_monster->getPositionX() - _speed);
		if (_way == RIGHT) _monster->setPositionX(_monster->getPositionX() + _speed);
	}
	if (_monster->getPositionX() < 20) {
		_monster->setPositionX(20);
	}
	if (_monster->getPositionX() > 1960) {
		_monster->setPositionX(1960);
	}
}

void Monster::setWay(bool way)
{
	_way = (WAY)way;
	_monster->setFlippedX(way);
	_rect->setFlippedX(way);
}
