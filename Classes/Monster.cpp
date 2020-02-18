#include "Monster.h"

Monster::Monster(Layer* layer, b2World* world) {

	cuey->cache()->addSpriteFramesWithFile("Monster/grinSnail.plist");

	_layer = layer;

	//��������Ʈ�� �ǵ� ��ġ�� �����
	_monster = Sprite::createWithSpriteFrameName("grinSnail_stand_0.png");
	//_monster->setCenterRect(Rect(0, 0, 128, 128));
	_monster->setPosition(cuey->rand(10, 1960), 720);
	_layer->addChild(_monster);
	_jPow = 0;

	//bodydef�� �����Ͽ� ���� �Ӽ����� �����Ѵ�.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(_monster->getPositionX() / PTM_RATIO, _monster->getPositionY() / PTM_RATIO);

	//���������Ϳ� ��������Ʈ�� ���δ�
	bodyDef.userData = _monster;

	//���忡 bodydef ������ �� �ٸ� �ٵ� ����
	body = world->CreateBody(&bodyDef);

	//�ٵ� ������ ���� �Ӽ��� �ٵ� ����� �����.
	//����
	b2CircleShape circle;
	circle.m_radius = 0.5;

	//�׸��� �ٵ𿡼� ����� ���ĳ���
	b2FixtureDef fixtureDef;



	//���� �Ӽ� ����
	fixtureDef.shape = &circle;

	//�е�
	fixtureDef.density = 1.0f;

	//������ ( 0 ~ 1 )
	fixtureDef.friction = 0.25f;

	//�ݹ߷�
	fixtureDef.restitution = 0.75f;


	body->CreateFixture(&fixtureDef);
}

Monster::~Monster()
{
	_layer->removeChild(_monster);
}

void Monster::tick()
{
	//_monster->setPositionY(_monster->getPositionY() - 5);

	/*_jPow += 0.1f;
	_monster->setPositionY(_monster->getPositionY() - _jPow);

	if (_monster->getPositionY() < 215) {
		_monster->setPositionY(215);
	}*/
}
