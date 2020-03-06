#pragma once
#include "Cuey.h"

class Item : public Scene
{
	enum STATE {
		NONE,
		DROP,
		PICKUP,
		GET
	};
	struct ITEM
	{
		String name;
		Sprite* sprite;
		Sprite* icon;
		STATE state;
		float speed;
		int gold;
	};

	Layer* _layer;

	vector<ITEM*> _item;

	Action* _pickup;

	bool _isRemove;

public:
	Item();

	void setLayer(Layer* layer);

	void setItem(String name);

	void dropItem(Sprite* monster);

	void pickupItem(Layer* player, int n);

	int getItemSize() { return _item.size(); }

	Vec2 getItemPosition(int n) { return Vec2(
		_item[n]->sprite->boundingBox().getMidX(), _item[n]->sprite->boundingBox().getMaxY()); }

	Rect getRect(int n) {
		return Rect(_item[n]->sprite->boundingBox().getMinX(), _item[n]->sprite->boundingBox().getMidY(),
			_item[n]->sprite->getContentSize().width, _item[n]->sprite->getContentSize().height);
	}

	void removeItem(int n) { 
		//_item[n]->sprite->cleanup();
		_item[n]->sprite->runAction(FadeTo::create(0.5, 0));
		//_layer->removeChild(_item[n]->sprite);
		_item[n]->state = NONE;
	}

	bool getIsNone(int n) { return _item[n]->state == NONE ? true : false; }
	bool getIsDrop(int n) { return _item[n]->state == DROP ? true : false; }
	bool getIsPickUp(int n) { return _item[n]->state == PICKUP ? true : false; }
	bool getIsGet(int n) { return _item[n]->state == GET ? true : false; }
	bool getIsRemove() { return _isRemove; }

private:
	void setState(int n, STATE state) { _item[n]->state = state; }
};