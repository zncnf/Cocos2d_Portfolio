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

	_bg = Sprite::create("Main/오르비스bg.png");
	_bg->setAnchorPoint(Vec2(0, 0.5));
	_bg->setPositionY(645);
	this->addChild(_bg);

	_layer = Layer::create();
	_layer->setPositionX(-10);
	this->addChild(_layer, 1);

	player->setLayer(_layer, false);
	player->getPlayer()->setPosition(370, 530);
	player->setWay(true);
	player->getPet()->getMountPet()->setPosition(280, 500);
	player->getPet()->getMountPet()->setFlippedX(true);

	_equipBtn = Sprite::create("Main/장비버튼.png");
	_equipBtn->setPosition(1160, 574);
	_layer->addChild(_equipBtn);

	_skillBtn = Sprite::create("Main/스킬버튼.png");
	_skillBtn->setPosition(1160, 499);
	_layer->addChild(_skillBtn);

	_itemBtn = Sprite::create("Main/아이템버튼.png");
	_itemBtn->setPosition(1160, 424);
	_layer->addChild(_itemBtn);

	_topBtn = Sprite::create("Main/아이템버튼.png");
	_topBtn->setPosition(1234, 174);
	_layer->addChild(_topBtn);

	_isAction = true;
	_isUse = false;

	_equipLayer = EquipLayer::create();
	_equipLayer->setPosition(700, 357);
	_layer->addChild(_equipLayer);

	_skillLayer = SkillLayer::create();
	_skillLayer->setPosition(9999, 9999);
	_layer->addChild(_skillLayer, 1);

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

	/*_weaponBtn = Sprite::createWithTexture(cuey->texture("Main/무기버튼.png"));
	_weaponBtn->setTextureRect(Rect(4, 227, _weaponBtn->getContentSize().width, _weaponBtn->getContentSize().height));
	_weaponBtn->setAnchorPoint(Vec2(2, 0.5));
	_weaponBtn->setPosition(704, 645);
	_layer->addChild(_weaponBtn);*/

	this->schedule(schedule_selector(MainScene::tick));

	return true;
}

void MainScene::tick(float delta)
{
	_bg->setPositionX(_bg->getPositionX() - 0.1);
	if (_bg->getPositionX() + instance->getWinSize().width >= _bg->getContentSize().width) {
		_bg->setPositionX(0);
	}
}

void MainScene::onEnter()
{
	Scene::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(MainScene::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MainScene::onExit()
{
	//_eventDispatcher->removeAllEventListeners();

	Scene::onExit();
}

bool MainScene::onTouchBegan(Touch * touch, Event * event)
{
	_equipLayer->onTouchBegan(touch, event, _isUse ? false : true);
	_skillLayer->onTouchBegan(touch, event, _isUse ? false : true);
	_itemLayer->onTouchBegan(touch, event, _isUse ? false : true);
	_topLayer->onTouchBegan(touch, event, _isUse ? true : false);

	Vec2 pt = touch->getLocation() - _layer->getPosition();
	if (_equipBtn->getBoundingBox().containsPoint(pt)) {
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
		setClean();
		_skillLayer->setPosition(689, 356);
		_skillBg->setPosition(_skillLayer->getPosition());
		_skillLeftUI->setPosition(_skillLayer->getPosition() + Vec2(-231, 53));
		player->getPlayer()->setPosition(400, 330);
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
		setClean();
		_itemLayer->setPosition(740, 351);
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
	
}

void MainScene::onTouchCancelled(Touch * touch, Event * event)
{
}

void MainScene::onTouchEnded(Touch * touch, Event * event)
{
}
