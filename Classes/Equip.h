#pragma once
#include "cocos_framework.h"

class Equip : public Scene
{
private:
	struct Weapon {
		Sprite *icon, *iconRaw;
		Sprite* sprite;
		String name;
		float atk;
	};
	struct Armor {
		Sprite *icon, *iconRaw;
		Sprite *body, *arm;
		String name;
		float life;
	};
	struct Shoes {
		Sprite *icon, *iconRaw;
		Sprite* sprite;
		String name;
		float speed;
	};

	SpriteFrameCache* _cache;
	
	vector<Weapon*> _myWeapon;
	vector<Armor*> _myArmor;
	vector<Shoes*> _myShoes;

	Weapon* _mountWeapon;
	Armor* _mountArmor;
	Shoes* _mountShoes;

public:
	Equip();

	void setWeapon(String name);
	void setArmor(String name);
	void setShoes(String name);

	void mountWeapon(int id);
	void mountArmor(int id);
	void mountShoes(int id);

	int getMyWeaponSize() { return _myWeapon.size(); }
	Sprite* getMyWeaponIcon(int n) { return _myWeapon.at(n)->icon; }
	Sprite* getMyWeaponIconRaw(int n) { return _myWeapon.at(n)->iconRaw; }
	String getMyWeaponName(int n) { return _myWeapon.at(n)->name; }
	float getMyWeaponAtk(int n) { return _myWeapon.at(n)->atk; }

	int getMyArmorSize() { return _myArmor.size(); }
	Sprite* getMyArmorIcon(int n) { return _myArmor.at(n)->icon; }
	Sprite* getMyArmorIconRaw(int n) { return _myArmor.at(n)->iconRaw; }
	String getMyArmorName(int n) { return _myArmor.at(n)->name; }
	float getMyArmorAtk(int n) { return _myArmor.at(n)->life; }

	int getMyShoesSize() { return _myShoes.size(); }
	Sprite* getMyShoesIcon(int n) { return _myShoes.at(n)->icon; }
	Sprite* getMyShoesIconRaw(int n) { return _myShoes.at(n)->iconRaw; }
	String getMyShoesName(int n) { return _myShoes.at(n)->name; }
	float getMyShoesAtk(int n) { return _myShoes.at(n)->speed; }
};