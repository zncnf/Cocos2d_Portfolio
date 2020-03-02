#include "Equip.h"

Equip::Equip(Layer* layer)
{
	cache->addSpriteFramesWithFile("Equip/Weapon/stick.plist");
	cache->addSpriteFramesWithFile("Equip/Weapon/tube.plist");
	cache->addSpriteFramesWithFile("Equip/Armor/commander.plist");
	cache->addSpriteFramesWithFile("Equip/Shoes/luminous.plist");

	_layer = layer;

	action1 = new Action;
	action1->setFlags(10);
	action2 = new Action;
	action2->setFlags(10);
	action3 = new Action;
	action3->setFlags(10);
	action4 = new Action;
	action4->setFlags(10);

	setWeapon("¸ùµÕÀÌ");
	setArmor("»ç·É°ü ½´Æ®");
	setShoes("¾ß±¤ ½Å¹ß");

	_mountWeapon = new Weapon({ 0 });
	_mountArmor = new Armor({ 0 });
	_mountShoes = new Shoes({ 0 });

	_mountWeapon->sprite = _myWeapon.back()->sprite;
	_mountArmor->body = _myArmor.back()->body;
	_mountArmor->arm = _myArmor.back()->arm;
	_mountShoes->sprite = _myShoes.back()->sprite;

	mountWeapon(0);
	mountArmor(0);
	mountShoes(0);

	_layer->addChild(_mountArmor->body, 12);
	_layer->addChild(_mountShoes->sprite, 13);
	_layer->addChild(_mountWeapon->sprite, 13);
	_layer->addChild(_mountArmor->arm, 16);	

}

void Equip::setWeapon(String name)
{
	if (name.compare("¸ùµÕÀÌ") == 0) {
		_myWeapon.push_back(new Weapon({
		Sprite::createWithSpriteFrameName("stick_icon.png"),
		Sprite::createWithSpriteFrameName("stick_iconRaw.png"),
		Sprite::createWithSpriteFrameName("stick_stand_0_0.png"),
		"¸ùµÕÀÌ",
		"stick",
		10.0f }));
	} else if(name.compare("Æ©ºê") == 0) {
		_myWeapon.push_back(new Weapon({
		Sprite::createWithSpriteFrameName("tube_icon.png"),
		Sprite::createWithSpriteFrameName("tube_iconRaw.png"),
		Sprite::createWithSpriteFrameName("tube_stand_0_0.png"),
		"Æ©ºê",
		"tube",
		10.0f }));
	}
}

void Equip::setArmor(String name)
{
	if (name.compare("»ç·É°ü ½´Æ®") == 0) {
		_myArmor.push_back(new Armor({
			Sprite::createWithSpriteFrameName("commander_icon.png"),
			Sprite::createWithSpriteFrameName("commander_iconRaw.png"),
			Sprite::createWithSpriteFrameName("commander_stand_0_body.png"),
			Sprite::createWithSpriteFrameName("commander_stand_0_arm.png"),
			"»ç·É°ü ½´Æ®",
			"commander",
			10.0f }));
	}
}

void Equip::setShoes(String name)
{
	if (name.compare("¾ß±¤ ½Å¹ß") == 0) {
		_myShoes.push_back(new Shoes({
		Sprite::createWithSpriteFrameName("luminous_icon.png"),
		Sprite::createWithSpriteFrameName("luminous_iconRaw.png"),
		Sprite::createWithSpriteFrameName("luminous_stand_0_0.png"),
		"¾ß±¤ ½Å¹ß",
		"luminous",
		10.0f }));
	}
}

void Equip::setStand()
{
	clean();

	Vector<SpriteFrame*> frame[4];

	for (int i = 0; i < 3; i++) {
		frame[0].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d_0.png", _mountWeapon->code.getCString(), i)));
		frame[1].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d_body.png", _mountArmor->code.getCString(), i)));
		frame[2].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d_arm.png", _mountArmor->code.getCString(), i)));
		frame[3].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d_0.png", _mountShoes->code.getCString(), i)));
	}
	action1 = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[0], 0.5f)));
	_mountWeapon->sprite->runAction(action1);

	action2 = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[1], 0.5f)));
	_mountArmor->body->runAction(action2);

	action3 = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[2], 0.5f)));
	_mountArmor->arm->runAction(action3);

	action4 = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[3], 0.5f)));
	_mountShoes->sprite->runAction(action4);
	
	for (int i = 0; i < 4; i++) {
		frame[i].clear();
	}
}

