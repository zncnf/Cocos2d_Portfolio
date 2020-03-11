#pragma once
#include "Cuey.h"
#include "Player.h"

class TopLayer : public Layer
{
private:
	Sprite* _tower;

	Sprite *_startBtn0, *_startBtn1, *_startBtn2;

public:
	static Layer* createLayer();
	virtual bool init();

	CREATE_FUNC(TopLayer);

	virtual bool onTouchBegan(Touch* touch, Event* event, bool isUse);

	virtual void onTouchMoved(Touch* touch, Event* event, bool isUse);

	virtual void onTouchCancelled(Touch* touch, Event* event, bool isUse);

	virtual void onTouchEnded(Touch* touch, Event* event, bool isUse);
};