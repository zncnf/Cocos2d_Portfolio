#include "SkillLayer.h"

Layer * SkillLayer::createLayer()
{
	return SkillLayer::create();
}

bool SkillLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	//left

	auto _skillRange = Sprite::create("Main/스킬범위창.png");
	this->addChild(_skillRange);

	_mountSkill.push_back(new LeftSkill({ Layer::create() }));
	_mountSkill.back()->layer->setPosition(-457, -250);
	this->addChild(_mountSkill.back()->layer);

	_mountSkill.back()->box = Sprite::create("Main/SkillSelect_1.png");
	_mountSkill.back()->box->setPositionY(-22);
	_mountSkill.back()->layer->addChild(_mountSkill.back()->box);

	_mountSkill.back()->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_icon.png", player->getSkill()->getNormalCode().getCString()));
	_mountSkill.back()->sprite->setPositionY(-22);
	_mountSkill.back()->sprite->setScale(1.5f);
	_mountSkill.back()->layer->addChild(_mountSkill.back()->sprite);

	_mountSkill.back()->label = Label::createWithTTF(player->getSkill()->getNormalName().getCString(), "fonts/Maplestory Bold.ttf", 20);
	_mountSkill.back()->label->setAnchorPoint(Vec2(0, 0.5));
	_mountSkill.back()->label->setPositionX(60);
	_mountSkill.back()->label->setColor(Color3B(50, 50, 50));
	_mountSkill.back()->layer->addChild(_mountSkill.back()->label);

	_mountSkill.back()->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
	_mountSkill.back()->label2->setString(StringUtils::format("데미지 : x%.1f\n타겟 수 : %d", player->getSkill()->getNormalAtkf(), player->getSkill()->getNormalCount()));
	_mountSkill.back()->label2->setAnchorPoint(Vec2(0, 0.5));
	_mountSkill.back()->label2->setPosition(50, -35);
	_mountSkill.back()->label2->setColor(Color3B(100, 100, 100));
	_mountSkill.back()->layer->addChild(_mountSkill.back()->label2);

	_mountSkill.push_back(new LeftSkill({ Layer::create() }));
	_mountSkill.back()->layer->setPosition(-177, -250);
	this->addChild(_mountSkill.back()->layer);

	_mountSkill.back()->box = Sprite::create("Main/SkillSelect_1.png");
	_mountSkill.back()->box->setPositionY(-22);
	_mountSkill.back()->layer->addChild(_mountSkill.back()->box);

	if (player->getSkill()->getSpecialName().compare("") == 0) _mountSkill.back()->sprite = Sprite::create();
	else _mountSkill.back()->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_icon.png", player->getSkill()->getSpecialName().getCString()));
	_mountSkill.back()->sprite->setPositionY(-22);
	_mountSkill.back()->sprite->setScale(1.5f);
	_mountSkill.back()->layer->addChild(_mountSkill.back()->sprite);

	if (player->getSkill()->getSpecialName().compare("") == 0) _mountSkill.back()->label = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 20);
	else _mountSkill.back()->label = Label::createWithTTF(player->getSkill()->getSpecialName().getCString(), "fonts/Maplestory Bold.ttf", 20);
	_mountSkill.back()->label->setAnchorPoint(Vec2(0, 0.5));
	_mountSkill.back()->label->setPositionX(60);
	_mountSkill.back()->label->setColor(Color3B(50, 50, 50));
	_mountSkill.back()->layer->addChild(_mountSkill.back()->label);

	if (player->getSkill()->getSpecialName().compare("") == 0) _mountSkill.back()->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
	else _mountSkill.back()->label2 = Label::createWithTTF(player->getSkill()->getSpecialEx().getCString(), "fonts/Maplestory Bold.ttf", 15);
	_mountSkill.back()->label2->setAnchorPoint(Vec2(0, 0.5));
	_mountSkill.back()->label2->setPosition(50, -35);
	_mountSkill.back()->label2->setColor(Color3B(100, 100, 100));
	_mountSkill.back()->layer->addChild(_mountSkill.back()->label2);

	//right

	_normalBtn = Sprite::create("Main/일반공격버튼.png");
	_normalBtn->setPosition(151.5, 287);
	this->addChild(_normalBtn);

	_specialBtn = Sprite::create("Main/필살기버튼.png");
	_specialBtn->setPosition(315, 287);
	this->addChild(_specialBtn);

	_rightUI_normal = Sprite::create("Main/스킬창우측UI_일반공격.png");
	_rightUI_normal->setPosition(233, 0);
	this->addChild(_rightUI_normal);

	_rightUI_special = Sprite::create("Main/스킬창우측UI_필살기.png");
	_rightUI_special->setPosition(9999, 9999);
	this->addChild(_rightUI_special);
	
	setNormal();

	return true;
}

