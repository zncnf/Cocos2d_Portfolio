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

	auto a = Sprite::create("Main/�ʹ�ư.png");
	this->addChild(a);
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

	_bgm = AudioEngine::play2d("Sound/WzLogo.mp3", false, 1.0f);

	return true;
}

void IntroScene::allUserFadeIn()
{
	grade->runAction(FadeIn::create(3));
	grade2->runAction(FadeIn::create(3));
	message->runAction(FadeIn::create(3));
	this->runAction(Sequence::create(
		DelayTime::create(4),//4
		CallFunc::create(CC_CALLBACK_0(IntroScene::allUserFadeOut, this)),
		nullptr
	));
}

void IntroScene::allUserFadeOut()
{
	grade->runAction(FadeOut::create(0.6));
	grade2->runAction(FadeOut::create(0.6));
	message->runAction(FadeOut::create(0.6));
	this->runAction(Sequence::create(
		DelayTime::create(0.6),//1
		CallFunc::create(CC_CALLBACK_0(IntroScene::gotoTopScene, this)),
		nullptr
	));
}

void IntroScene::gotoTopScene()
{
	instance->replaceScene(TransitionFade::create(0.5, MainScene::createScene(),Color3B::WHITE));
}
