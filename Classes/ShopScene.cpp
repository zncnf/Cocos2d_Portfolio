#include "ShopScene.h"

Scene * ShopScene::createScene()
{
	return ShopScene::create();
}

bool ShopScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	log("%d", Player::getInstance()->getItem()->getBuyGold());

	return true;
}
