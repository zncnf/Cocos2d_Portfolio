#include "Item.h"

Item::Item()
{
	_isRemove = false;
}

void Item::setLayer(Layer * layer)
{
	_layer = layer;
}

void Item::setItem(String name)
{
	bool isEmpty = true;
	bool isHave = false;
	if (name.compare("µ∑") == 0) {
		for (int i = 0; i < _item.size(); i++) {
			if (_item[i]->name.compare(name.getCString()) == 0) {
				isEmpty = false;
				_item[i]->count++;
				break;
			}
		}
		isHave = true;
	} 
	else if (name.compare("¥ﬁ∆ÿ¿Ã¿« ≤Æ¡˙") == 0) {
		for (int i = 0; i < _item.size(); i++) {
			if (_item[i]->name.compare(name.getCString()) == 0) {
				isEmpty = false;
				_item[i]->count++;
				break;
			}
		}
		isHave = true;
	}
	else if (name.compare("µ≈¡ˆ¿« ∏”∏Æ") == 0) {
		for (int i = 0; i < _item.size(); i++) {
			if (_item[i]->name.compare(name.getCString()) == 0) {
				isEmpty = false;
				_item[i]->count++;
				break;
			}
		}
		isHave = true;
	}
	if (isEmpty && isHave) {
		_item.push_back(new ITEM({}));
		_item.back()->sprite = Sprite::create(StringUtils::format("Item/%s.png", name.getCString()));
		_item.back()->name = name;
		_item.back()->state = NONE;
		_item.back()->count = 1;
	}
}

void Item::removeItem(String name)
{
	for (int i = 0; i++; i++) {
		if (_item[i]->name.compare(name.getCString()) == 0) {
			if (_item[i]->count > 1) _item[i]->count--;
			else if(_item[i]->count == 1) _item.erase(_item.begin() + i);
			return;
		}
	}
}

void Item::dropItem(Vec2 position)
{
	for (int i = 0; i < _item.size(); i++) {
		if (_item[i]->state == NONE) {
			_item[i]->sprite = Sprite::create(StringUtils::format("Item/%s.png", _item[i]->name.getCString()));
			_item[i]->sprite->setAnchorPoint(Vec2(0.5f, 0));
			_layer->addChild(_item[i]->sprite);
			_item[i]->state = DROP;
			_item[i]->sprite->setPosition(position);
			float x = (int)-_item.size() * 10 + 20 * i;
			if (_item[i]->sprite->boundingBox().getMinX() + x < 0) {
				x += _item[i]->sprite->getContentSize().width / 2;
			}
			if (_item[i]->sprite->boundingBox().getMaxX() > x + 1980) {
				x += -_item[i]->sprite->getContentSize().width / 2;
			}
			_item[i]->sprite->runAction(Spawn::create(
				JumpBy::create(0.8f, Vec2(x, 0), 50, 1),
				Sequence::create(
					DelayTime::create(0.2f),
					CallFunc::create(CC_CALLBACK_0(Item::dropItem, this, position)),
					DelayTime::create(0.6f),
					CallFunc::create(CC_CALLBACK_0(Item::setState, this, i, PICKUP)),
					nullptr
				), nullptr
			));
			break;
		}
	}
}

void Item::pickupItem(Layer* player, int n)
{
	_item[n]->state = GET;
	_item[n]->sprite->setZOrder(2);

	_item[n]->sprite->runAction(Spawn::create(
		FadeTo::create(0.3, 0),
		MoveTo::create(0.3, Vec2(player->getPositionX(), player->getPositionY() - 20)),
		nullptr));
}

void Item::pickupItem(Sprite * pet, int n)
{
	_item[n]->state = GET;
	_item[n]->sprite->setZOrder(2);

	_item[n]->sprite->runAction(Spawn::create(
		FadeTo::create(0.3, 0),
		MoveTo::create(0.3, Vec2(pet->getPositionX(), pet->getPositionY())),
		nullptr));
}

int Item::getId(String s)
{
	for (int i = 0; i < _item.size(); i++) {
		if (_item[i]->name.compare(s.getCString()) == 0) return i;
	}
	return -1;
}
