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

	auto tower = Sprite::create("Main/ž.png");
	this->addChild(tower);

	return true;
}
