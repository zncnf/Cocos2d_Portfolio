#pragma once
#include "Cuey.h"

class Skill : public Scene
{
private:
	struct Normal {
		Sprite *icon, *iconRaw;
		Sprite* sprite;
		String name, code;
		float atk;
	};
	struct Special {
		Sprite *icon, *iconRaw;
		Sprite *body, *arm;
		String name, code;
		float life;
	};
	struct Passive {
		Sprite *icon, *iconRaw;
		Sprite* sprite;
		String name, code;
		float speed;
	};

	SpriteFrameCache* _cache;

	Layer* _layer;

	Action *action1, *action2, *action3, *action4;

	vector<Normal*> _myWeapon;
	vector<Special*> _myArmor;
	vector<Passive*> _myShoes;

	Normal* _mountWeapon;
	Special* _mountArmor;
	Passive* _mountShoes;

public:
	//Skill(Layer* layer);

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
};