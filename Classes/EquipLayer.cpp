#include "EquipLayer.h"

Layer * EquipLayer::createLayer()
{
	return EquipLayer::create();
}

bool EquipLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	
	auto bg = Sprite::create("Main/���â.png");
	this->addChild(bg);

	//left

	_leftUI = Sprite::create("Main/���â����UI.png");
	_leftUI->setPosition(-288, 0);
	this->addChild(_leftUI);

	_weaponBtn = Sprite::create("Main/�����ư.png");
	_weaponBtn->setPosition(3, 288);
	this->addChild(_weaponBtn);

	_armorBtn = Sprite::create("Main/�ʹ�ư.png");
	_armorBtn->setPosition(112.666, 288);
	this->addChild(_armorBtn);

	_shoesBtn = Sprite::create("Main/�Ź߹�ư.png");
	_shoesBtn->setPosition(222.333, 288);
	this->addChild(_shoesBtn);

	_petBtn = Sprite::create("Main/���ư.png");
	_petBtn->setPosition(332, 288);
	this->addChild(_petBtn);

	Layer* layer = Layer::create();
	this->addChild(layer);
	player->setLayer(layer, false);
	player->getPlayer()->setPosition(-340, 200);
	player->setWay(true);
	player->getPet()->getMountPet()->setPosition(-410, 170);
	player->getPet()->getMountPet()->setFlippedX(true);

	_mountEquip.push_back(new LeftEquip({Layer::create()}));
	_mountEquip.back()->layer->setPosition(-250, 38);
	this->addChild(_mountEquip.back()->layer);

	_mountEquip.push_back(new LeftEquip({ Layer::create() }));
	_mountEquip.back()->layer->setPosition(-250, -58);
	this->addChild(_mountEquip.back()->layer);

	_mountEquip.push_back(new LeftEquip({ Layer::create() }));
	_mountEquip.back()->layer->setPosition(-250, -154);
	this->addChild(_mountEquip.back()->layer);

	_mountEquip.push_back(new LeftEquip({ Layer::create() }));
	_mountEquip.back()->layer->setPosition(-250, -250);
	this->addChild(_mountEquip.back()->layer);

	_mountEquip.at(0)->sprite = Sprite::createWithSpriteFrame(player->getPet()->getMountPet()->getSpriteFrame());
	_mountEquip.at(0)->layer->addChild(_mountEquip.at(0)->sprite);

	_mountEquip.at(0)->label = Label::createWithTTF(player->getPet()->getMountPetName().getCString(), "fonts/Maplestory Bold.ttf", 20);
	_mountEquip.at(0)->label->setColor(Color3B(50, 50, 50));
	_mountEquip.at(0)->layer->addChild(_mountEquip.at(0)->label);

	_mountEquip.at(1)->sprite = Sprite::createWithSpriteFrame(player->getPet()->getMountPet()->getSpriteFrame());
	_mountEquip.at(1)->layer->addChild(_mountEquip.at(1)->sprite);
				   
	_mountEquip.at(1)->label = Label::createWithTTF(player->getPet()->getMountPetName().getCString(), "fonts/Maplestory Bold.ttf", 20);
	_mountEquip.at(1)->label->setColor(Color3B(50, 50, 50));
	_mountEquip.at(1)->layer->addChild(_mountEquip.at(1)->label);

	_mountEquip.at(2)->sprite = Sprite::createWithSpriteFrame(player->getPet()->getMountPet()->getSpriteFrame());
	_mountEquip.at(2)->layer->addChild(_mountEquip.at(2)->sprite);
				   
	_mountEquip.at(2)->label = Label::createWithTTF(player->getPet()->getMountPetName().getCString(), "fonts/Maplestory Bold.ttf", 20);
	_mountEquip.at(2)->label->setColor(Color3B(50, 50, 50));
	_mountEquip.at(2)->layer->addChild(_mountEquip.at(2)->label);

	_mountEquip.at(3)->sprite = Sprite::createWithSpriteFrame(player->getPet()->getMountPet()->getSpriteFrame());
	_mountEquip.at(3)->layer->addChild(_mountEquip.at(3)->sprite);

	_mountEquip.at(3)->label = Label::createWithTTF(player->getPet()->getMountPetName().getCString(), "fonts/Maplestory Bold.ttf", 20);
	_mountEquip.at(3)->label->setColor(Color3B(50, 50, 50));
	_mountEquip.at(3)->layer->addChild(_mountEquip.at(3)->label);

	//right

	_rightUI_weapon = Sprite::create("Main/���â����UI_����.png");
	_rightUI_weapon->setPosition(168, 0);
	this->addChild(_rightUI_weapon);

	_rightUI_armor = Sprite::create("Main/���â����UI_��.png");
	_rightUI_armor->setPosition(9999, 9999);
	this->addChild(_rightUI_armor);

	_rightUI_shoes = Sprite::create("Main/���â����UI_�Ź�.png");
	_rightUI_shoes->setPosition(9999, 9999);
	this->addChild(_rightUI_shoes);

	_rightUI_pet = Sprite::create("Main/���â����UI_��.png");
	_rightUI_pet->setPosition(9999, 9999);
	this->addChild(_rightUI_pet);

	return true;
}

bool EquipLayer::onTouchBegan(Touch * touch, Event * event)
{
	Vec2 pt = touch->getLocation() - this->getPosition();
	//log("%d, %d\t%d, %d\t%d, %d", (int)pt.x, (int)pt.y, (int)_weaponBtn->getPositionX(), (int)_weaponBtn->getPositionY(), (int)this->getPositionX(), (int)this->getPositionY());

	if (_weaponBtn->getBoundingBox().containsPoint(pt)) {
		_rightUI_weapon->setPosition(168, 0);
		_rightUI_armor->setPosition(9999, 9999);
		_rightUI_shoes->setPosition(9999, 9999);
		_rightUI_pet->setPosition(9999, 9999);
	}
	if (_armorBtn->getBoundingBox().containsPoint(pt)) {
		_rightUI_weapon->setPosition(9999, 9999);
		_rightUI_armor->setPosition(168, 0);
		_rightUI_shoes->setPosition(9999, 9999);
		_rightUI_pet->setPosition(9999, 9999);
	}
	if (_shoesBtn->getBoundingBox().containsPoint(pt)) {
		_rightUI_weapon->setPosition(9999, 9999);
		_rightUI_armor->setPosition(9999, 9999);
		_rightUI_shoes->setPosition(168, 0);
		_rightUI_pet->setPosition(9999, 9999);
	}
	if (_petBtn->getBoundingBox().containsPoint(pt)) {
		_rightUI_weapon->setPosition(9999, 9999);
		_rightUI_armor->setPosition(9999, 9999);
		_rightUI_shoes->setPosition(9999, 9999);
		_rightUI_pet->setPosition(168, 0);
		player->setAttack(false);
	}
	return true;
}

void EquipLayer::onTouchMoved(Touch * touch, Event * event)
{
}

void EquipLayer::onTouchCancelled(Touch * touch, Event * event)
{
}

void EquipLayer::onTouchEnded(Touch * touch, Event * event)
{
}