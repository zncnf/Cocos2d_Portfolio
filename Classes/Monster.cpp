#include "Monster.h"

Monster::Monster(Layer* layer, b2World* world) {

	cuey->cache()->addSpriteFramesWithFile("Monster/grinSnail.plist");

	_layer = layer;
	_world = world;

	_monster = Sprite::createWithSpriteFrameName("grinSnail_stand_0.png");
	_monster->setPosition(cuey->rand(10, 1960), 720);
	_layer->addChild(_monster);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(_monster->getPositionX() / PTM_RATIO, _monster->getPositionY() / PTM_RATIO);

	bodyDef.userData = _monster;

	_body = _world->CreateBody(&bodyDef);
	
	b2CircleShape circle;
	circle.m_radius = 0.5;

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &circle;

	//밀도
	fixtureDef.density = 1.0f;

	//마찰력 ( 0 ~ 1 )
	fixtureDef.friction = 0.25f;

	//반발력
	fixtureDef.restitution = 0.25f;

	_body->CreateFixture(&fixtureDef);
	
}

Monster::~Monster()
{
	_world->DestroyBody(_body);
	_body = nullptr;
	_layer->removeChild(_monster);
}

void Monster::tick()
{
	//_monster->setPositionY(_monster->getPositionY() - 5);

	/*_jPow += 0.1f;
	_monster->setPositionY(_monster->getPositionY() - _jPow);
*/
	/*if (_monster->getPositionY() < 215) {
		_monster->setPositionY(215);
		_world->DestroyBody(_body);
		_body = nullptr;
	}*/
}
