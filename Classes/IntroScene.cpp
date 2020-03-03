#include "IntroScene.h"

Scene * IntroScene::createScene()
{
	return IntroScene::create();
}

bool IntroScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	log("%d", player->getItem()->getBuyGold());
	
	auto scene = TopScene::createScene();
	instance->replaceScene(scene);

	return true;
}
