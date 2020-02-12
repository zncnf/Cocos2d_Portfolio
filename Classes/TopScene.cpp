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

	_layer = Layer::create();
	this->addChild(_layer);

	Player::getInstance()->setLayer(_layer);

	//this->schedule(schedule_selector(MindForest_Stage1::tick));

	//log("%d", Player::getInstance()->getItem()->getBuyGold());
	//this->runAction(Player::getInstance())

	/*GifBase* gif = CacheGifData::create("g7.gif");
	gif->setPosition(960, 160);
	addChild(gif);

	Sprite* pImg = Sprite::create();
	pImg->initWithTexture(GIFMovieData::StaticGetTexture("g7.gif", 0));
	pImg->setPosition(856, 320);
	addChild(pImg);
	pImg->setTexture(GIFMovieData::StaticGetTexture("g7.gif", 5));*/

	return true;
}
