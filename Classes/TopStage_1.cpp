#include "TopStage_1.h"

Scene * TopStage_1::createScene()
{
	return TopStage_1::create();
}

bool TopStage_1::init()
{
	if (!Scene::init()) {
		return false;
	}

	_layer = Layer::create();
	this->addChild(_layer);
	_bg = Sprite::create("Map/헤네시스bg.png");
	_bg->setPosition(0, -43);
	_bg->setAnchorPoint(Vec2(0, 0));
	_layer->addChild(_bg);

	_map = Sprite::create("Map/헤네시스.png");
	_map->setPosition(0, -76);
	_map->setAnchorPoint(Vec2(0, 0));
	_layer->addChild(_map);

	_isViewRect = false;

	player->setLayer(_layer, true);

	_gold = 0;
	_time = 0;

	_goldLabel = Label::create(StringUtils::format("%d", _gold), "fonts/야놀자 야체Rehular.ttf", 35);
	_goldLabel->setPosition(instance->getWinSize().width - 100, instance->getWinSize().height - 30);
	_goldLabel->setAnchorPoint(Vec2(0, 0.5));
	_goldLabel->setColor(Color3B::YELLOW);
	_goldLabel->enableOutline(Color4B(192, 128, 64, 255), 1);
	this->addChild(_goldLabel, 50);

	_bestTimeLabel = Label::create(StringUtils::format("BEST TIME   %02d : %02d", (int)player->getBestTime(0) / 60, (int)player->getBestTime(0) % 60), "fonts/야놀자 야체Rehular.ttf", 25);
	_bestTimeLabel->setPosition(instance->getWinSize().width - 400, instance->getWinSize().height - 30);
	_bestTimeLabel->setAnchorPoint(Vec2(0, 0.5));
	_bestTimeLabel->setColor(Color3B::YELLOW);
	_bestTimeLabel->enableOutline(Color4B(150, 50, 150, 255), 1);
	this->addChild(_bestTimeLabel, 50);

	_timeLabel = Label::create(StringUtils::format("TIME   %02d : %02d", (int)_time / 60, (int)_time % 60), "fonts/야놀자 야체Rehular.ttf", 35);
	_timeLabel->setPosition(instance->getWinSize().width - 400, instance->getWinSize().height - 60);
	_timeLabel->setAnchorPoint(Vec2(0, 0.5));
	_timeLabel->setColor(Color3B(0, 255, 255));
	_timeLabel->enableOutline(Color4B::BLUE, 1);
	this->addChild(_timeLabel, 50);

	//키보드 조작
	auto K_listner = EventListenerKeyboard::create();
	K_listner->onKeyPressed = CC_CALLBACK_2(TopStage_1::onKeyPressed, this);
	K_listner->onKeyReleased = CC_CALLBACK_2(TopStage_1::onKeyReleased, this);
	instance->getEventDispatcher()->addEventListenerWithSceneGraphPriority(K_listner, this);

	this->schedule(schedule_selector(TopStage_1::tick));

	return true;
}

