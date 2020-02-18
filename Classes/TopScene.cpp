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

	_bg = Sprite::create("Map/���.png");
	_bg->setPosition(0, -43);
	_bg->setAnchorPoint(Vec2(0, 0));
	_layer->addChild(_bg);

	_map = Sprite::create("Map/��׻����.png");
	_map->setPosition(0, -43);
	_map->setAnchorPoint(Vec2(0, 0));
	_layer->addChild(_map);

	player->setLayer(_layer);

	//Ű���� ����
	auto K_listner = EventListenerKeyboard::create();
	K_listner->onKeyPressed = CC_CALLBACK_2(TopScene::onKeyPressed, this);
	K_listner->onKeyReleased = CC_CALLBACK_2(TopScene::onKeyReleased, this);
	instance->getEventDispatcher()->addEventListenerWithSceneGraphPriority(K_listner, this);


	b2Vec2 gravity = b2Vec2(0.0f, -9.8f);

	_world = new b2World(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, -0);

	b2Body* groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//�Ʒ���
	groundEdge.Set(b2Vec2(0, 170 / PTM_RATIO), b2Vec2(2000 / PTM_RATIO, 170 / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//����
	groundEdge.Set(b2Vec2(0, 800 / PTM_RATIO),
		b2Vec2(2000 / PTM_RATIO, 800 / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//����
	groundEdge.Set(b2Vec2(0, 170 / PTM_RATIO), b2Vec2(0, 800 / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//������
	groundEdge.Set(b2Vec2(2000 / PTM_RATIO, 800 / PTM_RATIO),
		b2Vec2(2000 / PTM_RATIO, 170 / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	this->schedule(schedule_selector(TopScene::tick));

	return true;
}

void TopScene::tick(float delta)
{
	player->tick();
	/*system("cls");
	log("%f\n%f\n%f\n%f\n%f\n%f", player->getPlayer()->boundingBox().getMaxX(),
		player->getPlayer()->boundingBox().getMaxY(),
		player->getPlayer()->boundingBox().getMidX(),
		player->getPlayer()->boundingBox().getMidY(),
		player->getPlayer()->boundingBox().getMinX(),
		player->getPlayer()->boundingBox().getMinY());*/
	if(cuey->rand(0,5) == 0) 
	_monster.pushBack(new Monster(_layer, _world));
	for (int i = 0; i < _monster.size(); i++) {
		_monster.at(i)->tick();
		//log("%f, %f", _monster.back()->getPositionX(), _monster.back()->getPositionY());

		if (player->getPlayer()->boundingBox().intersectsRect(_monster.at(i)->getMonster()->boundingBox())) {
			//player->setRange(i);
			//log("%f / %f", player->getPlayer()->boundingBox().getMaxX(), _monster.at(i)->getMonster()->boundingBox());
		}
		/*if (_monster.at(i)->getMonster()->getPositionY() < 100) {
			delete _monster.at(i);
			_monster.erase(_monster.begin() + i);
		}*/
	}
	
	//Box2D �Ŵ��� ���� �����ġ
	int velocityIterations = 8;
	int positionIterations = 3;

	//Step : ���� ���踦 �ùķ��̼��Ѵ�.
	_world->Step(delta, velocityIterations, positionIterations);

	//��� ���� ��ü���� ��ũ�� ����Ʈ�� ����Ǿ� �����غ� �� �ֵ��� �����Ǿ� �ִ�.
	//������� ��ü��ŭ ������ �����鼭 �ٵ� ���� ��������Ʈ�� ���⼭ �����Ѵ�.
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr)
		{
			Sprite* spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(
				Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));

			/*log("%f\n%f\n%f\n%f\n%f\n%f", spriteData->boundingBox().getMaxX(),
				spriteData->boundingBox().getMaxY(),
				spriteData->boundingBox().getMidX(),
				spriteData->boundingBox().getMidY(),
				spriteData->boundingBox().getMinX(),
				spriteData->boundingBox().getMinY());*/
			
		}
	}
	

}

void TopScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	player->onKeyPressed(keyCode, event);
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_M:
		_monster.pushBack(new Monster(_layer, _world));
		break;
	}
}

void TopScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	player->onKeyReleased(keyCode, event);
}