bool SkillLayer::onTouchBegan(Touch * touch, Event * event, bool isUse)
{
	Vec2 pt = touch->getLocation() - this->getPosition();

	if (_normalBtn->getBoundingBox().containsPoint(pt)) {
		_rightUI_normal->setPosition(233, 0);
		_rightUI_special->setPosition(9999, 9999);
		setNormal();
		AudioEngine::play2d("Sound/장비변경.mp3", false, 1.0f);
	}
	if (_specialBtn->getBoundingBox().containsPoint(pt)) {
		_rightUI_normal->setPosition(9999, 9999);
		_rightUI_special->setPosition(233, 0);
		setSpecial();
		AudioEngine::play2d("Sound/장비변경.mp3", false, 1.0f);
	}
	if (_mountSkill[0]->box->getBoundingBox().containsPoint(pt - _mountSkill[0]->layer->getPosition())) {
		player->getSkill()->setSkillClean();
		player->setAttack(false);
	}
	if (_mountSkill[1]->box->getBoundingBox().containsPoint(pt - _mountSkill[1]->layer->getPosition())) {
		player->getSkill()->setSkillClean();
		player->getSkill()->playSpecial(false);
	}
	for (int i = 0; i < _mySkill.size(); i++) {
		if (_mySkill.at(i)->box->getBoundingBox().containsPoint(pt - _mySkill.at(i)->layer->getPosition())) {
			switch (_selSkill) {
			case 0:
				player->getSkill()->setSkillClean();
				player->getSkill()->mountNormal(i);
				setNormal();
				player->setAttack(false);
				break;
			case 1:
				player->getSkill()->setSkillClean();
				player->getSkill()->mountSpecial(i);
				setSpecial();
				player->getSkill()->playSpecial(false);
				break;
			}
		}
	}

	return true;
}

void SkillLayer::onTouchMoved(Touch * touch, Event * event, bool isUse)
{
}

void SkillLayer::onTouchCancelled(Touch * touch, Event * event, bool isUse)
{
}

void SkillLayer::onTouchEnded(Touch * touch, Event * event, bool isUse)
{
	switch (_selSkill) {
	case 0:
		setNormal();
		break;
	case 1:
		setSpecial();
		break;
	}
}

