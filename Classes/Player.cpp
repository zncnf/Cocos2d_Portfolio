#include "Player.h"

Player* Player::Instance = nullptr;

Player::Player()
{
	cache->addSpriteFramesWithFile("Player/Player.plist");

	//�÷��̾� ����
	_player = Layer::create();
	_player->setAnchorPoint(Vec2(0, 0));
	_player->setPosition(500, 500);

	_body = Sprite::createWithSpriteFrameName("player_stand_0_body.png");
	_player->addChild(_body, 5);

	_head = Sprite::createWithSpriteFrameName("player_stand_0_head.png");
	_player->addChild(_head, 10);

	_arm = Sprite::createWithSpriteFrameName("player_stand_0_arm.png");
	_player->addChild(_arm, 15);

	_rhand = Sprite::createWithSpriteFrameName("player_jump_0_rhand.png");
	_rhand->setVisible(false);
	_player->addChild(_rhand, 20);

	_lhand = Sprite::createWithSpriteFrameName("player_jump_0_lhand.png");
	_lhand->setVisible(false);
	_player->addChild(_lhand, 25);

	_equip = new Equip(_player);

	_skill = new Skill(_player);

	_rect = Sprite::createWithTexture(nullptr, {0,0,30,72});
	_player->addChild(_rect);
	_rect->setPosition(0, -13);
	_rect->setTag(15);
	_rect->setColor(Color3B::RED);
	_rect->setOpacity(100);
	_rect->setVisible(false);

	Vector<SpriteFrame*> frame[4];

	//����
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

	//�̵�
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
	_isRange = -1;
	_isHit = 0;
	_isAttack = false;
	_isFoot = false;
	_isDead = false;
	_way = false;
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
	layer->addChild(_player, 50);
}

void Player::setStand()
{
	if (_isHit != 1) {
		for (int i = 0; i < _player->getChildrenCount(); i++) {
			_player->getChildren().at(i)->stopActionsByFlags(10);
		}
		_player->stopActionsByFlags(10);

		auto action1 = RepeatForever::create(_stand.at(0));
		action1->setFlags(10);
		_body->runAction(action1);

		auto action2 = RepeatForever::create(_stand.at(1));
		action2->setFlags(10);
		_head->runAction(action2);

		auto action3 = RepeatForever::create(_stand.at(2));
		action3->setFlags(10);
		_arm->runAction(action3);

		_rhand->setVisible(false);
		_lhand->setVisible(false);

		_equip->setStand();
	}
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
	if (_isHit != 1) {
		for (int i = 0; i < _player->getChildrenCount(); i++) {
			_player->getChildren().at(i)->stopActionsByFlags(10);
		}
		_player->stopActionsByFlags(10);

		auto action1 = RepeatForever::create(_walk.at(0));
		action1->setFlags(10);
		_body->runAction(action1);

		auto action2 = RepeatForever::create(_walk.at(1));
		action2->setFlags(10);
		_head->runAction(action2);

		auto action3 = RepeatForever::create(_walk.at(2));
		action3->setFlags(10);
		_arm->runAction(action3);

		_rhand->setVisible(false);
		_lhand->setVisible(false);

		_equip->setWalk();
	}
}

void Player::setJump()
{
	if (_isHit != 1) {
		for (int i = 0; i < _player->getChildrenCount(); i++) {
			_player->getChildren().at(i)->stopActionsByFlags(10);
		}
		_player->stopActionsByFlags(10);

		_body->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_jump_0_body.png")));
		_head->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_jump_0_head.png")));
		_arm->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_jump_0_arm.png")));

		_rhand->setVisible(true);
		_lhand->setVisible(true);

		_equip->setJump();
	}
}

void Player::setAttack()
{
	if (_isHit != 1) {
		for (int i = 0; i < _player->getChildrenCount(); i++) {
			_player->getChildren().at(i)->stopActionsByFlags(10);
		}
		_player->stopActionsByFlags(10);
		_skill->playNormal();
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
		action->setFlags(10);
		_player->runAction(action);

		_rhand->setVisible(false);
		_lhand->setVisible(false);
	}
}

