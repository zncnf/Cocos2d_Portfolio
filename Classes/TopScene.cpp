#include "TopScene.h"

Scene * TopScene::createScene()
{
	return TopScene::create();
}

bool TopScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	log("%d", Player::getInstance()->getItem()->getBuyGold());
	//this->runAction(Player::getInstance())

	return true;
}
