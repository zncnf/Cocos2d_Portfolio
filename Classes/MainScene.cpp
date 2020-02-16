#include "MainScene.h"

Scene * MainScene::createScene()
{
	return MainScene::create();
}

bool MainScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	_layer = Layer::create();
	this->addChild(_layer);

	Sprite* sprite = Sprite::create("Map/ž.png");
	_layer->addChild(sprite);
	sprite->setPosition(300, 300);

	return true;
}
