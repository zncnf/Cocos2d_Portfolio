#include "TopLayer.h"
#include "TopScene.h"
#include "TopStage_1.h"
#include "TopStage_2.h"
#include "TopStage_3.h"

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
	_tower->setPositionX(100);
	this->addChild(_tower);

	Label* _bestTime0 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 20);
	_bestTime0->setString(StringUtils::format("Best Time\n%d : %d", player->getBestTime(0) / 60, player->getBestTime(0) % 60));
	_bestTime0->setAlignment(TextHAlignment::CENTER);
	_bestTime0->setPosition(-195, -188);
	_bestTime0->setColor(Color3B(250, 250, 50));
	this->addChild(_bestTime0);

	Label* _bestTime1 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 20);
	_bestTime1->setString(StringUtils::format("Best Time\n%d : %d", player->getBestTime(1) / 60, player->getBestTime(1) % 60));
	_bestTime1->setAlignment(TextHAlignment::CENTER);
	_bestTime1->setPosition(-195, 55);
	_bestTime1->setColor(Color3B(250, 250, 50));
	this->addChild(_bestTime1);

	Label* _bestTime2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 20);
	_bestTime2->setString(StringUtils::format("Best Time\n%d : %d", player->getBestTime(2) / 60, player->getBestTime(2) % 60));
	_bestTime2->setAlignment(TextHAlignment::CENTER);
	_bestTime2->setPosition(-195, 298);
	_bestTime2->setColor(Color3B(250, 250, 50));
	this->addChild(_bestTime2);

	_startBtn0 = Sprite::create("Main/StartBtn.png");
	_startBtn0->setPosition(-195, -293);
	this->addChild(_startBtn0);

	_startBtn1 = Sprite::create("Main/StartBtn.png");
	_startBtn1->setPosition(-195, -50);
	this->addChild(_startBtn1);

	_startBtn2 = Sprite::create("Main/StartBtn.png");
	_startBtn2->setPosition(-195, 193);
	this->addChild(_startBtn2);

	return true;
}

bool TopLayer::onTouchBegan(Touch * touch, Event * event, bool isUse)
{
	if (isUse) {
		Vec2 pt = touch->getLocation() + Vec2(1103, 0) - this->getPosition();
		if (_startBtn0->getBoundingBox().containsPoint(pt)) {
			instance->replaceScene(TopStage_1::createScene());
		}
		if (_startBtn1->getBoundingBox().containsPoint(pt)) {
			instance->replaceScene(TopStage_2::createScene());
		}
		if (_startBtn2->getBoundingBox().containsPoint(pt)) {
			instance->replaceScene(TopStage_3::createScene());
		}
	}
	return true;
}

void TopLayer::onTouchMoved(Touch * touch, Event * event, bool isUse)
{
}

void TopLayer::onTouchCancelled(Touch * touch, Event * event, bool isUse)
{
}

void TopLayer::onTouchEnded(Touch * touch, Event * event, bool isUse)
{
}
