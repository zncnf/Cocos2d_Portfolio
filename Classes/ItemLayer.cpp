#include "ItemLayer.h"

Layer * ItemLayer::createLayer()
{
	return ItemLayer::create();
}

bool ItemLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	auto bg = Sprite::create("Main/아이템창.png");
	this->addChild(bg);

	_leftUI = Sprite::create("Main/아이템창좌측UI.png");
	_leftUI->setPosition(-261, 45);
	this->addChild(_leftUI);

	_rightUI = Sprite::create("Main/아이템창우측UI.png");
	_rightUI->setPosition(180, 0);
	this->addChild(_rightUI);

	setItem();

	return true;
}

bool ItemLayer::onTouchBegan(Touch * touch, Event * event, bool isUse)
{
	setItem();
	return true;
}

void ItemLayer::onTouchMoved(Touch * touch, Event * event, bool isUse)
{
}

void ItemLayer::onTouchCancelled(Touch * touch, Event * event, bool isUse)
{
}

void ItemLayer::onTouchEnded(Touch * touch, Event * event, bool isUse)
{
}

void ItemLayer::setItem()
{
	/*_mountEquip.at(3)->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", player->getPet()->getMountPetName().getCString()));
	_mountEquip.at(3)->label->setString(player->getPet()->getMountPetName().getCString());
	_mountEquip.at(3)->label2->setString(StringUtils::format(""));*/

	for (int i = 0; i < _myItem.size(); i++) {
		_myItem.at(i)->layer->removeFromParentAndCleanup(true);
	}
	_myItem.clear();
	for (int i = 0; i < player->getItem()->getItemSize(); i++) {
		_myItem.push_back(new RightItem({ Layer::create() }));
		_myItem.back()->layer->setPosition(80, 232 - 96 * i);
		this->addChild(_myItem.back()->layer);

		_myItem.back()->box = Sprite::create("Main/아이템칸.png");
		_myItem.back()->box->setPositionY(-22);
		_myItem.back()->layer->addChild(_myItem.back()->box);

		_myItem.back()->sprite = Sprite::createWithTexture(cuey->texture(&StringUtils::format("Item/%s_icon.png", player->getItem()->getName(i).getCString())[0]));
		_myItem.back()->sprite->setPositionY(-22);
		_myItem.back()->sprite->setScale(1.5f);
		_myItem.back()->layer->addChild(_myItem.at(i)->sprite);

		_myItem.back()->label = Label::createWithTTF(player->getItem()->getName(i).getCString(), "fonts/Maplestory Bold.ttf", 20);
		_myItem.back()->label->setAnchorPoint(Vec2(0, 0.5));
		_myItem.back()->label->setPositionX(60);
		_myItem.back()->label->setColor(Color3B(50, 50, 50));
		_myItem.back()->layer->addChild(_myItem.at(i)->label);

		_myItem.back()->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
		_myItem.back()->label2->setString(StringUtils::format("수량 : %d", player->getItem()->getCount(i)));
		_myItem.back()->label2->setAnchorPoint(Vec2(0, 0.5));
		_myItem.back()->label2->setPosition(50, -35);
		_myItem.back()->label2->setColor(Color3B(100, 100, 100));
		_myItem.back()->layer->addChild(_myItem.at(i)->label2);
	}
}
