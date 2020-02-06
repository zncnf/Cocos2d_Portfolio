#include "TrainingPhysics.h"

Scene * TrainingPhysics::createScene()
{
	return TrainingPhysics::create();
}

bool TrainingPhysics::init()
{
	if (!Scene::init()) {
		return false;
	}


	winSize = Director::getInstance()->getWinSize();

	//중력 작용 방향
	b2Vec2 gravity = b2Vec2(0, -20);

	//월드 생성
	_world = new b2World(gravity);

	//아무 것도 안 하고 있을 때 바디들의 처리
	_world->SetAllowSleeping(true);

	//물리연산을 계속 수행할 지 여부
	_world->SetContinuousPhysics(true);

	//바디 정보
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	//groundBoduDef의 정보를 가져와 바디를 만든다
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);
	
	//추후 테두리를 그릴 오브젝트 만들기
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//ground 객체에 Set으로 선을 생성
	//이후 바디(groundBody)에 모양(groundEdge)을 접목시켜 고정

	//아랫쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//윗쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//아랫쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//아랫쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	return true;
}

void TrainingPhysics::onEnter()
{
	Scene::onEnter();

	//터치 이벤트 설정
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(TrainingPhysics::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void TrainingPhysics::onExit()
{
	Scene::onExit();
}

void TrainingPhysics::tick(float dt)
{
}

bool TrainingPhysics::onTouchBegan(Touch * touch, Event * event)
{
	auto touchPoint = touch->getLocation();

	//터치된 곳에 새로운 스프라이트 추가
	this->addNewSpriteAtPosition(touchPoint);

	return true;
}

void TrainingPhysics::addNewSpriteAtPosition(Vec2 location)
{
	//스프라이트를 만든다.
	Sprite* sprite = Sprite::createWithTexture(texture, Rect(0, 0, 128, 128));
	sprite->setPosition(Vec2(location.x, location.y));
	this->addChild(sprite);

	//bodydef를 생성하여 하위 속성들을 관리한다.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);

	//유저데이터에 스프라이트를 붙인다.
	bodyDef.userData = sprite;

	//월드에 bodydef 정보로 또 다른 바디를 제작
	b2Body* body = _world->CreateBody(&bodyDef);

	//바디에 적용할 물리 속성용의 바디 모양을 만든다.
	//원형
	b2CircleShape circle;
	circle.m_radius = 0.5;

	//그리고 바디에서 모양을 고쳐놓기;
	b2FixtureDef fixtureDef;

	//내부 속성 지정
	fixtureDef.shape = &circle;

	//밀도
	fixtureDef.density = 1.0f;

	//마찰력 (0 ~ 1)
	fixtureDef.friction = 0.25f;

	//반발력
	fixtureDef.restitution = 0.75f;

	body->CreateFixture(&fixtureDef);
}

TrainingPhysics::~TrainingPhysics()
{
}
