#include "TopLayer.h"
#include "TopScene.h"

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
	_bestTime0->setPosition(-195, -189);
	this->addChild(_bestTime0);

	Label* _bestTime1 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 20);
	_bestTime1->setString(StringUtils::format("Best Time\n%d : %d", player->getBestTime(1) / 60, player->getBestTime(1) % 60));
	_bestTime1->setAlignment(TextHAlignment::CENTER);
	_bestTime1->setPosition(-195, 55);
	this->addChild(_bestTime1);

	Label* _bestTime2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 20);
	_bestTime2->setString(StringUtils::format("Best Time\n%d : %d", player->getBestTime(2) / 60, player->getBestTime(2) % 60));
	_bestTime2->setAlignment(TextHAlignment::CENTER);
	_bestTime2->setPosition(-195, 299);
	this->addChild(_bestTime2);

	return true;
}

bool TopLayer::onTouchBegan(Touch * touch, Event * event, bool isUse)
{
	if (isUse) {
		Vec2 pt = touch->getLocation() + Vec2(1103, 0) - this->getPosition();
		//log("(%.f, %.f), (%.f, %.f)", pt.x, pt.y, _tower->getPositionX(), _tower->getPositionY());
		if (_tower->getBoundingBox().containsPoint(pt)) {
			instance->replaceScene(TopScene::createScene());
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
