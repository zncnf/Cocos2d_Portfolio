#include "Item.h"

Item::Item()
{
}

void Item::setLayer(Layer * layer)
{
	_layer = layer;
}

void Item::setItem(String name)
{
	if (name.compare("��") == 0) {
		_item.push_back(new ITEM({
		"��",
		Sprite::create("Item/��.png"),
		Sprite::create("Item/��_icon.png"),
		NONE
		}));
	}
	if (name.compare("�������� ����") == 0) {
		_item.push_back(new ITEM({
		"�������� ����",
		Sprite::create("Item/�������� ����.png"),
		Sprite::create("Item/�������� ����_icon.png"),
		NONE
		}));
	}
	if (name.compare("������ �Ӹ�") == 0) {
		_item.push_back(new ITEM({
		"������ �Ӹ�",
		Sprite::create("Item/������ �Ӹ�.png"),
		Sprite::create("Item/������ �Ӹ�_icon.png"),
		NONE
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