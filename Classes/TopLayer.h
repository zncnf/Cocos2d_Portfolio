#pragma once
#include "Cuey.h"
#include "Player.h"

class TopLayer : public Layer
{
private:
	Sprite* _tower;

public:
	static Layer* createLayer();
	virtual bool init();

	CREATE_FUNC(TopLayer);

	virtual bool onTouchBegan(Touch* touch, Event* event, bool isUse);

	virtual void onTouchMoved(Touch* touch, Event* event, bool isUse);

	virtual void onTouchCancelled(Touch* touch, Event* event, bool isUse);

	virtual void onTouchEnded(Touch* touch, Event* event, bool isUse);
};