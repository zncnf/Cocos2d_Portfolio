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

	auto bg = Sprite::create("Main/장비창.png");
	this->addChild(bg);

	//left

	_leftUI = Sprite::create("Main/장비창좌측UI.png");
	_leftUI->setPosition(-288, 0);
	this->addChild(_leftUI);

	_stats = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 17);
	_stats->setString(StringUtils::format("Lv : %d\n\n공격력 : %.1f(%d+%.1f)\n\n생명력 : %d(%.1f+%.1f)\n\n기동력 : %.1f(%.1f+%.1f)",
											(int)player->getLv(),
											player->getAtk(), (int)player->getBaseAtk(), player->getEquip()->getMountWeaponAtk(),
											(int)player->getLife(), player->getBaseLife(), player->getEquip()->getMountArmorLife(), 
											player->getSpeed(), player->getBaseSpeed(), player->getEquip()->getMountShoesSpeed()));
	_stats->setAnchorPoint(Vec2(0, 1));
	_stats->setPosition(-245, 260);
	_stats->setColor(Color3B(100, 100, 100));
	this->addChild(_stats);

	_mountEquip.push_back(new LeftEquip({Layer::create()}));
	_mountEquip.back()->layer->setPosition(-357, 38);
	this->addChild(_mountEquip.back()->layer);

	_mountEquip.push_back(new LeftEquip({ Layer::create() }));
	_mountEquip.back()->layer->setPosition(-357, -58);
	this->addChild(_mountEquip.back()->layer);

	_mountEquip.push_back(new LeftEquip({ Layer::create() }));
	_mountEquip.back()->layer->setPosition(-357, -154);
	this->addChild(_mountEquip.back()->layer);

	_mountEquip.push_back(new LeftEquip({ Layer::create() }));
	_mountEquip.back()->layer->setPosition(-357, -250);
	this->addChild(_mountEquip.back()->layer);

	_mountEquip.at(0)->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_icon.png", player->getEquip()->getMountWeaponCode().getCString()));
	_mountEquip.at(0)->sprite->setPositionY(-22);
	_mountEquip.at(0)->sprite->setScale(1.5f);
	_mountEquip.at(0)->layer->addChild(_mountEquip.at(0)->sprite);
				   
	_mountEquip.at(0)->label = Label::createWithTTF(player->getEquip()->getMountWeaponName().getCString(), "fonts/Maplestory Bold.ttf", 20);
	_mountEquip.at(0)->label->setAnchorPoint(Vec2(0, 0.5));
	_mountEquip.at(0)->label->setPositionX(60);
	_mountEquip.at(0)->label->setColor(Color3B(50, 50, 50));
	_mountEquip.at(0)->layer->addChild(_mountEquip.at(0)->label);

	_mountEquip.at(0)->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
	_mountEquip.at(0)->label2->setString(StringUtils::format("공격력 : +%.1f", player->getEquip()->getMountWeaponAtk()));
	_mountEquip.at(0)->label2->setAnchorPoint(Vec2(0, 0.5));
	_mountEquip.at(0)->label2->setPosition(50, -35);
	_mountEquip.at(0)->label2->setColor(Color3B(100, 100, 100));
	_mountEquip.at(0)->layer->addChild(_mountEquip.at(0)->label2);

	_mountEquip.at(1)->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_icon.png", player->getEquip()->getMountArmorCode().getCString()));
	_mountEquip.at(1)->sprite->setPositionY(-22);
	_mountEquip.at(1)->sprite->setScale(1.5f);
	_mountEquip.at(1)->layer->addChild(_mountEquip.at(1)->sprite);
				   
	_mountEquip.at(1)->label = Label::createWithTTF(player->getEquip()->getMountArmorName().getCString(), "fonts/Maplestory Bold.ttf", 20);
	_mountEquip.at(1)->label->setAnchorPoint(Vec2(0, 0.5));
	_mountEquip.at(1)->label->setPositionX(60);
	_mountEquip.at(1)->label->setColor(Color3B(50, 50, 50));
	_mountEquip.at(1)->layer->addChild(_mountEquip.at(1)->label);

	_mountEquip.at(1)->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
	_mountEquip.at(1)->label2->setString(StringUtils::format("생명력 : +%d", (int)player->getEquip()->getMountArmorLife()));
	_mountEquip.at(1)->label2->setAnchorPoint(Vec2(0, 0.5));
	_mountEquip.at(1)->label2->setPosition(50, -35);
	_mountEquip.at(1)->label2->setColor(Color3B(100, 100, 100));
	_mountEquip.at(1)->layer->addChild(_mountEquip.at(1)->label2);

	_mountEquip.at(2)->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_icon.png", player->getEquip()->getMountShoesCode().getCString()));
	_mountEquip.at(2)->sprite->setPositionY(-22);
	_mountEquip.at(2)->sprite->setScale(1.5f);
	_mountEquip.at(2)->layer->addChild(_mountEquip.at(2)->sprite);
				   
	_mountEquip.at(2)->label = Label::createWithTTF(player->getEquip()->getMountShoesName().getCString(), "fonts/Maplestory Bold.ttf", 20);
	_mountEquip.at(2)->label->setAnchorPoint(Vec2(0, 0.5));
	_mountEquip.at(2)->label->setPositionX(60);
	_mountEquip.at(2)->label->setColor(Color3B(50, 50, 50));
	_mountEquip.at(2)->layer->addChild(_mountEquip.at(2)->label);
	
	_mountEquip.at(2)->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
	_mountEquip.at(2)->label2->setString(StringUtils::format("기동력 : +%.1f", player->getEquip()->getMountShoesSpeed()));
	_mountEquip.at(2)->label2->setAnchorPoint(Vec2(0, 0.5));
	_mountEquip.at(2)->label2->setPosition(50, -35);
	_mountEquip.at(2)->label2->setColor(Color3B(100, 100, 100));
	_mountEquip.at(2)->layer->addChild(_mountEquip.at(2)->label2);

	_mountEquip.at(3)->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_icon.png", player->getPet()->getMountPetName().getCString()));
	_mountEquip.at(3)->sprite->setPositionY(-22);
	_mountEquip.at(3)->sprite->setScale(1.5f);
	_mountEquip.at(3)->layer->addChild(_mountEquip.at(3)->sprite);

	_mountEquip.at(3)->label = Label::createWithTTF(player->getPet()->getMountPetName().getCString(), "fonts/Maplestory Bold.ttf", 20);
	_mountEquip.at(3)->label->setAnchorPoint(Vec2(0, 0.5));
	_mountEquip.at(3)->label->setPositionX(60);
	_mountEquip.at(3)->label->setColor(Color3B(50, 50, 50));
	_mountEquip.at(3)->layer->addChild(_mountEquip.at(3)->label);

	_mountEquip.at(3)->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
	_mountEquip.at(3)->label2->setString(StringUtils::format(""));
	_mountEquip.at(3)->label2->setAnchorPoint(Vec2(0, 0.5));
	_mountEquip.at(3)->label2->setPosition(50, -35);
	_mountEquip.at(3)->label2->setColor(Color3B(100, 100, 100));
	_mountEquip.at(3)->layer->addChild(_mountEquip.at(3)->label2);

	//right

	_weaponBtn = Sprite::create("Main/무기버튼.png");
	_weaponBtn->setPosition(3, 288);
	this->addChild(_weaponBtn);

	_armorBtn = Sprite::create("Main/옷버튼.png");
	_armorBtn->setPosition(112.666, 288);
	this->addChild(_armorBtn);

	_shoesBtn = Sprite::create("Main/신발버튼.png");
	_shoesBtn->setPosition(222.333, 288);
	this->addChild(_shoesBtn);

	_petBtn = Sprite::create("Main/펫버튼.png");
	_petBtn->setPosition(332, 288);
	this->addChild(_petBtn);

	_rightUI_weapon = Sprite::create("Main/장비창우측UI_무기.png");
	_rightUI_weapon->setPosition(168, 0);
	this->addChild(_rightUI_weapon);

	_rightUI_armor = Sprite::create("Main/장비창우측UI_옷.png");
	_rightUI_armor->setPosition(9999, 9999);
	this->addChild(_rightUI_armor);

	_rightUI_shoes = Sprite::create("Main/장비창우측UI_신발.png");
	_rightUI_shoes->setPosition(9999, 9999);
	this->addChild(_rightUI_shoes);

	_rightUI_pet = Sprite::create("Main/장비창우측UI_펫.png");
	_rightUI_pet->setPosition(9999, 9999);
	this->addChild(_rightUI_pet);

	for (int i = 0; i < player->getEquip()->getMyWeaponSize(); i++) {
		_myEquip.push_back(new RightEquip({ Layer::create() }));
		_myEquip.back()->layer->setPosition(30, 232 - 96 * i);
		this->addChild(_myEquip.back()->layer);

		auto equipbg = Sprite::create("Main/아이템칸.png");
		equipbg->setPositionY(-22);
		_myEquip.back()->layer->addChild(equipbg);

		_myEquip.back()->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_icon.png", player->getEquip()->getMyWeaponCode(i).getCString()));
		_myEquip.back()->sprite->setPositionY(-22);
		_myEquip.back()->sprite->setScale(1.5f);
		_myEquip.back()->layer->addChild(_myEquip.at(i)->sprite);
		
		_myEquip.back()->label = Label::createWithTTF(player->getEquip()->getMyWeaponName(i).getCString(), "fonts/Maplestory Bold.ttf", 20);
		_myEquip.back()->label->setAnchorPoint(Vec2(0, 0.5));
		_myEquip.back()->label->setPositionX(60);
		_myEquip.back()->label->setColor(Color3B(50, 50, 50));
		_myEquip.back()->layer->addChild(_myEquip.at(i)->label);
		
		_myEquip.back()->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
		_myEquip.back()->label2->setString(StringUtils::format("공격력 : +%.1f", player->getEquip()->getMyWeaponAtk(i)));
		_myEquip.back()->label2->setAnchorPoint(Vec2(0, 0.5));
		_myEquip.back()->label2->setPosition(50, -35);
		_myEquip.back()->label2->setColor(Color3B(100, 100, 100));
		_myEquip.back()->layer->addChild(_myEquip.at(i)->label2);
	}

	_selEquip = 0;

	return true;
}

