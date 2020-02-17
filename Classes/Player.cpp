#include "Player.h"

Player* Player::Instance = nullptr;

Player::Player()
{
	_cache = SpriteFrameCache::getInstance();
	_cache->addSpriteFramesWithFile("Player/Player.plist");

	_equip = new Equip();

	//«√∑π¿ÃæÓ ª˝º∫
	_player = Layer::create();
	_player->setPosition(500, 500);

	_body = Sprite::createWithSpriteFrameName("player_stand_0_body.png");
	_player->addChild(_body, 5);

	_head = Sprite::createWithSpriteFrameName("player_stand_0_head.png");
	_player->addChild(_head, 6);

	_arm = Sprite::createWithSpriteFrameName("player_stand_0_arm.png");
	_player->addChild(_arm, 7);

	_rhand = Sprite::createWithSpriteFrameName("player_jump_0_rhand.png");
	_rhand->setVisible(false);
	_player->addChild(_rhand, 8);

	_lhand = Sprite::createWithSpriteFrameName("player_jump_0_lhand.png");
	_lhand->setVisible(false);
	_player->addChild(_lhand, 9);


	Vector<SpriteFrame*> frame[5];

	//∏ÿ√„
	for (int i = 0; i < 3; i++) {
		frame[0].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_stand_%d_body.png", i)));
		frame[1].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_stand_%d_head.png", i)));
		frame[2].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_stand_%d_arm.png", i)));
	}
	_stand.pushBack(Animate::create(Animation::createWithSpriteFrames(frame[0], 0.5f)));
	_stand.pushBack(Animate::create(Animation::createWithSpriteFrames(frame[1], 0.5f)));
	_stand.pushBack(Animate::create(Animation::createWithSpriteFrames(frame[2], 0.5f)));
	for (int i = 0; i < 3; i++) {
		frame[i].clear();
	}

	//¿Ãµø
	for (int i = 0; i < 4; i++) {
		frame[0].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_walk_%d_body.png", i)));
		frame[1].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_walk_%d_head.png", i)));
		frame[2].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_walk_%d_arm.png", i)));
	}
	_walk.pushBack(Animate::create(Animation::createWithSpriteFrames(frame[0], 0.18f)));
	_walk.pushBack(Animate::create(Animation::createWithSpriteFrames(frame[1], 0.18f)));
	_walk.pushBack(Animate::create(Animation::createWithSpriteFrames(frame[2], 0.18f)));
	for (int i = 0; i < 4; i++) {
		frame[i].clear();
	}

	_lv = 1;
	_exp = 1;
	_expm = 1;
	_gold = 1;
	_item.push_back(new Item());
	_isStand = 1;
	_isLeft = 0;
	_isRight = 0;
	_isJump = 0;
	_isAttack = false;
	_isRange = false;
	_isFoot = false;
	_isDead = false;
	_jPow = 0;
}

Player * Player::getInstance()
{
	if (Instance == nullptr) {
		Instance = new Player();
	}
	return Instance;
}

void Player::setLayer(Layer * layer)
{
	layer->addChild(_player);
}

void Player::setStand()
{
	_player->cleanup();
	auto action1 = RepeatForever::create(_stand.at(0));
	_body->runAction(action1);

	auto action2 = RepeatForever::create(_stand.at(1));
	_head->runAction(action2);

	auto action3 = RepeatForever::create(_stand.at(2));
	_arm->runAction(action3);

	_rhand->setVisible(false);
	_lhand->setVisible(false);
}

void Player::setFoot()
{
	if (_isJump != 0) {
		_jPow = -8;
	} else {
		_jPow = 0;
		_isFoot = true;
	}	
	if (!_isAttack && (_isLeft == 2 || _isRight == 2)) {
		setWalk();
	}
		
}

void Player::setWalk()
{
	_player->cleanup();
	auto action1 = RepeatForever::create(_walk.at(0));
	_body->runAction(action1);

	auto action2 = RepeatForever::create(_walk.at(1));
	_head->runAction(action2);

	auto action3 = RepeatForever::create(_walk.at(2));
	_arm->runAction(action3);

	_rhand->setVisible(false);
	_lhand->setVisible(false);
}

void Player::setJump()
{
	_player->cleanup();
	_body->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_jump_0_body.png")));
	_head->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_jump_0_head.png")));
	_arm->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_jump_0_arm.png")));

	_rhand->setVisible(true);
	_lhand->setVisible(true);
}

