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
	if (name.compare("돈") == 0 ||
		name.compare("달팽이의 껍질") == 0 ||
		name.compare("돼지의 머리") == 0 ||
		name.compare("좀비의 잃어버린 금니") == 0 ||
		name.compare("좀비의 잃어버린 어금니") == 0 ||
		name.compare("부러진 뿔") == 0 ||
		name.compare("어둠의 날개") == 0 ||
		name.compare("어둠의 돌") == 0 ||
		name.compare("어둠의 조각") == 0 ||
		name.compare("죽음의 공포") == 0 ||
		name.compare("어둠의 크리스탈") == 0 ||
		name.compare("흑수정") == 0) {
		for (int i = 0; i < _item.size(); i++) {
			if (_item[i]->name.compare(name.getCString()) == 0) {
				isEmpty = false;
				_item[i]->count++;
				break;
			}
		}
		if (isEmpty) {
			_item.push_back(new ITEM({}));
			_item.back()->sprite = Sprite::create(StringUtils::format("Item/%s.png", name.getCString()));
			_item.back()->name = name;
			_item.back()->state = NONE;
			_item.back()->count = 1;
		}
	}
}

void Item::removeItem(String name)
{
	for (int i = 0; _item.size(); i++) {
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
