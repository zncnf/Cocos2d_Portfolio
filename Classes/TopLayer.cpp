#include "TopLayer.h"

Layer * TopLayer::createLayer()
{
	return TopLayer::create();
}

bool TopLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	_tower = Sprite::create("Main/ž.png");
	this->addChild(_tower);

	return true;
}

bool TopLayer::onTouchBegan(Touch * touch, Event * event)
{
	Vec2 pt = touch->getLocation() - this->getPosition();
	if (_tower->getBoundingBox().containsPoint(pt)) {
		//instance->replaceScene(TopScene::createScene());
	}
	return true;
}

void TopLayer::onTouchMoved(Touch * touch, Event * event)
{
}

void TopLayer::onTouchCancelled(Touch * touch, Event * event)
{
}

void TopLayer::onTouchEnded(Touch * touch, Event * event)
{
}
