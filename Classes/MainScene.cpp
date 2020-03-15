#include "MainScene.h"

Scene * MainScene::createScene()
{
	return MainScene::create();
}

bool MainScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	return true;
}

void MainScene::tick(float delta)
{
	_bg->setPositionX(_bg->getPositionX() - 0.1);
	if (_bg->getPositionX() - instance->getWinSize().width < -_bg->getContentSize().width) {
		_bg->setPositionX(0);
	}
	_goldLabel->setString(StringUtils::format("GOLD : %d", (int)player->getGold()));
}

void MainScene::onEnter()
{
	Scene::onEnter();

	
	/*if (AudioEngine::getState(_soundBs) != AudioEngine::AudioState::PLAYING && AudioEngine::getState(_soundBg1) != AudioEngine::AudioState::PLAYING && !BgSoundClear)
	{
		_soundBg1 = AudioEngine::play2d("Sound/bg_stage.mp3", true, 0.6);
		BgSoundClear = true;
	}*/

	_bg = Sprite::create("Main/오르비스bg.png");
	_bg->setAnchorPoint(Vec2(0, 0.5));
	_bg->setPositionY(645);
	this->addChild(_bg);

	_layer = Layer::create();
	_layer->setPositionX(-10);
	this->addChild(_layer, 1);

	_equipBtn = Sprite::create("Main/장비버튼.png");
	_equipBtn->setPosition(1160, 574);
	_layer->addChild(_equipBtn);

	_skillBtn = Sprite::create("Main/스킬버튼.png");
	_skillBtn->setPosition(1160, 499);
	_layer->addChild(_skillBtn);

	_itemBtn = Sprite::create("Main/아이템버튼.png");
	_itemBtn->setPosition(1160, 424);
	_layer->addChild(_itemBtn);

	_topBtn = Sprite::create("Main/탑버튼.png");
	_topBtn->setPosition(1234, 174);
	_layer->addChild(_topBtn);

	_isAction = true;
	_isUse = false;

	_equipLayer = EquipLayer::create();
	_equipLayer->setPosition(700, 357);
	_layer->addChild(_equipLayer);

	_skillLayer = SkillLayer::create();
	_skillLayer->setPosition(9999, 9999);
	_layer->addChild(_skillLayer, 50);

	_skillBg = Sprite::create("Main/스킬창.png");
	_skillBg->setPosition(_skillLayer->getPosition());
	_layer->addChild(_skillBg);

	_skillLeftUI = Sprite::create("Main/스킬창좌측UI.png");
	_skillLeftUI->setPosition(_skillLayer->getPosition() + Vec2(-231, 53));
	_layer->addChild(_skillLeftUI);

	_itemLayer = ItemLayer::create();
	_itemLayer->setPosition(9999, 9999);
	_layer->addChild(_itemLayer);

	_topLayer = TopLayer::create();
	_topLayer->setPosition(1650, 357);
	_layer->addChild(_topLayer);

	_goldLabel = Label::create(StringUtils::format("GOLD : %d", (int)player->getGold()), "fonts/야놀자 야체Rehular.ttf", 30);
	_goldLabel->setPosition(instance->getWinSize().width - 160, instance->getWinSize().height - 50);
	_goldLabel->setAnchorPoint(Vec2(0, 0.5));
	_goldLabel->setColor(Color3B::YELLOW);
	_goldLabel->enableOutline(Color4B(192, 128, 64, 255), 1);
	_layer->addChild(_goldLabel, 50);

	for (int i = 0; i < 15; i++) {
		player->getItem()->setItem("달팽이의 껍질");
		player->getItem()->setItem("돼지의 머리");
		player->getItem()->setItem("부러진 뿔");
		player->getItem()->setItem("좀비의 잃어버린 금니");
		player->getItem()->setItem("좀비의 잃어버린 어금니");
		player->getItem()->setItem("어둠의 크리스탈");
		player->getItem()->setItem("어둠의 조각");
		player->getItem()->setItem("어둠의 날개");
		player->getItem()->setItem("어둠의 돌");
	}
	player->appendGold(10000);

	player->getSkill()->setNormal("파이널 블로우");
	player->getSkill()->setNormal("디바이드");
	player->getSkill()->setSpecial("쉘터");
	player->getSkill()->setSpecial("다크 포그");

	player->setLayer(_layer, false);
	player->setStand();
	player->getPlayer()->setPosition(370, 530);
	player->setWay(true);
	player->getPet()->getMountPet()->setPosition(280, 500);
	player->getPet()->getMountPet()->setFlippedX(true);

	this->schedule(schedule_selector(MainScene::tick));

	this->scheduleOnce(schedule_selector(MainScene::bgmPlay), 1);

	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(MainScene::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MainScene::onExit()
{
	_eventDispatcher->removeEventListener(listener);
	//_eventDispatcher->removeAllEventListeners();
	AudioEngine::stop(_bgm);

	Scene::onExit();
}

bool MainScene::onTouchBegan(Touch * touch, Event * event)
{
	_equipLayer->onTouchBegan(touch, event, _isUse ? false : true);
	_skillLayer->onTouchBegan(touch, event, _isUse ? false : true);
	_itemLayer->onTouchBegan(touch, event, _isUse ? false : true);
	_topLayer->onTouchBegan(touch, event, _isUse ? true : false);

	cuey->glview()->setCursor("Cursor_down.png");

	Vec2 pt = touch->getLocation() - _layer->getPosition();
	if (_equipBtn->getBoundingBox().containsPoint(pt)) {
		AudioEngine::play2d("Sound/창변경.mp3", false, 1.0f);
		setClean();
		_equipLayer->setPosition(700, 357);
		player->getPlayer()->setPosition(370, 530);
		player->getPet()->getMountPet()->setPosition(280, 500);
		if (_isAction) {
			_isAction = false;
			_isUse = false;
			_layer->runAction(Sequence::create(
				EaseExponentialInOut::create(MoveTo::create(1, Vec2(-10, 0))),
				CallFunc::create(CC_CALLBACK_0(MainScene::setisAction, this, true)),
				nullptr));
			_topBtn->runAction(EaseExponentialInOut::create(MoveTo::create(1, Vec2(1234, 174))));
		}
	}
	else if (_skillBtn->getBoundingBox().containsPoint(pt)) {
		AudioEngine::play2d("Sound/창변경.mp3", false, 1.0f);
		setClean();
		_skillLayer->setPosition(689, 356);
		_skillBg->setPosition(_skillLayer->getPosition());
		_skillLeftUI->setPosition(_skillLayer->getPosition() + Vec2(-231, 53));
		player->getPlayer()->setPosition(380, 330);
		if (_isAction) {
			_isAction = false;
			_isUse = false;
			_layer->runAction(Sequence::create(
				EaseExponentialInOut::create(MoveTo::create(1, Vec2(-10, 0))),
				CallFunc::create(CC_CALLBACK_0(MainScene::setisAction, this, true)),
				nullptr));
			_topBtn->runAction(EaseExponentialInOut::create(MoveTo::create(1, Vec2(1234, 174))));
		}
	}
	else if (_itemBtn->getBoundingBox().containsPoint(pt)) {
		AudioEngine::play2d("Sound/창변경.mp3", false, 1.0f);
		setClean();
		_itemLayer->setPosition(772, 351);
		if (_isAction) {
			_isAction = false;
			_isUse = false;
			_layer->runAction(Sequence::create(
				EaseExponentialInOut::create(MoveTo::create(1, Vec2(-10, 0))),
				CallFunc::create(CC_CALLBACK_0(MainScene::setisAction, this, true)),
				nullptr));
			_topBtn->runAction(EaseExponentialInOut::create(MoveTo::create(1, Vec2(1234, 174))));
		}
	} else if (_topBtn->getBoundingBox().containsPoint(pt)) {
		AudioEngine::play2d("Sound/창변경.mp3", false, 1.0f);
		if (_isAction && !_isUse) {
			_isAction = false;
			_isUse = true;
			_layer->runAction(Sequence::create(
				EaseExponentialInOut::create(MoveTo::create(1, Vec2(-1103, 0))),
				CallFunc::create(CC_CALLBACK_0(MainScene::setisAction, this, true)),
				CallFunc::create(CC_CALLBACK_0(MainScene::setClean, this)),
				nullptr));
			_topBtn->runAction(Sequence::create(
				DelayTime::create(0.3),
				EaseExponentialInOut::create(MoveTo::create(0.4, Vec2(1469, 174))),
				nullptr));
		}
	}

	return true;
}

void MainScene::onTouchMoved(Touch * touch, Event * event)
{
	_itemLayer->onTouchMoved(touch, event, _isUse ? false : true);
}

void MainScene::onTouchCancelled(Touch * touch, Event * event)
{
}

void MainScene::onTouchEnded(Touch * touch, Event * event)
{
	_equipLayer->onTouchEnded(touch, event, _isUse ? false : true);
	_skillLayer->onTouchEnded(touch, event, _isUse ? false : true);
	_itemLayer->onTouchEnded(touch, event, _isUse ? false : true);

	cuey->glview()->setCursor("Cursor_up.png");
}

void MainScene::bgmPlay(float delta)
{
	_bgm = AudioEngine::play2d("Sound/Shinin'Harbor.mp3", true, 1.0f);
}
