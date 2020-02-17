#include "TopScene.h"

Scene * TopScene::createScene()
{
	return TopScene::create();
}

bool TopScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	_layer = Layer::create();
	this->addChild(_layer);

	_map = Sprite::create("Map/배경.png");
	_map->setAnchorPoint(Vec2(0, 0));
	_layer->addChild(_map);

	_map = Sprite::create("Map/헤네사냥터.png");
	_map->setAnchorPoint(Vec2(0, 0));
	_layer->addChild(_map);

	Player::getInstance()->setLayer(_layer);

	//키보드 조작
	auto K_listner = EventListenerKeyboard::create();
	K_listner->onKeyPressed = CC_CALLBACK_2(TopScene::onKeyPressed, this);
	K_listner->onKeyReleased = CC_CALLBACK_2(TopScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(K_listner, this);

	this->schedule(schedule_selector(TopScene::tick));

	return true;
}

void TopScene::tick(float delta)
{
	Player::getInstance()->tick();
	//1280, 720
	if (Player::getInstance()->getPlayer()->getPositionX() > 640 && Player::getInstance()->getPlayer()->getPositionX() < 1980 - 640) {
		if (Player::getInstance()->getIsLeft()) {
			_layer->setPositionX(_layer->getPositionX() + 2);
		}
		if (Player::getInstance()->getIsRight()) {
			_layer->setPositionX(_layer->getPositionX() - 2);
		}
	}

	if (Player::getInstance()->getPlayer()->getPositionY() < _map->getPositionY() + 250) {
		Player::getInstance()->getPlayer()->setPositionY(_map->getPositionY() + 250);
		Player::getInstance()->setFoot();
	}

}

void TopScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	Player::getInstance()->onKeyPressed(keyCode, event);
}

void TopScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	Player::getInstance()->onKeyReleased(keyCode, event);
}
