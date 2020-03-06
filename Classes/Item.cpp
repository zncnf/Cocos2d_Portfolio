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
	if (name.compare("µ·") == 0) {
		_item.push_back(new ITEM({
		"µ·",
		Sprite::create("Item/µ·.png"),
		Sprite::create("Item/µ·_icon.png"),
		NONE, 0
		}));
	}
	if (name.compare("´ÞÆØÀÌÀÇ ²®Áú") == 0) {
		_item.push_back(new ITEM({
		"´ÞÆØÀÌÀÇ ²®Áú",
		Sprite::create("Item/´ÞÆØÀÌÀÇ ²®Áú.png"),
		Sprite::create("Item/´ÞÆØÀÌÀÇ ²®Áú_icon.png"),
		NONE, 0
		}));
	}
	if (name.compare("µÅÁöÀÇ ¸Ó¸®") == 0) {
		_item.push_back(new ITEM({
		"µÅÁöÀÇ ¸Ó¸®",
		Sprite::create("Item/µÅÁöÀÇ ¸Ó¸®.png"),
		Sprite::create("Item/µÅÁöÀÇ ¸Ó¸®_icon.png"),
		NONE, 0
		}));
	}
}

void Item::dropItem(Sprite * monster)
{
	auto temp = Sprite::create();
	temp->setDisplayFrame(monster->displayFrame());
	temp->setPosition(monster->getPosition());
	temp->setAnchorPoint(Vec2(0, 0));
	for (int i = 0; i < _item.size(); i++) {
		if (_item[i]->state == NONE) {
			log("%s", _item[i]->name.getCString());
			_item[i]->sprite = Sprite::create(StringUtils::format("Item/%s.png", _item[i]->name.getCString()));
			_item[i]->sprite->setAnchorPoint(Vec2(0.5f, 0));
			_layer->addChild(_item[i]->sprite);
			_item[i]->state = DROP;
			_item[i]->sprite->setPosition(temp->getPosition());
			float x = (int)-_item.size() * 10 + 20 * i;
			if (_item[i]->sprite->boundingBox().getMinX() + x < 0) {
				x += _item[i]->sprite->getContentSize().width / 2;
			}
			if (_item[i]->sprite->boundingBox().getMaxX() > x + 1980) {
				x += -_item[i]->sprite->getContentSize().width / 2;
			}
			float y = -17;
			_item[i]->sprite->runAction(Spawn::create(
				JumpBy::create(0.8f, Vec2(x, y), 50, 1),
				Sequence::create(
					DelayTime::create(0.2f),
					CallFunc::create(CC_CALLBACK_0(Item::dropItem, this, monster)),
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
	_item[n]->speed -= 0.1f;
	_item[n]->sprite->setZOrder(2);
	_item[n]->sprite->runAction(Sequence::create(
		JumpTo::create(1 + _item[n]->speed, Vec2(player->getPositionX(), player->getPositionY()-10), 10, 1), 
		CallFunc::create(CC_CALLBACK_0(Item::pickupItem, this, player, n)),
		nullptr));
}