void Equip::setWalk()
{
	clean();
	
	Vector<SpriteFrame*> frame[4];

	//¸ØÃã
	for (int i = 0; i < 4; i++) {
		frame[0].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_walk_%d_0.png", _mountWeapon->code.getCString(), i)));
		frame[1].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_walk_%d_body.png", _mountArmor->code.getCString(), i)));
		frame[2].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_walk_%d_arm.png", _mountArmor->code.getCString(), i)));
		frame[3].pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_walk_%d_0.png", _mountShoes->code.getCString(), i)));
	}
	action1 = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[0], 0.18f)));
	_mountWeapon->sprite->runAction(action1);

	action2 = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[1], 0.18f)));
	_mountArmor->body->runAction(action2);

	action3 = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[2], 0.18f)));
	_mountArmor->arm->runAction(action3);

	action4 = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame[3], 0.18f)));
	_mountShoes->sprite->runAction(action4);

	for (int i = 0; i < 4; i++) {
		frame[i].clear();
	}
}

void Equip::setJump()
{
	clean();

	_mountWeapon->sprite->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_jump_0_0.png", _mountWeapon->code.getCString())));
	_mountArmor->body->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_jump_0_body.png", _mountArmor->code.getCString())));
	_mountArmor->arm->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_jump_0_arm.png", _mountArmor->code.getCString())));
	_mountShoes->sprite->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_jump_0_0.png", _mountShoes->code.getCString())));
}	

void Equip::setAttack(int frame)
{
	clean();

	_mountWeapon->sprite->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_swing_%d_0.png", _mountWeapon->code.getCString(), frame)));
	_mountArmor->body->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_swing_%d_body.png", _mountArmor->code.getCString(), frame)));
	_mountArmor->arm->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_swing_%d_arm.png", _mountArmor->code.getCString(), frame)));
	_mountShoes->sprite->setSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_swing_%d_0.png", _mountShoes->code.getCString(), frame)));
	if (frame == 0) {
		_mountWeapon->sprite->setZOrder(3);	
	}
	else if (frame == 2) {
		_mountWeapon->sprite->setZOrder(13);
	}
}

void Equip::setDead()
{
	clean();

	_mountWeapon->sprite->setVisible(false);
	_mountArmor->body->setVisible(false);
	_mountArmor->arm->setVisible(false);
	_mountShoes->sprite->setVisible(false);
}

void Equip::setWay(bool way)
{
	_mountWeapon->sprite->setFlippedX(way);
	_mountArmor->body->setFlippedX(way);
	_mountArmor->arm->setFlippedX(way);
	_mountShoes->sprite->setFlippedX(way);
}

void Equip::mountWeapon(int n)
{	
	if (n < _myWeapon.size()) {
		String temp = _mountWeapon->name;
		_mountWeapon->atk = _myWeapon[n]->atk;
		_mountWeapon->code = _myWeapon[n]->code;
		_mountWeapon->icon = _myWeapon[n]->icon;
		_mountWeapon->iconRaw = _myWeapon[n]->iconRaw;
		_mountWeapon->name = _myWeapon[n]->name;

		_myWeapon.erase(_myWeapon.begin() + n);
		if (temp.getCString() != "") setWeapon(temp);
	}
}

void Equip::mountArmor(int n)
{
	if (n < _myArmor.size()) {
		String temp = _mountArmor->name;
		_mountArmor->life = _myArmor[n]->life;
		_mountArmor->code = _myArmor[n]->code;
		_mountArmor->icon = _myArmor[n]->icon;
		_mountArmor->iconRaw = _myArmor[n]->iconRaw;
		_mountArmor->name = _myArmor[n]->name;

		_myArmor.erase(_myArmor.begin() + n);
		if (temp.getCString() != "") setArmor(temp);
	}
}

void Equip::mountShoes(int n)
{
	if (n < _myShoes.size()) {
		String temp = _mountShoes->name;
		_mountShoes->speed = _myShoes[n]->speed;
		_mountShoes->code = _myShoes[n]->code;
		_mountShoes->icon = _myShoes[n]->icon;
		_mountShoes->iconRaw = _myShoes[n]->iconRaw;
		_mountShoes->name = _myShoes[n]->name;

		_myShoes.erase(_myShoes.begin() + n);
		if (temp.getCString() != "") setShoes(temp);
	}
}

void Equip::clean()
{
	_mountWeapon->sprite->cleanup();
	_mountArmor->body->cleanup();
	_mountArmor->arm->cleanup();
	_mountShoes->sprite->cleanup();
}
