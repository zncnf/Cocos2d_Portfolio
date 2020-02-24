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

	_bg = Sprite::create("Map/배경.png");
	_bg->setPosition(0, -43);
	_bg->setAnchorPoint(Vec2(0, 0));
	_layer->addChild(_bg);

	_map = Sprite::create("Map/헤네사냥터.png");
	_map->setPosition(0, -43);
	_map->setAnchorPoint(Vec2(0, 0));
	_layer->addChild(_map);

	_isViewRect = false;

	player->setLayer(_layer);

	//키보드 조작
	auto K_listner = EventListenerKeyboard::create();
	K_listner->onKeyPressed = CC_CALLBACK_2(TopScene::onKeyPressed, this);
	K_listner->onKeyReleased = CC_CALLBACK_2(TopScene::onKeyReleased, this);
	instance->getEventDispatcher()->addEventListenerWithSceneGraphPriority(K_listner, this);

	this->schedule(schedule_selector(TopScene::tick));

	return true;
}

void TopScene::tick(float delta)
{
	player->tick();
	if (cuey->rand(0, 500) == 0) {
		_monster.pushBack(new Monster(_layer));
		_monster.back()->viewRect(_isViewRect);
	}
	for (int i = 0; i < _monster.size(); i++) {
		_monster.at(i)->tick();
		_monster.at(i)->getRect();
		if (player->getRect().intersectsRect(_monster.at(i)->getRect()) && !_monster.at(i)->getIsFollow()) {
			player->setHit();
		}
		/*if (_monster.at(i)->getMonster()->getPositionY() < 100) {
			delete _monster.at(i);
			_monster.erase(_monster.begin() + i);
		}*/
	}
}

void TopScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	player->onKeyPressed(keyCode, event);
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_M:
		_monster.pushBack(new Monster(_layer));
		_monster.back()->viewRect(_isViewRect);
		break;
	case EventKeyboard::KeyCode::KEY_F1:
		_isViewRect = !_isViewRect;
		player->viewRect(_isViewRect);
		for (int i = 0; i < _monster.size(); i++) {
			_monster.at(i)->viewRect(_isViewRect);
		}
		break;
	}
}

void TopScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	player->onKeyReleased(keyCode, event);
}
