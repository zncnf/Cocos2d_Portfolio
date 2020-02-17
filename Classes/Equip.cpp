#include "Equip.h"

Equip::Equip()
{
	_cache = SpriteFrameCache::getInstance(); 
	_cache->addSpriteFramesWithFile("Equip/Weapon/stick.plist");
	_cache->addSpriteFramesWithFile("Equip/Weapon/tube.plist");
	_cache->addSpriteFramesWithFile("Equip/Shoes/luminous.plist");
	_cache->addSpriteFramesWithFile("Equip/Armor/commander.plist");
}

void Equip::setWeapon(String name)
{
	if (name.compare("������") == 0) {
		_myWeapon.push_back(new Weapon({
		Sprite::createWithSpriteFrameName("stick_icon.png"),
		Sprite::createWithSpriteFrameName("stick_iconRaw.png"),
		Sprite::createWithSpriteFrameName("stick_stand_0_0.png"),
		"������",
		10.0f }));
	} else if(name.compare("Ʃ��") == 0) {
		_myWeapon.push_back(new Weapon({
		Sprite::createWithSpriteFrameName("tube_icon.png"),
		Sprite::createWithSpriteFrameName("tube_iconRaw.png"),
		Sprite::createWithSpriteFrameName("tube_stand_0_0.png"),
		"Ʃ��",
		10.0f }));
	}
}

void Equip::setArmor(String name)
{
	if (name.compare("��ɰ� ��Ʈ") == 0) {
		_myArmor.push_back(new Armor({
			Sprite::createWithSpriteFrameName("commander_icon.png"),
			Sprite::createWithSpriteFrameName("commander_iconRaw.png"),
			Sprite::createWithSpriteFrameName("commander_stand_0_body.png"),
			Sprite::createWithSpriteFrameName("commander_stand_0_arm.png"),
			"��ɰ� ��Ʈ",
			10.0f }));
	}
}

void Equip::setShoes(String name)
{
	if (name.compare("��ɰ� ��Ʈ") == 0) {
		_myShoes.push_back(new Shoes({
		Sprite::createWithSpriteFrameName("tube_icon.png"),
		Sprite::createWithSpriteFrameName("tube_iconRaw.png"),
		Sprite::createWithSpriteFrameName("tube_stand_0_0.png"),
		"�߱� �Ź�",
		10.0f }));
	}
}

void Equip::mountWeapon(int id)
{
	if (_mountWeapon != nullptr) {
		setWeapon(_mountWeapon->name);
	}
	_mountWeapon = _myWeapon[id];
}

void Equip::mountArmor(int id)
{
	if (_mountArmor != nullptr) {
		setArmor(_mountArmor->name);
	}
	_mountArmor = _myArmor[id];
}

void Equip::mountShoes(int id)
{
	if (_mountShoes != nullptr) {
		setArmor(_mountShoes->name);
	}
	_mountShoes = _myShoes[id];
}
