#pragma once
#include "Cuey.h"

class Item : public Scene
{
	enum STATE {
		NONE,
		DROP,
		PICKUP,
		GET,
		REMOVE
	};
	struct ITEM
	{
		Sprite* sprite;
		String name;
		STATE state;
		int count;
	};

	Layer* _layer;

	vector<ITEM*> _item;

	Action* _pickup;

	bool _isRemove;

public:
	Item();

	void setLayer(Layer* layer);

	void setItem(String name);
	void removeItem(String name);

	void dropItem(Vec2 position);

	void pickupItem(Layer* player, int n);
	void pickupItem(Sprite* pet, int n);

	int getItemSize() { return _item.size(); }
	String getName(int n) { return _item[n]->name; }
	int getCount(int n) { return _item[n]->count; }
	int getId(String s);

	Vec2 getItemPosition(int n) { return Vec2(
		_item[n]->sprite->boundingBox().getMidX(), _item[n]->sprite->boundingBox().getMaxY()); }

	Rect getRect(int n) {
		return Rect(_item[n]->sprite->boundingBox().getMinX(), _item[n]->sprite->boundingBox().getMidY(),
			_item[n]->sprite->getContentSize().width, _item[n]->sprite->getContentSize().height);
	}

	void removeItem(int n) { 
		_item[n]->state = REMOVE;
		_isRemove = true;
		for (int i = 0; i < _item.size(); i++) {
			if(_item[i]->state != REMOVE) _isRemove = false;
		}
	}

	bool getIsNone(int n) { return _item[n]->state == NONE ? true : false; }
	bool getIsDrop(int n) { return _item[n]->state == DROP ? true : false; }
	bool getIsPickUp(int n) { return _item[n]->state == PICKUP ? true : false; }
	bool getIsGet(int n) { return _item[n]->state == GET ? true : false; }
	bool getIsRemove() { return _isRemove; }

private:
	void setState(int n, STATE state) { _item[n]->state = state; }
};