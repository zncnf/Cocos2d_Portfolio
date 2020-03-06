#pragma once
#include "Cuey.h"

class Item : public Scene
{
	enum STATE {
		NONE,
		DROP,
		PICKUP
	};
	struct ITEM
	{
		String name;
		Sprite* sprite;
		Sprite* icon;
		STATE state;
		int gold;
	};

	Layer* _layer;

	vector<ITEM*> _item;

	Action* _pickup;

public:
	Item();

	void setLayer(Layer* layer);

	void setItem(String name);

	void dropItem(Sprite* monster);

	void pickupItem();

private:
	void setState(int n, STATE state) { _item[n]->state = state; }
};