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

	_gold = 0;
	_time = 0;

	_goldLabel = Label::create(StringUtils::format("%d", _gold), "fonts/야놀자 야체Rehular.ttf", 35);
	_goldLabel->setPosition(instance->getWinSize().width - 100, instance->getWinSize().height - 30);
	_goldLabel->setAnchorPoint(Vec2(0, 0.5));
	_goldLabel->setColor(Color3B::YELLOW);
	_goldLabel->enableOutline(Color4B(192, 128, 64, 255), 1);
	this->addChild(_goldLabel, 50);

	_timeLabel = Label::create(StringUtils::format("TIME   %02d : %02d", (int)_time / 60, (int)_time % 60), "fonts/야놀자 야체Rehular.ttf", 35);
	_timeLabel->setPosition(instance->getWinSize().width - 400, instance->getWinSize().height - 30);
	_timeLabel->setAnchorPoint(Vec2(0, 0.5));
	_timeLabel->setColor(Color3B(0, 255, 255));
	_timeLabel->enableOutline(Color4B::BLUE, 1);
	this->addChild(_timeLabel, 50);

	//키보드 조작
	auto K_listner = EventListenerKeyboard::create();
	K_listner->onKeyPressed = CC_CALLBACK_2(TopScene::onKeyPressed, this);
	K_listner->onKeyReleased = CC_CALLBACK_2(TopScene::onKeyReleased, this);
	instance->getEventDispatcher()->addEventListenerWithSceneGraphPriority(K_listner, this);

	this->schedule(schedule_selector(TopScene::tick));

	return true;
}

TopScene::~TopScene()
{
}

void TopScene::tick(float delta)
{
	if(!player->getIsDead()) _time += delta;
	_timeLabel->setString(StringUtils::format("TIME   %02d : %02d", (int)_time / 60, (int)_time % 60));
	player->tick();
	int mobRezen = 600 / pow(_time,0.6f) + 30;
	if (cuey->rand(0, mobRezen) == 0 && !player->getIsDead()) {
		_monster.pushBack(new Monster(_layer));
		_monster.back()->viewRect(_isViewRect);
	}
	char str[1048] = "";
	for (int i = 0; i < _monster.size(); i++) {
		_monster.at(i)->tick();
		_monster.at(i)->getRect();
		if (!_monster.at(i)->getIsDead()) {
			if (player->getRect().intersectsRect(_monster.at(i)->getRect())) {
				player->setHit();
			}
			if (player->getSkill()->getNormalRect().intersectsRect(_monster.at(i)->getRect()) &&
				!player->getIsAttack() && !player->getSkill()->getIsNormal() && player->getSkill()->getNormalCount() > player->getMobRangeSize() &&
				_monster.at(i)->getIsHitTrue()) {
				player->setRange(i);
				_monster.at(i)->setHit(player->getNormalDamage());
				//sprintf(str, "%s%d : %d/%d, ", str, i, (int)_monster.at(i)->getHp(), (int)_monster.at(i)->getHpm());
			}
		}
		if (_monster.at(i)->getIsRemove()) {
			delete _monster.at(i);
			_monster.erase(_monster.begin() + i);
			i--;
		}
	}
	if (strcmp(str, "") != 0) {
		log("%s", str);
	}
}

void TopScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	auto scene = IntroScene::createScene();
	player->onKeyPressed(keyCode, event);
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_M:
		_monster.pushBack(new Monster(_layer));
		_monster.back()->viewRect(_isViewRect);
		break;
	case EventKeyboard::KeyCode::KEY_R:
		for (int i = 0; i < _layer->getChildren().size(); i++) {
			_layer->getChildren().at(i)->removeAllChildrenWithCleanup(true);
		}
		_layer->removeAllChildrenWithCleanup(true);
		//this->removeAllChildrenWithCleanup(true);
		instance->replaceScene(scene);
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

void TopScene::onEnter()
{
	Scene::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(TopScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TopScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TopScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void TopScene::onExit()
{
	_eventDispatcher->removeAllEventListeners();

	Scene::onExit();
}

bool TopScene::onTouchBegan(Touch * touch, Event * event)
{
	//auto touchPoint = touch->getLocation();

	cuey->glview()->setCursor("Cursor_down.png");

	return true;
}

void TopScene::onTouchMoved(Touch * touch, Event * event)
{
	
}

void TopScene::onTouchEnded(Touch * touch, Event * event)
{
	cuey->glview()->setCursor("Cursor_up.png");
}

void TopScene::onTouchCancelled(Touch * touch, Event * event)
{
}