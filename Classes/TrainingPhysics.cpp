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

	//�߷� �ۿ� ����
	b2Vec2 gravity = b2Vec2(0, -20);

	//���� ����
	_world = new b2World(gravity);

	//�ƹ� �͵� �� �ϰ� ���� �� �ٵ���� ó��
	_world->SetAllowSleeping(true);

	//���������� ��� ������ �� ����
	_world->SetContinuousPhysics(true);

	//�ٵ� ����
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	//groundBoduDef�� ������ ������ �ٵ� �����
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);
	
	//���� �׵θ��� �׸� ������Ʈ �����
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//ground ��ü�� Set���� ���� ����
	//���� �ٵ�(groundBody)�� ���(groundEdge)�� ������� ����

	//�Ʒ���
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//����
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//�Ʒ���
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//�Ʒ���
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	return true;
}

void TrainingPhysics::onEnter()
{
	Scene::onEnter();

	//��ġ �̺�Ʈ ����
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

	//��ġ�� ���� ���ο� ��������Ʈ �߰�
	this->addNewSpriteAtPosition(touchPoint);

	return true;
}

void TrainingPhysics::addNewSpriteAtPosition(Vec2 location)
{
	//��������Ʈ�� �����.
	Sprite* sprite = Sprite::createWithTexture(texture, Rect(0, 0, 128, 128));
	sprite->setPosition(Vec2(location.x, location.y));
	this->addChild(sprite);

	//bodydef�� �����Ͽ� ���� �Ӽ����� �����Ѵ�.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);

	//���������Ϳ� ��������Ʈ�� ���δ�.
	bodyDef.userData = sprite;

	//���忡 bodydef ������ �� �ٸ� �ٵ� ����
	b2Body* body = _world->CreateBody(&bodyDef);

	//�ٵ� ������ ���� �Ӽ����� �ٵ� ����� �����.
	//����
	b2CircleShape circle;
	circle.m_radius = 0.5;

	//�׸��� �ٵ𿡼� ����� ���ĳ���;
	b2FixtureDef fixtureDef;

	//���� �Ӽ� ����
	fixtureDef.shape = &circle;

	//�е�
	fixtureDef.density = 1.0f;

	//������ (0 ~ 1)
	fixtureDef.friction = 0.25f;

	//�ݹ߷�
	fixtureDef.restitution = 0.75f;

	body->CreateFixture(&fixtureDef);
}

TrainingPhysics::~TrainingPhysics()
{
}