void SkillLayer::setNormal()
{
	_mountSkill[0]->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", player->getSkill()->getNormalCode().getCString()));
	_mountSkill[0]->label->setString(player->getSkill()->getNormalName().getCString());
	_mountSkill[0]->label2->setString(StringUtils::format("데미지 : x%.1f\n타겟 수 : %d", player->getSkill()->getNormalAtkf(), player->getSkill()->getNormalCount()));
	for (int i = 0; i < _mySkill.size(); i++) {
		_mySkill.at(i)->layer->removeFromParentAndCleanup(true);
	}
	_mySkill.clear();

	for (int i = 0; i < player->getSkill()->getMyNormalSize(); i++) {
		_mySkill.push_back(new RightSkill({ Layer::create() }));
		_mySkill.back()->layer->setPosition(125, 216 - 113 * i);
		this->addChild(_mySkill.back()->layer);

		_mySkill.back()->box = Sprite::create("Main/SkillSelect_1.png");
		_mySkill.back()->box->setPositionY(-22);
		_mySkill.back()->layer->addChild(_mySkill.back()->box);

		_mySkill.back()->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_icon.png", player->getSkill()->getMyNormalCode(i).getCString()));
		_mySkill.back()->sprite->setPositionY(-22);
		_mySkill.back()->sprite->setScale(1.5f);
		_mySkill.back()->layer->addChild(_mySkill.at(i)->sprite);

		_mySkill.back()->label = Label::createWithTTF(player->getSkill()->getMyNormalName(i).getCString(), "fonts/Maplestory Bold.ttf", 20);
		_mySkill.back()->label->setAnchorPoint(Vec2(0, 0.5));
		_mySkill.back()->label->setPositionX(60);
		_mySkill.back()->label->setColor(Color3B(50, 50, 50));
		_mySkill.back()->layer->addChild(_mySkill.at(i)->label);

		_mySkill.back()->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
		_mySkill.back()->label2->setString(StringUtils::format("데미지 : x%.1f\n타겟 수 : %d", player->getSkill()->getMyNormalAtkf(i), player->getSkill()->getMyNormalCount(i)));
		_mySkill.back()->label2->setAnchorPoint(Vec2(0, 0.5));
		_mySkill.back()->label2->setPosition(50, -35);
		_mySkill.back()->label2->setColor(Color3B(100, 100, 100));
		_mySkill.back()->layer->addChild(_mySkill.at(i)->label2);
	}

	_selSkill = 0;
}

void SkillLayer::setSpecial()
{
	if (player->getSkill()->getSpecialName().compare("") == 0) {
		_mountSkill[1]->sprite->setVisible(false);
		_mountSkill[1]->label->setString("");
		_mountSkill[1]->label2->setString("");
	}
	else {
		_mountSkill[1]->sprite->setVisible(true);
		_mountSkill[1]->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", player->getSkill()->getSpecialName().getCString()));
		_mountSkill[1]->label->setString(player->getSkill()->getSpecialName().getCString());
		_mountSkill[1]->label2->setString(player->getSkill()->getSpecialEx().getCString());
	}

	for (int i = 0; i < _mySkill.size(); i++) {
		_mySkill.at(i)->layer->removeFromParentAndCleanup(true);
	}
	_mySkill.clear();

	for (int i = 0; i < player->getSkill()->getMySpecialSize(); i++) {
		_mySkill.push_back(new RightSkill({ Layer::create() }));
		_mySkill.back()->layer->setPosition(125, 216 - 113 * i);
		this->addChild(_mySkill.back()->layer);

		_mySkill.back()->box = Sprite::create("Main/SkillSelect_1.png");
		_mySkill.back()->box->setPositionY(-22);
		_mySkill.back()->layer->addChild(_mySkill.back()->box);

		_mySkill.back()->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_icon.png", player->getSkill()->getMySpecialName(i).getCString()));
		_mySkill.back()->sprite->setPositionY(-22);
		_mySkill.back()->sprite->setScale(1.5f);
		_mySkill.back()->layer->addChild(_mySkill.at(i)->sprite);

		_mySkill.back()->label = Label::createWithTTF(player->getSkill()->getMySpecialName(i).getCString(), "fonts/Maplestory Bold.ttf", 20);
		_mySkill.back()->label->setAnchorPoint(Vec2(0, 0.5));
		_mySkill.back()->label->setPositionX(60);
		_mySkill.back()->label->setColor(Color3B(50, 50, 50));
		_mySkill.back()->layer->addChild(_mySkill.at(i)->label);

		_mySkill.back()->label2 = Label::createWithTTF(player->getSkill()->getMySpecialEx(i).getCString(), "fonts/Maplestory Bold.ttf", 15);
		_mySkill.back()->label2->setAnchorPoint(Vec2(0, 0.5));
		_mySkill.back()->label2->setPosition(50, -35);
		_mySkill.back()->label2->setColor(Color3B(100, 100, 100));
		_mySkill.back()->layer->addChild(_mySkill.at(i)->label2);
	}

	_selSkill = 1;
}
