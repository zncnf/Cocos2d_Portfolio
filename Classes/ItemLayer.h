#pragma once
#include "Cuey.h"
#include "Player.h"

class ItemLayer : public Layer
{
private:
	struct LeftItem {
		Layer* layer;
		Sprite* box;
		Sprite* sprite;
		Label *label;
		Label* label2;
	};

	struct RightItem {
		Layer* layer;
		Sprite* box;
		Sprite* sprite;
		Label *label;
		Label* label2;
	};

	Sprite* _leftUI;

	vector<LeftItem*> _selItem;

	Sprite* _rightUI;

	vector<RightItem*> _myItem;

public:
	static Layer* createLayer();
	virtual bool init();

	CREATE_FUNC(ItemLayer);

	virtual bool onTouchBegan(Touch* touch, Event* event, bool isUse);

	virtual void onTouchMoved(Touch* touch, Event* event, bool isUse);

	virtual void onTouchCancelled(Touch* touch, Event* event, bool isUse);

	virtual void onTouchEnded(Touch* touch, Event* event, bool isUse);

private:
	void setItem();
};