bool EquipLayer::onTouchBegan(Touch * touch, Event * event, bool isUse)
{
	Vec2 pt = touch->getLocation() - this->getPosition();
	//log("%d, %d\t%d, %d\t%d, %d", (int)pt.x, (int)pt.y, (int)_weaponBtn->getPositionX(), (int)_weaponBtn->getPositionY(), (int)this->getPositionX(), (int)this->getPositionY());

	if (_weaponBtn->getBoundingBox().containsPoint(pt)) {
		setWeapon();
	}
	if (_armorBtn->getBoundingBox().containsPoint(pt)) {
		setArmor();
	}
	if (_shoesBtn->getBoundingBox().containsPoint(pt)) {
		setShoes();
	}
	if (_petBtn->getBoundingBox().containsPoint(pt)) {
		setPet();
	}


	for (int i = 0; i < _myEquip.size(); i++) {
		if (_myEquip.at(i)->sprite->getBoundingBox().containsPoint(pt - _myEquip.at(i)->layer->getPosition())) {
			switch (_selEquip) {
			case 0:
				player->getEquip()->mountWeapon(i);
				setWeapon();
				player->setStand();
				break;
			case 1:
				player->getEquip()->mountArmor(i);
				setArmor();
				player->setStand();
				break;
			case 2:
				player->getEquip()->mountShoes(i);
				setShoes();
				player->setStand();
				break;
			case 3:
				setPet();
				break;
			}
		}
	}
	_stats->setString(StringUtils::format("Lv : %d\n\n공격력 : %.1f(%d+%.1f)\n\n생명력 : %d(%.1f+%.1f)\n\n기동력 : %.1f(%.1f+%.1f)",
		(int)player->getLv(),
		player->getAtk(), (int)player->getBaseAtk(), player->getEquip()->getMountWeaponAtk(),
		(int)player->getLife(), player->getBaseLife(), player->getEquip()->getMountArmorLife(),
		player->getSpeed(), player->getBaseSpeed(), player->getEquip()->getMountShoesSpeed()));
	
	return true;
}

