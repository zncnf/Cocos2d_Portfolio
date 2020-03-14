#pragma once
#include "Cuey.h"
#include "Player.h"
#include "Monster.h"
#include "Obstacle.h"
#include "IntroScene.h"

#define PTM_RATIO 32

class TopStage_2 : public Scene
{
private:
	Layer* _layer;
	Sprite *_bg, *_map;
	Label *_goldLabel, *_timeLabel, *_bestTimeLabel;

	Vector<Monster*> _monster;
	Vector<Obstacle*> _obstacle;

	int _gold;
	float _time;

	bool _itemChat[10];

	bool _isViewRect;

	bool _isGameSet;

	EventListenerTouchOneByOne* listener;

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TopStage_2);
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

	void setItemChatFalse(int n) { _itemChat[n] = false; }

	void setGame();

	void gameOver(float delta);
};