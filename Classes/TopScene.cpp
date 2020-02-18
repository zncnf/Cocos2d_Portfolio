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

	player->setLayer(_layer);

	//키보드 조작
	auto K_listner = EventListenerKeyboard::create();
	K_listner->onKeyPressed = CC_CALLBACK_2(TopScene::onKeyPressed, this);
	K_listner->onKeyReleased = CC_CALLBACK_2(TopScene::onKeyReleased, this);
	instance->getEventDispatcher()->addEventListenerWithSceneGraphPriority(K_listner, this);

	//---월드 생성---



	//중력의 작용 방향
	b2Vec2 gravity = b2Vec2(0.0f, -20.0f);

	//월드 생성
	_world = new b2World(gravity);

	//아무 것도 안 하고 있을 때 바디들의 처리
	_world->SetAllowSleeping(true);

	//물리연산을 계속해서 수행할 건지의 여부
	_world->SetContinuousPhysics(true);



	//바디 정보
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	//groundBodyDef의 정보를 가져와 바디를 만든다
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);

	//추후 테두리를 그릴 오브젝트 만들기
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//ground 객체에 Set으로 선을 생성
	//이후 바디(groundBody)에 모양(groundEdge)을 접목시켜 고정

	//아랫쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(2000 / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//윗쪽
	groundEdge.Set(b2Vec2(0, 800 / PTM_RATIO),
		b2Vec2(2000 / PTM_RATIO, 800 / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//왼쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, 800 / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//오른쪽
	groundEdge.Set(b2Vec2(2000 / PTM_RATIO, 800 / PTM_RATIO),
		b2Vec2(2000 / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);


	this->schedule(schedule_selector(TopScene::tick));

	return true;
}

void TopScene::tick(float delta)
{
	player->tick();
	if(cuey->rand(0,5) == 0) 
	_monster.pushBack(new Monster(_layer, _world));
	for (int i = 0; i < _monster.size(); i++) {
		_monster.at(i)->tick();
		/*if (_monster.at(i)->getMonster()->getPositionY() < 100) {
			delete _monster.at(i);
			_monster.erase(_monster.begin() + i);
		}*/
	}
	

	//Box2D 매뉴얼 상의 권장수치
	int velocityIterations = 8;
	int positionIterations = 3;

	//Step : 물리 세계를 시뮬레이션한다.
	_world->Step(delta, velocityIterations, positionIterations);

	//모든 물리 객체들은 링크드 리스트에 저장되어 참조해볼 수 있도록 구현되어 있다.
	//만들어진 객체만큼 루프를 돌리면서 바디에 붙인 스프라이트를 여기서 제어한다.
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr)
		{
			Sprite* spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(
				Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
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