void EquipLayer::onTouchMoved(Touch * touch, Event * event, bool isUse)
{
}

void EquipLayer::onTouchCancelled(Touch * touch, Event * event, bool isUse)
{
}

void EquipLayer::onTouchEnded(Touch * touch, Event * event, bool isUse)
{
}

void EquipLayer::setWeapon()
{
	_mountEquip.at(0)->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", player->getEquip()->getMountWeaponCode().getCString()));
	_mountEquip.at(0)->label->setString(player->getEquip()->getMountWeaponName().getCString());
	_mountEquip.at(0)->label2->setString(StringUtils::format("공격력 : +%.1f", player->getEquip()->getMountWeaponAtk()));

	_rightUI_weapon->setPosition(168, 0);
	_rightUI_armor->setPosition(9999, 9999);
	_rightUI_shoes->setPosition(9999, 9999);
	_rightUI_pet->setPosition(9999, 9999);

	for (int i = 0; i < _myEquip.size(); i++) {
		_myEquip.at(i)->layer->removeFromParentAndCleanup(true);
	}
	_myEquip.clear();
	for (int i = 0; i < player->getEquip()->getMyWeaponSize(); i++) {
		_myEquip.push_back(new RightEquip({ Layer::create() }));
		_myEquip.back()->layer->setPosition(30, 232 - 96 * i);
		this->addChild(_myEquip.back()->layer);

		auto equipbg = Sprite::create("Main/아이템칸.png");
		equipbg->setPositionY(-22);
		_myEquip.back()->layer->addChild(equipbg);

		_myEquip.back()->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_icon.png", player->getEquip()->getMyWeaponCode(i).getCString()));
		_myEquip.back()->sprite->setPositionY(-22);
		_myEquip.back()->sprite->setScale(1.5f);
		_myEquip.back()->layer->addChild(_myEquip.at(i)->sprite);

		_myEquip.back()->label = Label::createWithTTF(player->getEquip()->getMyWeaponName(i).getCString(), "fonts/Maplestory Bold.ttf", 20);
		_myEquip.back()->label->setAnchorPoint(Vec2(0, 0.5));
		_myEquip.back()->label->setPositionX(60);
		_myEquip.back()->label->setColor(Color3B(50, 50, 50));
		_myEquip.back()->layer->addChild(_myEquip.at(i)->label);

		_myEquip.back()->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
		_myEquip.back()->label2->setString(StringUtils::format("공격력 : +%.1f", player->getEquip()->getMyWeaponAtk(i)));
		_myEquip.back()->label2->setAnchorPoint(Vec2(0, 0.5));
		_myEquip.back()->label2->setPosition(50, -35);
		_myEquip.back()->label2->setColor(Color3B(100, 100, 100));
		_myEquip.back()->layer->addChild(_myEquip.at(i)->label2);
	}
	_selEquip = 0;
}