void TopStage_1::tick(float delta)
{
	if (!player->getIsDead()) {
		_time += delta;
		if (player->getBestTime(0) < _time) {
			player->setBestTime(0, _time);
			_bestTimeLabel->setString(StringUtils::format("BEST TIME   %02d : %02d(New)", (int)player->getBestTime(0) / 60, (int)player->getBestTime(0) % 60));
		}
	}

	_timeLabel->setString(StringUtils::format("TIME   %02d : %02d", (int)_time / 60, (int)_time % 60));
	player->tick();
	int mobRezen = 600 / pow(_time, 0.6f) + 30;
	if (cuey->rand(0, mobRezen) == 0 && !player->getIsDead()) {
		_monster.pushBack(new Monster(_layer, cuey->rand(0, 1) == 0 ? Monster::초록달팽이 : Monster::돼지));
		_monster.back()->viewRect(_isViewRect);
	}
	int obsRezen = 600 / pow(_time, 0.5f) + 30;
	if (cuey->rand(0, obsRezen) == 0 && !player->getIsDead()) {
		_obstacle.pushBack(new Obstacle("미사일"));
	}
	for (int i = 0; i < _obstacle.size(); i++) {
		_obstacle.at(i)->tick();
		if (_obstacle.at(i)->getIsAttack()) {
			if (_obstacle.at(i)->getIsSectRect()) {
				player->setHit();
			}
		}
		if (_obstacle.at(i)->getIsRemove()) {
			_layer->removeChild(_obstacle.at(i)->getSprite());
			delete _obstacle.at(i);
			_obstacle.erase(_obstacle.begin() + i);
			break;
		}
	}

	char str[1048] = "";
	vector<float> itemX;
	for (int i = 0; i < _monster.size(); i++) {
		for (int j = 0; j < _monster.at(i)->getItem()->getItemSize(); j++) {
			if (_monster.at(i)->getItem()->getIsPickUp(j)) {
				if (player->getRect2().intersectsRect(_monster.at(i)->getItem()->getRect(j))) {
					bool isItemX = false;
					for (int k = 0; k < itemX.size(); k++) {
						if (itemX[k] == _monster.at(i)->getItem()->getItemPosition(j).x) isItemX = true;
					}
					if (!isItemX) itemX.push_back(_monster.at(i)->getItem()->getItemPosition(j).x);
				}
			}
		}
	}
	bool isItamInPlayer = false;
	if (itemX.size() == 0 &&
		(player->getPlayer()->getPositionX() + 150 < player->getPet()->getMountPet()->getPositionX() ||
			player->getPlayer()->getPositionX() - 150 > player->getPet()->getMountPet()->getPositionX())) {
		isItamInPlayer = true;
		itemX.push_back(player->getPlayer()->getPositionX() + (player->getPlayer()->getPositionX() > player->getPet()->getMountPet()->getPositionX() ? 10 : -10));
	}
	if (!player->getIsDead()) {
		if (itemX.empty()) {
			if (!player->getPet()->getIsStand()) player->getPet()->setStand();
		}
		else {
			if (!player->getPet()->getIsMove()) player->getPet()->setMove();
			if (player->getPet()->getMountPet()->getPositionX() > itemX[0]) {
				player->getPet()->getMountPet()->setFlippedX(false);
				player->getPet()->getMountPet()->setPositionX(player->getPet()->getMountPet()->getPositionX() - player->getSpeed() * (isItamInPlayer ? 1.0f : 1.8f));
			}
			else {
				player->getPet()->getMountPet()->setFlippedX(true);
				player->getPet()->getMountPet()->setPositionX(player->getPet()->getMountPet()->getPositionX() + player->getSpeed() * (isItamInPlayer ? 1.0f : 1.8f));
			}
		}
	}
	for (int i = 0; i < _monster.size(); i++) {
		_monster.at(i)->tick();
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
		for (int j = 0; j < _monster.at(i)->getItem()->getItemSize(); j++) {
			if (_monster.at(i)->getItem()->getIsPickUp(j)) {
				if (player->getRect().intersectsRect(_monster.at(i)->getItem()->getRect(j)) && player->getIsPickUp()) {
					_monster.at(i)->getItem()->pickupItem(player->getPlayer(), j);
					player->setPickUp();
				}
				else if (player->getPet()->getMountPet()->getBoundingBox().intersectsRect(_monster.at(i)->getItem()->getRect(j)) && player->getPet()->getIsPickUp()) {
					_monster.at(i)->getItem()->pickupItem(player->getPet()->getMountPet(), j);
					player->getPet()->setPickUp();
				}
			}
			if (_monster.at(i)->getItem()->getIsGet(j)) {
				if (_monster.at(i)->getItem()->getName(j).compare("돈") == 0) {
					int gold = _monster.at(i)->getGold();
					player->appendGold(gold);
					_gold += gold;
					_goldLabel->setString(StringUtils::format("%d", _gold));
				}
				else {
					player->getItem()->setItem(_monster.at(i)->getItem()->getName(j));
					log("%s(%d)을(를) 획득하였습니다.",
						player->getItem()->getName(player->getItem()->getId(_monster.at(i)->getItem()->getName(j))).getCString(),
						player->getItem()->getCount(player->getItem()->getId(_monster.at(i)->getItem()->getName(j))));
				}
				_monster.at(i)->getItem()->removeItem(j);
			}
		}
		if (_monster.at(i)->getIsRemove() && _monster.at(i)->getItem()->getIsRemove()) {
			delete _monster.at(i);
			_monster.erase(_monster.begin() + i);
			i--;
		}
	}
	if (strcmp(str, "") != 0) {
		log("%s", str);
	}
}

void TopStage_1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	player->onKeyPressed(keyCode, event);
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_M:
		_monster.pushBack(new Monster(_layer, Monster::초록달팽이));
		_monster.back()->viewRect(_isViewRect);
		break;
	case EventKeyboard::KeyCode::KEY_R:
		player->offGame();
		this->cleanup();
		init();
		instance->replaceScene(IntroScene::createScene());
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

void TopStage_1::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	player->onKeyReleased(keyCode, event);
}

void TopStage_1::onEnter()
{
	Scene::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(TopStage_1::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TopStage_1::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TopStage_1::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(TopStage_1::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void TopStage_1::onExit()
{
	_eventDispatcher->removeAllEventListeners();

	Scene::onExit();
}

bool TopStage_1::onTouchBegan(Touch * touch, Event * event)
{
	//auto touchPoint = touch->getLocation();

	cuey->glview()->setCursor("Cursor_down.png");

	return true;
}

void TopStage_1::onTouchMoved(Touch * touch, Event * event)
{
	PtInRect(nullptr, { 1,1 });
	cuey->pt = touch->getLocation() - _layer->getPosition();
	for (int i = 0; i < _obstacle.size(); i++) {
		if (_obstacle.at(i)->getRect().containsPoint(cuey->pt)) {
			log("%d, %d", (int)cuey->pt.x, (int)cuey->pt.y);
		}
	}
}

void TopStage_1::onTouchEnded(Touch * touch, Event * event)
{
	cuey->glview()->setCursor("Cursor_up.png");
}

void TopStage_1::onTouchCancelled(Touch * touch, Event * event)
{

}