void Player::setAttack()
{
	_player->cleanup();
	auto action = RepeatForever::create(Sequence::create(
		CallFunc::create(CC_CALLBACK_0(Player::setAttack_Frame, this, 0)),
		DelayTime::create(0.35f),
		CallFunc::create(CC_CALLBACK_0(Player::setAttack_Frame, this, 1)),
		DelayTime::create(0.15f),
		CallFunc::create(CC_CALLBACK_0(Player::setAttack_Frame, this, 2)),
		DelayTime::create(0.35f),
		CallFunc::create(CC_CALLBACK_0(Player::setAttack_Frame, this, 3)),
		nullptr
	));
	_player->runAction(action);

	_rhand->setVisible(false);
	_lhand->setVisible(false);
}

void Player::setAttack_Frame(int frame)
{
	if (frame == 3) {
		if (_isJump == 1) _isJump = 2;
		else if (_isLeft == 2) _isLeft = 1;
		else if (_isRight == 2) _isRight = 1;
		_isAttack = false;
	}
	else {
		_body->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_swing_%d_body.png", frame)));
		_head->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_swing_%d_head.png", frame)));
		_arm->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_swing_%d_arm.png", frame)));
	};
}

void Player::setHit()
{
	_rhand->setVisible(false);
	_lhand->setVisible(false);
}

void Player::setDead()
{
	_rhand->setVisible(false);
	_lhand->setVisible(false);
}

void Player::setWay(bool way)
{
	_body->setFlippedX(way);
	_head->setFlippedX(way);
	_arm->setFlippedX(way);
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (!_isDead) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			_isLeft = 1;
			if (_isRight == 2) _isRight = 1;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			_isRight = 1;
			if (_isLeft == 2) _isLeft = 1;
			break;
		case EventKeyboard::KeyCode::KEY_CTRL:
			_isRange = !_isRange;
			break;
		case EventKeyboard::KeyCode::KEY_ALT:
			if (_isFoot) {
				_isJump = 2;
				_jPow = -8;
			}
			else {
				_isJump = 1;
			}
			break;
		}
	}
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		_isLeft = 0;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		_isRight = 0;
		break;
	case EventKeyboard::KeyCode::KEY_ALT:
		_isJump = 0;
		break;
	}
}

void Player::tick()
{
	if (!_isDead) {
		if (_isStand == 1) { //∏ÿ√„ 0, ¥Î±‚ 1, ¿˚øÎ 2
			if (_isLeft != 2 && _isRight != 2 && !_isAttack && _isFoot) {
				setStand();
				_isStand = 0;
			}
		}
		if (_isLeft == 1) {
			if (_isRight == 0) {
				_isLeft = 2;
				setWay(false);	
			}
			if (_isFoot && !_isAttack && _isRight != 1 && _isStand != 2) {
				_isStand = 1;
				setWalk();
			}
		} 
		if (_isRight == 1) {
			if (_isLeft == 0) {
				_isRight = 2;
				setWay(true);	
			}
			if (_isFoot && !_isAttack && _isLeft != 1 && _isStand != 2) {
				_isStand = 1;
				setWalk();
			}
		}
		if (_isJump == 2) {
			_isStand = 1;
			if (_isFoot) {
				_isJump = 3;
				_isFoot = false;
			}
		}
		if (!_isAttack) {
			if (_isRange) {
				_isStand = 1;
				if (_isJump == 2) _isJump = 1;
				_isAttack = true;
				setAttack();
			}
			else if(!_isFoot) {
				setJump();
			}
		} 
		if (!_isFoot) {
			_jPow += 0.5f;
			_player->setPositionY(_player->getPositionY() - _jPow);
		}
	}
	/*system("cls");
	log("stand : %d, left : %d, right : %d, jump : %d, foot : %d, attack : %d, range : %d", _isStand, _isLeft, _isRight, _isJump, _isFoot, _isAttack, _isRange);*/
	if (_player->getPositionX() > 20) {
		if (_isLeft == 2) _player->setPositionX(_player->getPositionX() - 2);
	}
	if(_player->getPositionX() < 1960) {
		if (_isRight == 2) _player->setPositionX(_player->getPositionX() + 2);
	}
}