void EquipLayer::setArmor()
{
	_mountEquip.at(1)->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", player->getEquip()->getMountArmorCode().getCString()));
	_mountEquip.at(1)->label->setString(player->getEquip()->getMountArmorName().getCString());
	_mountEquip.at(1)->label2->setString(StringUtils::format("생명력 : +%d", (int)player->getEquip()->getMountArmorLife()));

	_rightUI_weapon->setPosition(9999, 9999);
	_rightUI_armor->setPosition(168, 0);
	_rightUI_shoes->setPosition(9999, 9999);
	_rightUI_pet->setPosition(9999, 9999);
	for (int i = 0; i < _myEquip.size(); i++) {
		_myEquip.at(i)->layer->removeFromParentAndCleanup(true);
	}
	_myEquip.clear();
	for (int i = 0; i < player->getEquip()->getMyArmorSize(); i++) {
		_myEquip.push_back(new RightEquip({ Layer::create() }));
		_myEquip.back()->layer->setPosition(30, 232 - 96 * i);
		this->addChild(_myEquip.back()->layer);

		auto equipbg = Sprite::create("Main/아이템칸.png");
		equipbg->setPositionY(-22);
		_myEquip.back()->layer->addChild(equipbg);

		_myEquip.back()->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_icon.png", player->getEquip()->getMyArmorCode(i).getCString()));
		_myEquip.back()->sprite->setPositionY(-22);
		_myEquip.back()->sprite->setScale(1.5f);
		_myEquip.back()->layer->addChild(_myEquip.at(i)->sprite);

		_myEquip.back()->label = Label::createWithTTF(player->getEquip()->getMyArmorName(i).getCString(), "fonts/Maplestory Bold.ttf", 20);
		_myEquip.back()->label->setAnchorPoint(Vec2(0, 0.5));
		_myEquip.back()->label->setPositionX(60);
		_myEquip.back()->label->setColor(Color3B(50, 50, 50));
		_myEquip.back()->layer->addChild(_myEquip.at(i)->label);

		_myEquip.back()->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
		_myEquip.back()->label2->setString(StringUtils::format("생명력 : +%d", (int)player->getEquip()->getMyArmorLife(i)));
		_myEquip.back()->label2->setAnchorPoint(Vec2(0, 0.5));
		_myEquip.back()->label2->setPosition(50, -35);
		_myEquip.back()->label2->setColor(Color3B(100, 100, 100));
		_myEquip.back()->layer->addChild(_myEquip.at(i)->label2);
	}
	_selEquip = 1;
}

