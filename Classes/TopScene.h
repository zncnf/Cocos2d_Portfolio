#pragma once
#include "Cuey.h"
#include "Player.h"
#include "Monster.h"
#include "IntroScene.h"

#define PTM_RATIO 32

class TopScene : public Scene
{
private:
	Layer* _layer;
	Sprite *_bg, *_map;
	Label *_goldLabel, *_timeLabel;

	Vector<Monster*> _monster;

	int _gold;
	float _time;

	bool _isViewRect;

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TopScene);
private:
	void tick(float delta);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	virtual void onEnter();

	virtual void onExit();

	virtual bool onTouchBegan(Touch* touch, Event* event);

	virtual void onTouchMoved(Touch* touch, Event* event);

	virtual void onTouchEnded(Touch* touch, Event* event);

	virtual void onTouchCancelled(Touch* touch, Event* event);
};