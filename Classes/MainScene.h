#pragma once
#include "Cuey.h"
#include "Player.h"
#include "EquipLayer.h"
#include "TopLayer.h"

class MainScene : public Scene
{
private:
	Layer* _layer;
	EquipLayer* _equipLayer;
	TopLayer* _topLayer;

	Sprite* _bg;

	Sprite *_equipBtn, *_skillBtn, *_itemBtn;

	Sprite* _weaponBtn;

	bool _isAction;

public:
	static Scene* createScene();
	virtual bool init();

	void tick(float delta);

	CREATE_FUNC(MainScene);

private:

	void setisAction(bool b) { _isAction = b; }
	void moveTopLayer() { _equipLayer->setPosition(9999, 9999); }

	virtual void onEnter();

	virtual void onExit();

	virtual bool onTouchBegan(Touch* touch, Event* event);

	virtual void onTouchMoved(Touch* touch, Event* event);

	virtual void onTouchCancelled(Touch* touch, Event* event);

	virtual void onTouchEnded(Touch* touch, Event* event);
};
