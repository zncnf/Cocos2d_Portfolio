#include "Player.h"

Player* Player::Instance = nullptr;

Player::Player()
{
	cache->addSpriteFramesWithFile("Player/Player.plist");
	cache->addSpriteFramesWithFile("Player/LavelUp1.plist");
	cache->addSpriteFramesWithFile("Player/LavelUp2.plist");
	cache->addSpriteFramesWithFile("Main/SkillSelect.plist");

	_layer = Layer::create();

	_item = new Item();

	_equip = new Equip();

	_skill = new Skill();

	_pet = new Pet();

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
	_exp = 0;
	_expm = 25;
	_gold = 0;
	_atk = 10;
	_lifem = _life = 2;
	_speed = 1;
	_isGame = false;

	ZeroMemory(&_bestTime, sizeof(_bestTime));
}

Player * Player::getInstance()
{
	if (Instance == nullptr) {
		Instance = new Player();
	}
	return Instance;
}

void Player::setLayer(Layer * layer, bool game)
{
	if(_layer != layer) _layer = layer;

	_isGame = game;
	_isStand = 1;
	_isLeft = 0;
	_isRight = 0;
	_isJump = 0;
	_isHit = 0;
	_isAttack = game ? false : true;
	_isFoot = false;
	_isDead = false;
	_isSkill = true;
	_way = false;
	_jPow = 0;
	_pickUpDelay = 0;
	_mobInRange.clear();

	_player = Layer::create();
	_layer->addChild(_player, 1);
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

	_equip->setLayer(_player);
	_skill->setLayer(_layer, _player);
	_pet->setLayer(_layer, _player);
	if (game) {
		auto UIBack = Sprite::createWithTexture(cuey->texture("Main/���â.png"));
		UIBack->setAnchorPoint(Vec2(0, 1));
		UIBack->setPosition(950, 130);
		UIBack->setOpacity(190);
		_layer->getParent()->addChild(UIBack);

		_rect = Sprite::createWithTexture(nullptr, { 0,0,30,72 });
		_player->addChild(_rect, -1);
		_rect->setPosition(0, -13);
		_rect->setTag(15);
		_rect->setColor(Color3B::RED);
		_rect->setOpacity(70);
		_rect->setVisible(false);

		_rect2 = Sprite::createWithTexture(nullptr, { 0,0,1000,200 });
		_player->addChild(_rect2, -1);
		_rect2->setAnchorPoint(Vec2(0.5f, 1));
		_rect2->setPosition(0, -13);
		_rect2->setTag(15);
		_rect2->setColor(Color3B::RED);
		_rect2->setOpacity(70);
		_rect2->setVisible(false);

		_life = getLife();

		_expLayer = Layer::create();
		_expLayer->setPosition(640, 5);
		_layer->getParent()->addChild(_expLayer);

		auto _expBar_back = Sprite::create("Map/exp_back.png");
		_expLayer->addChild(_expBar_back, 1);

		auto _expBar_back2 = Sprite::create("Map/exp_back2.png");
		_expBar_back2->setScaleX(1.004);
		_expBar_back2->setPositionX(7);
		_expLayer->addChild(_expBar_back2, 3);

		_expBar = Sprite::create("Map/exp.png");
		_expBar->setScaleX(_exp / _expm);
		_expBar->setPosition(-625, 0);
		_expBar->setAnchorPoint(Vec2(0, 0.5f));
		_expLayer->addChild(_expBar, 2);

		_lifeLayer = Layer::create();
		_lifeLayer->setPosition(0, 50);
		_player->addChild(_lifeLayer);

		auto _lifeSprite = Sprite::create("Player/life.png");
		_lifeSprite->setScale(0.1f);
		_lifeLayer->addChild(_lifeSprite);

		_lifeLabel = Label::create(StringUtils::format("%d", (int)_life), "fonts/�߳��� ��üRehular.ttf", 30);
		_lifeLayer->addChild(_lifeLabel);

		auto _skillGaugeLayer = Layer::create();
		_skillGaugeLayer->setPosition(1170, 70);
		_layer->getParent()->addChild(_skillGaugeLayer);

		_skillBox = Sprite::create(); 
		_skillGaugeLayer->addChild(_skillBox);

		if (player->getSkill()->getSpecialName().compare("") != 0) {
			_skillBox->setSpriteFrame("SkillSelect2_0.png");
			Vector<SpriteFrame*> frame;
			for (int i = 0; i <= 6; i++) frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("SkillSelect2_%d.png", i)));
			_skillBox->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1f))));
		}

		_skillGauge = Sprite::create();
		if (player->getSkill()->getSpecialName().compare("") != 0) {
			_skillGauge->setSpriteFrame(StringUtils::format("%s_icon.png", _skill->getSpecialName().getCString()));
		}
		_skillGauge->setScale(2);
		_skillGaugeLayer->addChild(_skillGauge);
		auto ptSprite = Sprite::create();
		if (player->getSkill()->getSpecialName().compare("") != 0) {
			ptSprite->setSpriteFrame(StringUtils::format("%s_iconDisabled.png", _skill->getSpecialName().getCString()));
		}
		_pt = ProgressTimer::create(ptSprite);
		_pt->setType(ProgressTimer::Type::RADIAL);
		_pt->setMidpoint(Vec2(0.5, 0.5));
		_pt->setScale(2);
		_pt->setReverseProgress(true);
		_pt->setColor(Color3B(100, 100, 100));
		_pt->setOpacity(150);
		_skillGaugeLayer->addChild(_pt);

		_lvLabel = Label::createWithTTF(StringUtils::format("LV : %d", (int)_lv), "fonts/Maplestory Bold.ttf", 30);
		_lvLabel->setAnchorPoint(Vec2(0, 0));
		_lvLabel->setPosition(1000, 50);
		_lvLabel->enableOutline(Color4B::BLACK, 1);
		_lvLabel->setOpacity(200);
		_layer->getParent()->addChild(_lvLabel);
	}

	setStand();
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
		_jPow = -getSpeed() * 0.2 - 8;
		AudioEngine::play2d("Sound/����.mp3", false, 1.0f);
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
	if (!_isDead) {
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

void Player::setAttack(bool game)
{
	if (_isHit != 1) {
		for (int i = 0; i < _player->getChildrenCount(); i++) {
			_player->getChildren().at(i)->stopActionsByFlags(10);
		}
		_player->stopActionsByFlags(10);
		_skill->playNormal();
		auto action = Sequence::create(
			CallFunc::create(CC_CALLBACK_0(Player::setAttack_Frame, this, 0)),
			DelayTime::create(0.35f),
			CallFunc::create(CC_CALLBACK_0(Player::setAttack_Frame, this, 1)),
			DelayTime::create(0.15f),
			CallFunc::create(CC_CALLBACK_0(Player::setAttack_Frame, this, 2)),
			DelayTime::create(_skill->getNormalDelay()),
			CallFunc::create(CC_CALLBACK_0(Player::setAttack_Frame, this, game ? 3 : 4)),
			nullptr
		);
		action->setFlags(10);

		_player->runAction(action); 

		_rhand->setVisible(false);
		_lhand->setVisible(false);
	}
}

void Player::setAttack_Frame(int frame)
{
	if (frame == 3) {
		if (_isJump == 1) {
			_isJump = 2;
		} else {
			setWalk();
			if (_isLeft == 2) _isLeft = 1;
			else if (_isRight == 2) _isRight = 1;
		}
		_isAttack = false;
		_mobInRange.clear();
	} else if(frame == 4) {
		setStand();
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
	_mobInRange.push_back(n);
}

void Player::setHit()
{
	if (_isHit == 0 && !_isDead) {
		_life--;
		_lifeLabel->setString(StringUtils::format("%d", (int)_life));
		if ((int)_life == 0) {
			setDead();
		}
		else {
			_isHit = 1;
			for (int i = 0; i < _player->getChildrenCount(); i++) {
				if (_player->getChildren().at(i)->getTag() != 15) _player->getChildren().at(i)->setOpacity(150);
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
	_isDead = true;
	AudioEngine::play2d("Sound/ĳ��������.mp3", false, 1.0f);
	_lifeLayer->setVisible(false);
	for (int i = 0; i < _player->getChildrenCount(); i++) {
		_player->getChildren().at(i)->stopActionsByFlags(10);
	}
	_player->stopActionsByFlags(10);

	_player->runAction(Sequence::create(
		MoveTo::create(0.3f, Vec2(_player->getPositionX(), 210)),
		Repeat::create(
			Sequence::create(
				MoveBy::create(0.2f, Vec2(3.0f, -1.0f)),
				MoveBy::create(0.2f, Vec2(1.0f, -3.0f)),
				MoveBy::create(0.2f, Vec2(-1.0f, -3.0f)),
				MoveBy::create(0.2f, Vec2(-3.0f, -1.0f)),
				MoveBy::create(0.2f, Vec2(-3.0f, 1.0f)),
				MoveBy::create(0.2f, Vec2(-1.0f, 3.0f)),
				MoveBy::create(0.2f, Vec2(1.0f, 3.0f)),
				MoveBy::create(0.2f, Vec2(3.0f, 1.0f)),
				nullptr
			) , 99999
		),
		nullptr));
		

	_body->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_dead_0_body.png")));
	_head->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("player_dead_0_head.png")));
	_arm->setVisible(false);

	_equip->setDead();
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
	_skill->setWay(way);
}

void Player::levelUp()
{
	AudioEngine::play2d("Sound/������.mp3", false, 1.0f);

	auto sprite = Sprite::create();
	sprite->setTag(15);
	sprite->setPositionY(70);
	_player->addChild(sprite);

	Vector<SpriteFrame*> frame;

	for (int i = 0; i < 21; i++) {
		frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("LavelUp_%d.png", i)));
	}
	
	sprite->runAction(Sequence::create(
		Animate::create(Animation::createWithSpriteFrames(frame, 0.08f)),
		RemoveSelf::create(true),
		nullptr));
	_exp -= _expm;
	_lv+= 1;
	_expm = _lv * 25;
	_atk = pow(_lv, 1.2) + 10;
	_lifem = _lv / 5 + 2;
	if (_speed < 4) {
		_speed = (int)(_lv / 3) * 0.1 + 1;
	}
	_lvLabel->setString(StringUtils::format("LV : %d", (int)_lv));
	_expBar->cleanup();
	_expBar->setScaleX(_exp / _expm);
	if (_exp >= _expm) {
		levelUp();
	}
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
			if (player->getSkill()->getSpecialName().compare("") != 0) {
				_skill->playSpecial();
			}
			break;
		case EventKeyboard::KeyCode::KEY_ALT:
			if (_isFoot) {
				_isJump = 2;
				_jPow = -getSpeed() * 0.2 - 8;
				AudioEngine::play2d("Sound/����.mp3", false, 1.0f);
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

void Player::tick(float delta)
{
	if (_isGame) {
		if (!_isDead) {
			_pet->tick();
			_skill->tick(delta);
			if (_skill->getDelay() > 0) {
				_isSkill = true;
				_skillBox->setVisible(false);
				_pt->setPercentage(_skill->getDelay() / _skill->getSpecialDelay() * 100);
			}
			else if (_isSkill) {
				_isSkill = false;
				_skillBox->setVisible(true);
				_pt->setPercentage(_skill->getDelay() / _skill->getSpecialDelay() * 100);
			}
			if (_isHit != 1) {
				if (_isStand == 1) { //���� 0, ��� 1, ���� 2
					if (_isLeft != 2 && _isRight != 2 && !_isAttack && _isFoot) {
						setStand();
						_isStand = 0;
					}
				}
				if (_isLeft == 1) {
					if (_isFoot && !_isAttack && _isRight != 1 && _isStand != 2) {
						_isStand = 1;
						setWalk();
					}
					if (_isRight == 0) {
						_isLeft = 2;
						if (!_isAttack && _mobInRange.empty()) setWay(false);
					}

				}
				if (_isRight == 1) {
					if (_isFoot && !_isAttack && _isLeft != 1 && _isStand != 2) {
						_isStand = 1;
						setWalk();
					}
					if (_isLeft == 0) {
						_isRight = 2;
						if (!_isAttack&& _mobInRange.empty()) setWay(true);
					}
				}
				if (_isJump == 2) {
					_isStand = 1;
					if (_isFoot) {
						_isJump = 3;
						_isFoot = false;
					}
				}
				if (!_isAttack && !_skill->getIsNormal()) {
					if (!_mobInRange.empty()) {
						_isStand = 1;
						if (_isJump == 2) _isJump = 1;
						_isAttack = true;
						setAttack();
					}
					else if (!_isFoot) {
						setJump();
					}
				}
				if (!_isFoot) {
					_jPow += 0.4f;
					_player->setPositionY(_player->getPositionY() - _jPow);
				}
			}

			if (_player->getPositionX() > 20) {
				if (_isLeft == 2) _player->setPositionX(_player->getPositionX() - getSpeed());
			}
			if (_player->getPositionX() < 1960) {
				if (_isRight == 2) _player->setPositionX(_player->getPositionX() + getSpeed());
			}

			if(_pickUpDelay > 0) _pickUpDelay--;
		}


		if (_player->getPositionX() > instance->getWinSize().width / 2 && _player->getPositionX() < 1980 - instance->getWinSize().width / 2) {
			_player->getParent()->setPositionX(instance->getWinSize().width / 2 - _player->getPositionX());
		}

		if (_player->getPositionY() < 207) {
			_player->setPositionY(207);
			setFoot();
		}
	}
}