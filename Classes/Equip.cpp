#include "Equip.h"

Equip::Equip()
{
	cache->addSpriteFramesWithFile("Equip/Weapon/stick.plist");
	cache->addSpriteFramesWithFile("Equip/Weapon/tube.plist");
	cache->addSpriteFramesWithFile("Equip/Armor/commander.plist");
	cache->addSpriteFramesWithFile("Equip/Shoes/luminous.plist");

	action1 = new Action;
	action1->setFlags(10);
	action2 = new Action;
	action2->setFlags(10);
	action3 = new Action;
	action3->setFlags(10);
	action4 = new Action;
	action4->setFlags(10);

	setWeapon("∏˘µ’¿Ã");
	setArmor("ªÁ∑…∞¸ Ω¥∆Æ");
	setShoes("æﬂ±§ Ω≈πﬂ");

	_mountWeapon = new Weapon({ 0 });
	_mountArmor = new Armor({ 0 });
	_mountShoes = new Shoes({ 0 });

	_mountWeapon->sprite = Sprite::create();
	_mountArmor->body = Sprite::create();
	_mountArmor->arm = Sprite::create();
	_mountShoes->sprite = Sprite::create();

	mountWeapon(0);
	mountArmor(0);
	mountShoes(0);
}

void Equip::setLayer(Layer* layer)
{
	_mountWeapon->sprite = Sprite::create();
	_mountArmor->body = Sprite::create();
	_mountArmor->arm = Sprite::create();
	_mountShoes->sprite = Sprite::create();

	layer->addChild(_mountWeapon->sprite, 13);
	layer->addChild(_mountArmor->body, 12);
	layer->addChild(_mountArmor->arm, 16);
	layer->addChild(_mountShoes->sprite, 13);
}

void Equip::setWeapon(String name, int n)
{
	if (n == -1) n = _myWeapon.size();
	else if (_myWeapon.size() == 0) n = 0;

	if (_myWeapon.size() == 0)_myWeapon.push_back(new Weapon({ 0 }));
	else _myWeapon.insert(_myWeapon.begin() + n, new Weapon({ 0 }));

	_myWeapon[n]->name = name;
	log("%s, %d", name.getCString(), n);
	if(name.compare("∏˘µ’¿Ã") == 0) {
		_myWeapon[n]->code = "stick";
		_myWeapon[n]->atk = 1.0f;
	}
	else if (name.compare("∆©∫Í") == 0) {
		_myWeapon[n]->code = "tube";
		_myWeapon[n]->atk = 2.0f;
	}

	_myWeapon[n]->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_stand_0_0.png", _myWeapon[n]->code.getCString()));
}

void Equip::setArmor(String name, int n)
{
	if (n == -1) n = _myArmor.size();
	else if (_myArmor.size() == 0) n = 0;

	if (_myArmor.size() == 0)_myArmor.push_back(new Armor({ 0 }));
	else _myArmor.insert(_myArmor.begin() + n, new Armor({ 0 }));

	_myArmor[n]->name = name;
	log("%s, %d", name.getCString(), n);
	if (name.compare("ªÁ∑…∞¸ Ω¥∆Æ") == 0) {
		_myArmor[n]->code = "commander";
		_myArmor[n]->life = 3.0f;
	}

	_myArmor[n]->body = Sprite::createWithSpriteFrameName(StringUtils::format("%s_stand_0_body.png", _myArmor[n]->code.getCString()));
	_myArmor[n]->arm = Sprite::createWithSpriteFrameName(StringUtils::format("%s_stand_0_arm.png", _myArmor[n]->code.getCString()));
}

void Equip::setShoes(String name, int n)
{
	if (n == -1) n = _myShoes.size();
	else if (_myShoes.size() == 0) n = 0;

	if (_myShoes.size() == 0)_myShoes.push_back(new Shoes({ 0 }));
	else _myShoes.insert(_myShoes.begin() + n, new Shoes({ 0 }));

	_myShoes[n]->name = name;
	log("%s, %d", name.getCString(), n);
	if (name.compare("æﬂ±§ Ω≈πﬂ") == 0) {
		_myShoes[n]->code = "luminous";
		_myShoes[n]->speed = 1.0f;
	}

	_myShoes[n]->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_stand_0_0.png", _myShoes[n]->code.getCString()));
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

	//∏ÿ√„
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
		_mountWeapon->name = _myWeapon[n]->name;

		_myWeapon.erase(_myWeapon.begin() + n);
		if (temp.compare("") != 0) setWeapon(temp, n);
	}
}

void Equip::mountArmor(int n)
{
	if (n < _myArmor.size()) {
		String temp = _mountArmor->name;
		_mountArmor->life = _myArmor[n]->life;
		_mountArmor->code = _myArmor[n]->code;
		_mountArmor->name = _myArmor[n]->name;

		_myArmor.erase(_myArmor.begin() + n);
		if (temp.compare("") != 0) setArmor(temp, n);
	}
}

void Equip::mountShoes(int n)
{
	if (n < _myShoes.size()) {
		String temp = _mountShoes->name;
		_mountShoes->speed = _myShoes[n]->speed;
		_mountShoes->code = _myShoes[n]->code;
		_mountShoes->name = _myShoes[n]->name;

		_myShoes.erase(_myShoes.begin() + n);
		if (temp.compare("") != 0) setShoes(temp, n);
	}
}

void Equip::clean()
{
	_mountWeapon->sprite->cleanup();
	_mountArmor->body->cleanup();
	_mountArmor->arm->cleanup();
	_mountShoes->sprite->cleanup();
}
