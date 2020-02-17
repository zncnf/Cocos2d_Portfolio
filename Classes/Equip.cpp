#include "Equip.h"

Equip::Equip(Layer* layer)
{
	_cache = SpriteFrameCache::getInstance(); 
	_cache->addSpriteFramesWithFile("Equip/Weapon/stick.plist");
	_cache->addSpriteFramesWithFile("Equip/Weapon/tube.plist");
	_cache->addSpriteFramesWithFile("Equip/Armor/commander.plist");
	_cache->addSpriteFramesWithFile("Equip/Shoes/luminous.plist");

	_layer = layer;

	/*_myWeapon.push_back(new Weapon({
		Sprite::createWithSpriteFrameName("stick_icon.png"),
		Sprite::createWithSpriteFrameName("stick_iconRaw.png"),
		Sprite::createWithSpriteFrameName("stick_stand_0_0.png"),
		"∏˘µ’¿Ã",
		10.0f }));*/

	setWeapon("∏˘µ’¿Ã");
	setArmor("ªÁ∑…∞¸ Ω¥∆Æ");
	setShoes("æﬂ±§ Ω≈πﬂ");
	mountWeapon(0);
	mountArmor(0);
	mountShoes(0);
	_mountWeapon->sprite->setTag(13);
	_mountArmor->body->setTag(11);
	_mountArmor->arm->setTag(16);
	_mountShoes->sprite->setTag(12);
	_layer->addChild(_mountArmor->body, 11);
	_layer->addChild(_mountShoes->sprite, 12);
	_layer->addChild(_mountWeapon->sprite, 13);
	_layer->addChild(_mountArmor->arm, 16);	

}

void Equip::setWeapon(String name)
{
	if (name.compare("∏˘µ’¿Ã") == 0) {
		_myWeapon.push_back(new Weapon({
		Sprite::createWithSpriteFrameName("stick_icon.png"),
		Sprite::createWithSpriteFrameName("stick_iconRaw.png"),
		Sprite::createWithSpriteFrameName("stick_stand_0_0.png"),
		"∏˘µ’¿Ã",
		"stick",
		10.0f }));
	} else if(name.compare("∆©∫Í") == 0) {
		_myWeapon.push_back(new Weapon({
		Sprite::createWithSpriteFrameName("tube_icon.png"),
		Sprite::createWithSpriteFrameName("tube_iconRaw.png"),
		Sprite::createWithSpriteFrameName("tube_stand_0_0.png"),
		"∆©∫Í",
		"tube",
		10.0f }));
	}
}

void Equip::setArmor(String name)
{
	if (name.compare("ªÁ∑…∞¸ Ω¥∆Æ") == 0) {
		_myArmor.push_back(new Armor({
			Sprite::createWithSpriteFrameName("commander_icon.png"),
			Sprite::createWithSpriteFrameName("commander_iconRaw.png"),
			Sprite::createWithSpriteFrameName("commander_stand_0_body.png"),
			Sprite::createWithSpriteFrameName("commander_stand_0_arm.png"),
			"ªÁ∑…∞¸ Ω¥∆Æ",
			"commander",
			10.0f }));
	}
}

void Equip::setShoes(String name)
{
	if (name.compare("æﬂ±§ Ω≈πﬂ") == 0) {
		_myShoes.push_back(new Shoes({
		Sprite::createWithSpriteFrameName("luminous_icon.png"),
		Sprite::createWithSpriteFrameName("luminous_iconRaw.png"),
		Sprite::createWithSpriteFrameName("luminous_stand_0_0.png"),
		"æﬂ±§ Ω≈πﬂ",
		"luminous",
		10.0f }));
	}
}

void Equip::setStand()
{
	_mountWeapon->sprite->cleanup();
	Vector<SpriteFrame*> frame[4];

	//∏ÿ√„
	for (int i = 0; i < 3; i++) {
		frame[0].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d_0.png", _mountWeapon->code.getCString(), i)));
		frame[1].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d_body.png", _mountArmor->code.getCString(), i)));
		frame[2].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d_arm.png", _mountArmor->code.getCString(), i)));
		frame[3].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d_0.png", _mountShoes->code.getCString(), i)));
	}
	_mountWeapon->sprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[0], 0.5f))));
	_mountArmor->body->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[1], 0.5f))));
	_mountArmor->arm->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[2], 0.5f))));
	_mountShoes->sprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[3], 0.5f))));
	for (int i = 0; i < 4; i++) {
		frame[i].clear();
	}
}

void Equip::setWalk()
{
	_mountWeapon->sprite->cleanup();
	_mountArmor->body->cleanup();
	_mountArmor->arm->cleanup();
	_mountShoes->sprite->cleanup();
	Vector<SpriteFrame*> frame[4];

	//∏ÿ√„
	for (int i = 0; i < 3; i++) {
		frame[0].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d_0.png", _mountWeapon->code.getCString(), i)));
		frame[1].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d_body.png", _mountArmor->code.getCString(), i)));
		frame[2].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d_arm.png", _mountArmor->code.getCString(), i)));
		frame[3].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d_0.png", _mountShoes->code.getCString(), i)));
	}
	_mountWeapon->sprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[0], 0.5f))));
	_mountArmor->body->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[1], 0.5f))));
	_mountArmor->arm->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[2], 0.5f))));
	_mountShoes->sprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[3], 0.5f))));
	for (int i = 0; i < 4; i++) {
		frame[i].clear();
	}
}

void Equip::setJump()
{
}

void Equip::setAttack()
{
}

void Equip::setDead()
{
}

void Equip::mountWeapon(int id)
{
	swap(_mountWeapon, _myWeapon[id]);
}

void Equip::mountArmor(int id)
{
	swap(_mountArmor, _myArmor[id]);
}

void Equip::mountShoes(int id)
{
	swap(_mountShoes, _myShoes[id]);
}