void EquipLayer::setShoes()
{
	_mountEquip.at(2)->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", player->getEquip()->getMountShoesCode().getCString()));
	_mountEquip.at(2)->label->setString(player->getEquip()->getMountShoesName().getCString());
	_mountEquip.at(2)->label2->setString(StringUtils::format("기동력 : +%.1f", player->getEquip()->getMountShoesSpeed()));

	_rightUI_weapon->setPosition(9999, 9999);
	_rightUI_armor->setPosition(9999, 9999);
	_rightUI_shoes->setPosition(168, 0);
	_rightUI_pet->setPosition(9999, 9999);
	for (int i = 0; i < _myEquip.size(); i++) {
		_myEquip.at(i)->layer->removeFromParentAndCleanup(true);
	}
	_myEquip.clear();
	for (int i = 0; i < player->getEquip()->getMyShoesSize(); i++) {
		_myEquip.push_back(new RightEquip({ Layer::create() }));
		_myEquip.back()->layer->setPosition(30, 232 - 96 * i);
		this->addChild(_myEquip.back()->layer);

		auto equipbg = Sprite::create("Main/아이템칸.png");
		equipbg->setPositionY(-22);
		_myEquip.back()->layer->addChild(equipbg);

		_myEquip.back()->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_icon.png", player->getEquip()->getMyShoesCode(i).getCString()));
		_myEquip.back()->sprite->setPositionY(-22);
		_myEquip.back()->sprite->setScale(1.5f);
		_myEquip.back()->layer->addChild(_myEquip.at(i)->sprite);

		_myEquip.back()->label = Label::createWithTTF(player->getEquip()->getMyShoesName(i).getCString(), "fonts/Maplestory Bold.ttf", 20);
		_myEquip.back()->label->setAnchorPoint(Vec2(0, 0.5));
		_myEquip.back()->label->setPositionX(60);
		_myEquip.back()->label->setColor(Color3B(50, 50, 50));
		_myEquip.back()->layer->addChild(_myEquip.at(i)->label);

		_myEquip.back()->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
		_myEquip.back()->label2->setString(StringUtils::format("기동력 : +%.1f", player->getEquip()->getMyShoesSpeed(i)));
		_myEquip.back()->label2->setAnchorPoint(Vec2(0, 0.5));
		_myEquip.back()->label2->setPosition(50, -35);
		_myEquip.back()->label2->setColor(Color3B(100, 100, 100));
		_myEquip.back()->layer->addChild(_myEquip.at(i)->label2);
	}
	_selEquip = 2;
}

void EquipLayer::setPet()
{
	_mountEquip.at(3)->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", player->getPet()->getMountPetName().getCString()));
	_mountEquip.at(3)->label->setString(player->getPet()->getMountPetName().getCString());
	_mountEquip.at(3)->label2->setString(StringUtils::format(""));

	_rightUI_weapon->setPosition(9999, 9999);
	_rightUI_armor->setPosition(9999, 9999);
	_rightUI_shoes->setPosition(9999, 9999);
	_rightUI_pet->setPosition(168, 0);
	for (int i = 0; i < _myEquip.size(); i++) {
		_myEquip.at(i)->layer->removeFromParentAndCleanup(true);
	}
	_myEquip.clear();

	_selEquip = 3;
}
