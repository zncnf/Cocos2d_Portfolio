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
	//_layer->setPosition(700, 357);
	this->addChild(_layer);

	_equipBtn = Sprite::create("Main/장비버튼.png");
	_equipBtn->setPosition(1160, 574);
	_layer->addChild(_equipBtn);

	_skillBtn = Sprite::create("Main/스킬버튼.png");
	_skillBtn->setPosition(1160, 477);
	_layer->addChild(_skillBtn);

	_itemBtn = Sprite::create("Main/아이템버튼.png");
	_itemBtn->setPosition(1160, 407);
	_layer->addChild(_itemBtn);

	_isAction = true;

	_equipLayer = EquipLayer::create();
	_equipLayer->setPosition(700, 357);
	_layer->addChild(_equipLayer);

	_topLayer = TopLayer::create();
	_topLayer->setPosition(1750, 357);
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
	_eventDispatcher->removeAllEventListeners();

	Scene::onExit();
}

bool MainScene::onTouchBegan(Touch * touch, Event * event)
{
	_equipLayer->onTouchBegan(touch, event);

	Vec2 pt = touch->getLocation();
	if (_equipBtn->getBoundingBox().containsPoint(pt - _layer->getPosition())) {
		_equipLayer->setPosition(0, 0);
		if (_isAction) {
			_layer->runAction(Sequence::create(
				EaseExponentialInOut::create(MoveTo::create(1, Vec2(1100, 357))),
				CallFunc::create(CC_CALLBACK_0(MainScene::setisAction, this, true)),
				nullptr));
		}
		_isAction = false;
	}
	if (_skillBtn->getBoundingBox().containsPoint(pt - _layer->getPosition())) {
		_equipLayer->setPosition(9999, 9999);
	}
	if (_itemBtn->getBoundingBox().containsPoint(pt - _layer->getPosition())) {
		//_equipLayer->setPosition(9999, 9999);
		if (_isAction) {
			_layer->runAction(Sequence::create(
				EaseExponentialInOut::create(MoveTo::create(1, Vec2(303, 357))),
				CallFunc::create(CC_CALLBACK_0(MainScene::setisAction, this, true)),
				CallFunc::create(CC_CALLBACK_0(MainScene::moveTopLayer, this)),
				nullptr));
		}
		_isAction = false;
	}
	/*if (_weaponBtn->getBoundingBox().containsPoint(pt - _layer->getPosition())) {
		log("test");
	}*/
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
