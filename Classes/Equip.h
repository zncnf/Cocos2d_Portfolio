#pragma once
#include "Cuey.h"

class Equip : public Scene
{
private:
	struct Weapon {
		Sprite *icon, *iconRaw;
		Sprite* sprite;
		String name, code;
		float atk;
	};
	struct Armor {
		Sprite *icon, *iconRaw;
		Sprite *body, *arm;
		String name, code;
		float life;
	};
	struct Shoes {
		Sprite *icon, *iconRaw;
		Sprite* sprite;
		String name, code;
		float speed;
	};
	
	Layer* _layer;

	Action *action1, *action2, *action3, *action4;

	vector<Weapon*> _myWeapon;
	vector<Armor*> _myArmor;
	vector<Shoes*> _myShoes;

	Weapon* _mountWeapon;
	Armor* _mountArmor;
	Shoes* _mountShoes;

public:
	Equip(Layer* layer);

	void setWeapon(String name);
	void setArmor(String name);
	void setShoes(String name);

	void setStand();
	void setWalk();
	void setJump();
	void setAttack(int frame);
	void setDead();
	void setWay(bool way);

	void mountWeapon(int n);
	void mountArmor(int n);
	void mountShoes(int n);

	void clean();

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


	Sprite* getMountWeaponIcon() { return _mountWeapon->icon; }
	Sprite* getMountWeaponIconRaw() { return _mountWeapon->iconRaw; }
	String getMountWeaponName() { return _mountWeapon->name; }
	float getMountWeaponAtk() { return _mountWeapon->atk; }

	Sprite* getMountArmorIcon() { return _mountArmor->icon; }
	Sprite* getMountArmorIconRaw() { return _mountArmor->iconRaw; }
	String getMountArmorName() { return _mountArmor->name; }
	float getMountArmorAtk() { return _mountArmor->life; }

	Sprite* getMountShoesIcon() { return _mountShoes->icon; }
	Sprite* getMountShoesIconRaw() { return _mountShoes->iconRaw; }
	String getMountShoesName() { return _mountShoes->name; }
	float getMountShoesAtk() { return _mountShoes->speed; }

};