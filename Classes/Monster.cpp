#include "Monster.h"

Monster::Monster(Layer* layer, b2World* world) {

	cuey->cache()->addSpriteFramesWithFile("Monster/grinSnail.plist");

	_layer = layer;

	//스프라이트를 탭된 위치에 만든다
	_monster = Sprite::createWithSpriteFrameName("grinSnail_stand_0.png");
	//_monster->setCenterRect(Rect(0, 0, 128, 128));
	_monster->setPosition(cuey->rand(10, 1960), 720);
	_layer->addChild(_monster);
	_jPow = 0;

	//bodydef를 생성하여 하위 속성들을 관리한다.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(_monster->getPositionX() / PTM_RATIO, _monster->getPositionY() / PTM_RATIO);

	//유저데이터에 스프라이트를 붙인다
	bodyDef.userData = _monster;

	//월드에 bodydef 정보로 또 다른 바디를 제작
	body = world->CreateBody(&bodyDef);

	//바디에 적용할 물리 속성의 바디 모양을 만든다.
	//원형
	b2CircleShape circle;
	circle.m_radius = 0.5;

	//그리고 바디에서 모양을 고쳐놓기
	b2FixtureDef fixtureDef;



	//내부 속성 지정
	fixtureDef.shape = &circle;

	//밀도
	fixtureDef.density = 1.0f;

	//마찰력 ( 0 ~ 1 )
	fixtureDef.friction = 0.25f;

	//반발력
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
