#pragma once
#include "Cuey.h"
#include "Player.h"

class EquipLayer : public Layer
{
private:
	struct LeftEquip {
		Layer* layer;
		Sprite* sprite;
		Label* label;
		Label* label2;
	};

	struct RightEquip {
		Layer* layer;
		Sprite* sprite;
		Label* label;
		Label* label2;
	};

public:
	static Layer* createLayer();
	virtual bool init();

	//left
	Sprite *_leftUI;

	Label* _stats;

	vector<LeftEquip*> _mountEquip;


	//right
	Sprite *_rightUI_weapon, *_rightUI_armor, *_rightUI_shoes, *_rightUI_pet;

	Sprite *_weaponBtn, *_armorBtn, *_shoesBtn, *_petBtn;

	vector<RightEquip*> _myEquip;

	int _selEquip;

	CREATE_FUNC(EquipLayer);

	virtual bool onTouchBegan(Touch* touch, Event* event, bool isUse);

	virtual void onTouchMoved(Touch* touch, Event* event, bool isUse);

	virtual void onTouchCancelled(Touch* touch, Event* event, bool isUse);

	virtual void onTouchEnded(Touch* touch, Event* event, bool isUse);

private:
	void setWeapon();
	void setArmor();
	void setShoes();
	void setPet();
};