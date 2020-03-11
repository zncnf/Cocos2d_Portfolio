#pragma once
#include "Cuey.h"

class Equip : public Scene
{
private:
	struct Weapon {
		Sprite* sprite;
		String name, code;
		float atk;
	};
	struct Armor {
		Sprite *body, *arm;
		String name, code;
		float life;
	};
	struct Shoes {
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
	Equip();

	void setLayer(Layer* layer);

	void setWeapon(String name, int n = -1);
	void setArmor(String name, int n = -1);
	void setShoes(String name, int n = -1);

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
	String getMyWeaponName(int n) { return _myWeapon.at(n)->name; }
	String getMyWeaponCode(int n) { return _myWeapon.at(n)->code; }
	float getMyWeaponAtk(int n) { return _myWeapon.at(n)->atk; }

	int getMyArmorSize() { return _myArmor.size(); }
	String getMyArmorName(int n) { return _myArmor.at(n)->name; }
	String getMyArmorCode(int n) { return _myArmor.at(n)->code; }
	float getMyArmorLife(int n) { return _myArmor.at(n)->life; }

	int getMyShoesSize() { return _myShoes.size(); }
	String getMyShoesName(int n) { return _myShoes.at(n)->name; }
	String getMyShoesCode(int n) { return _myShoes.at(n)->code; }
	float getMyShoesSpeed(int n) { return _myShoes.at(n)->speed; }


	String getMountWeaponName() { return _mountWeapon->name; }
	String getMountWeaponCode() { return _mountWeapon->code; }
	float getMountWeaponAtk() { return _mountWeapon->atk; }

	String getMountArmorName() { return _mountArmor->name; }
	String getMountArmorCode() { return _mountArmor->code; }
	float getMountArmorLife() { return _mountArmor->life; }

	String getMountShoesName() { return _mountShoes->name; }
	String getMountShoesCode() { return _mountShoes->code; }
	float getMountShoesSpeed() { return _mountShoes->speed; }

};