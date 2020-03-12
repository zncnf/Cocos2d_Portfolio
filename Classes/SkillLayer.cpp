#include "SkillLayer.h"

Layer * SkillLayer::createLayer()
{
	return SkillLayer::create();
}

bool SkillLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	//left

	

	//right

	_normalBtn = Sprite::create("Main/일반공격버튼.png");
	_normalBtn->setPosition(151.5, 287);
	this->addChild(_normalBtn);

	_specialBtn = Sprite::create("Main/필살기버튼.png");
	_specialBtn->setPosition(315, 287);
	this->addChild(_specialBtn);

	_rightUI_normal = Sprite::create("Main/스킬창우측UI_일반공격.png");
	_rightUI_normal->setPosition(233, 0);
	this->addChild(_rightUI_normal);

	_rightUI_special = Sprite::create("Main/스킬창우측UI_필살기.png");
	_rightUI_special->setPosition(9999, 9999);
	this->addChild(_rightUI_special);

	return true;
}

bool SkillLayer::onTouchBegan(Touch * touch, Event * event, bool isUse)
{
	Vec2 pt = touch->getLocation() - this->getPosition();

	if (_normalBtn->getBoundingBox().containsPoint(pt)) {
		_rightUI_normal->setPosition(233, 0);
		_rightUI_special->setPosition(9999, 9999);
	}
	if (_specialBtn->getBoundingBox().containsPoint(pt)) {
		_rightUI_normal->setPosition(9999, 9999);
		_rightUI_special->setPosition(233, 0);
		player->setAttack(false);
	}

	return true;
}

void SkillLayer::onTouchMoved(Touch * touch, Event * event, bool isUse)
{
}

void SkillLayer::onTouchCancelled(Touch * touch, Event * event, bool isUse)
{
}

void SkillLayer::onTouchEnded(Touch * touch, Event * event, bool isUse)
{
}
