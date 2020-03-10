#pragma once
#include "Cuey.h"
#include "Player.h"
#include "TopScene.h"

class TopLayer : public Layer
{
private:
	Sprite* _tower;

public:
	static Layer* createLayer();
	virtual bool init();

	CREATE_FUNC(TopLayer);

	virtual bool onTouchBegan(Touch* touch, Event* event);

	virtual void onTouchMoved(Touch* touch, Event* event);

	virtual void onTouchCancelled(Touch* touch, Event* event);

	virtual void onTouchEnded(Touch* touch, Event* event);
};