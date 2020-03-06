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

	auto _layer = LayerColor::create(Color4B::WHITE);
	this->addChild(_layer);
	
	grade = Sprite::create("Intro/Grade.0.png");
	grade->setPosition(instance->getWinSize().width - 150, instance->getWinSize().height - 150);
	grade->setAnchorPoint(Vec2(0, 0));
	grade->setOpacity(0);
	this->addChild(grade);

	grade2 = Sprite::create("Intro/Grade.1.png");
	grade2->setPosition(instance->getWinSize().width - 230, instance->getWinSize().height - 150);
	grade2->setAnchorPoint(Vec2(0, 0));
	grade2->setOpacity(0);
	this->addChild(grade2);

	message = Sprite::create("Intro/Message.0.png");
	message->setPosition(instance->getWinSize().width/2, instance->getWinSize().height/2);
	message->setOpacity(0);
	this->addChild(message);

	allUserFadeIn();

	return true;
}

void IntroScene::allUserFadeIn()
{
	grade->runAction(FadeIn::create(3));
	grade2->runAction(FadeIn::create(3));
	message->runAction(FadeIn::create(3));
	this->runAction(Sequence::create(
		DelayTime::create(0.5),//4
		CallFunc::create(CC_CALLBACK_0(IntroScene::allUserFadeOut, this)),
		nullptr
	));
}

void IntroScene::allUserFadeOut()
{
	grade->runAction(FadeOut::create(1));
	grade2->runAction(FadeOut::create(1));
	message->runAction(FadeOut::create(1));
	this->runAction(Sequence::create(
		DelayTime::create(0.5),//1
		CallFunc::create(CC_CALLBACK_0(IntroScene::gotoTopScene, this)),
		nullptr
	));
}

void IntroScene::gotoTopScene()
{
	auto scene = TopScene::createScene();
	instance->replaceScene(scene);
}