void Player::setAttack_Frame(int frame)
{
	if (frame == 3) {
		if (_isJump == 1) _isJump = 2;
		else if (_isLeft == 2) _isLeft = 1;
		else if (_isRight == 2) _isRight = 1;
		_isAttack = false;
		_isRange = -1;
	}
	else if(_isAttack) {
		_body->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_swing_%d_body.png", frame)));
		_head->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_swing_%d_head.png", frame)));
		_arm->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_swing_%d_arm.png", frame)));

		_equip->setAttack(frame);
	};
}

void Player::setRange(int n)
{
	_isRange = n;
}

void Player::setHit()
{
	if (_isHit == 0) {
		_isHit = 1;
		for (int i = 0; i < _player->getChildrenCount(); i++) {
			if(_player->getChildren().at(i)->getTag() != 15) _player->getChildren().at(i)->setOpacity(150);
		}
		auto action = Sequence::create(
			JumpBy::create(0.2f, Vec2(_way ? -15 : 15, 0), 10, 1),
			CallFunc::create(CC_CALLBACK_0(Player::setHitCount, this, 2)),
			DelayTime::create(2.0f),
			CallFunc::create(CC_CALLBACK_0(Player::setHitCount, this, 0)),
			nullptr);
		_player->runAction(action);
	}
}

void Player::setHitCount(int n)
{
	_isHit = n;
	if (_isHit == 0) {
		for (int i = 0; i < _player->getChildrenCount(); i++) {
			if (_player->getChildren().at(i)->getTag() != 15) _player->getChildren().at(i)->setOpacity(255);
		}
	}
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
	_rhand->setFlippedX(way);
	_lhand->setFlippedX(way);
	_way = way;

	_equip->setWay(way);
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
			_isRange = _isRange == -1 ? 0 : -1;
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
		case EventKeyboard::KeyCode::KEY_Q:
			//_equip->setWeapon("Ʃ��");
			log("Ʃ��ȹ��");
			break;
		case EventKeyboard::KeyCode::KEY_W:
			for (int i = 0; i < _equip->getMyWeaponSize(); i++) {
				log("%d : %s", i, _equip->getMyWeaponName(i).getCString());
			}
			break;
		case EventKeyboard::KeyCode::KEY_E:
			//_equip->mountWeapon(0);
			setStand();
			setAttack_Frame(3);
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
	if (!_isDead && _isHit != 1) {
		if (_isStand == 1) { //���� 0, ��� 1, ���� 2
			if (_isLeft != 2 && _isRight != 2 && !_isAttack && _isFoot) {
				setStand();
				_isStand = 0;
			}
		}
		if (_isLeft == 1) {
			if (_isRight == 0) {
				_isLeft = 2;
				if (!_isAttack) setWay(false);
			}
			if (_isFoot && !_isAttack && _isRight != 1 && _isStand != 2) {
				_isStand = 1;
				setWalk();
			}
		} 
		if (_isRight == 1) {
			if (_isLeft == 0) {
				_isRight = 2;
				if (!_isAttack) setWay(true);
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
			if (_isRange != -1) {
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
			_jPow += 0.4f;
			_player->setPositionY(_player->getPositionY() - _jPow);
		}
	}

	if (_player->getPositionX() > 20) {
		if (_isLeft == 2) _player->setPositionX(_player->getPositionX() - 2);
	}
	if(_player->getPositionX() < 1960) {
		if (_isRight == 2) _player->setPositionX(_player->getPositionX() + 2);
	}

	if (_player->getPositionX() > 640 && _player->getPositionX() < 1340) {
		if (getIsLeft()) {
			_player->getParent()->setPositionX(_player->getParent()->getPositionX() + 2);
		}
		if (getIsRight()) {
			_player->getParent()->setPositionX(_player->getParent()->getPositionX() - 2);
		}
	}

	if (_player->getPositionY() < 207) {
		_player->setPositionY(207);
		setFoot();
	}
}