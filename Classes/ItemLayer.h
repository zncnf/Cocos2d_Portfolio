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
		String sel;
	};

	struct RightItem {
		Layer* layer;
		Sprite* box;
		Sprite* sprite;
		Label *label;
		Label* label2;
	};

	struct Recipe {
		String kind;
		String complete;
		vector<String> material;
		int gold;
	};

	Sprite* _leftUI;

	LeftItem* _selItem[5];

	Sprite* _rightUI;

	vector<RightItem*> _myItem;

	Sprite *_leftBtn, *_rightBtn;

	Sprite* _pickItemSprite;

	String _pickItem;

	Sprite* _makeBtn;

	vector<Recipe*> _recipe;
	vector<Label*> _selRecipe;

	Vec2 _selPt;

	int _selPage;

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

	void seMadeItem(int n);

	void setRecipe();

	void makeBgm1();
};