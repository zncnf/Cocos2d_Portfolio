#pragma once
#include "Cuey.h"
#include "Player.h"
#include "EquipLayer.h"
#include "SkillLayer.h"
#include "ItemLayer.h"
#include "TopLayer.h"
#include "TopScene.h"

class MainScene : public Scene
{
private:
	Layer* _layer;
	EquipLayer* _equipLayer;
	SkillLayer* _skillLayer;
	ItemLayer* _itemLayer;
	TopLayer* _topLayer;

	Sprite* _bg;
	Sprite *_skillBg, *_skillLeftUI;

	Sprite *_equipBtn, *_skillBtn, *_itemBtn, *_topBtn;

	Sprite* _weaponBtn;

	Label* _goldLabel;

	bool _isAction;
	bool _isUse;

	EventListenerTouchOneByOne* listener;

public:
	static Scene* createScene();
	virtual bool init();

	void tick(float delta);

	CREATE_FUNC(MainScene);

private:

	void setisAction(bool b) { _isAction = b; }
	void setClean() { 
		player->getPlayer()->setPosition(9999, 9999);
		player->getPet()->getMountPet()->setPosition(9999, 9999);
		player->getSkill()->setSkillClean();
		player->setStand();
		_equipLayer->setPosition(9999, 9999); 
		_skillLayer->setPosition(9999, 9999);
		_skillBg->setPosition(_skillLayer->getPosition());
		_skillLeftUI->setPosition(_skillLayer->getPosition() + Vec2(-231, 53));
		_itemLayer->setPosition(9999, 9999);
	}

	virtual void onEnter();

	virtual void onExit();

	virtual bool onTouchBegan(Touch* touch, Event* event);

	virtual void onTouchMoved(Touch* touch, Event* event);

	virtual void onTouchCancelled(Touch* touch, Event* event);

	virtual void onTouchEnded(Touch* touch, Event* event);
};
