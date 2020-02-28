#include "Skill.h"

Skill::Skill(Layer* player)
{
	_player = player;

	cache->addSpriteFramesWithFile("Skill/Normal/soulBlade.plist");

	setNormal("소울 블레이드");

	_mountNormal = new Normal({ 0 });

	_mountNormal->attack = _myNormal.back()->attack;

	mountNormal(0);

	_mountNormal->rect = Sprite::createWithTexture(nullptr, _mountNormal->attack->boundingBox());
	_mountNormal->rect->setPositionX((-_mountNormal->attack->boundingBox().size.width / 2));
	_mountNormal->rect->setColor(Color3B::RED);
	_mountNormal->rect->setOpacity(100);
	_mountNormal->rect->setTag(15);
	_mountNormal->rect->setVisible(false);
	//_mountNormal->attack->addChild(_mountNormal->rect, -1);
	_player->addChild(_mountNormal->rect, -1);

	_isWay = false;
	_isNormal = false;
}

void Skill::setLayer(Layer* layer)
{
	_layer = layer;
	_layer->addChild(_mountNormal->attack);
	_mountNormal->attack->setPosition(_player->getPosition());
}

void Skill::setNormal(String name)
{
	if (name.compare("소울 블레이드") == 0) {
		_myNormal.push_back(new Normal({
		Sprite::createWithSpriteFrameName("soulBlade_icon.png"),
		Sprite::createWithSpriteFrameName("soulBlade_attack_0.png"),
		Sprite::createWithSpriteFrameName("soulBlade_hit_0.png"),
		nullptr,
		"소울 블레이드",
		"soulBlade",
		1.0f, 1, 11, 3}));
	}
}

void Skill::setWay(bool way)
{
	_mountNormal->attack->setFlippedX(way);
	_mountNormal->attack->setPositionX(-_mountNormal->attack->getPositionX());
	_mountNormal->rect->setPositionX((_mountNormal->attack->boundingBox().size.width / 2 * (way ? 1 : -1)));
	_isWay = way;
}

void Skill::mountNormal(int n)
{
	if (n < _myNormal.size()) {
		String temp = _mountNormal->name;
		_mountNormal->atkf = _myNormal[n]->atkf;
		_mountNormal->count = _myNormal[n]->count;
		_mountNormal->code = _myNormal[n]->code;
		_mountNormal->icon = _myNormal[n]->icon;
		_mountNormal->attack = _myNormal[n]->attack;
		_mountNormal->hit = _myNormal[n]->hit;
		_mountNormal->name = _myNormal[n]->name;
		_mountNormal->atkCount = _myNormal[n]->atkCount;
		_mountNormal->hitCount = _myNormal[n]->hitCount;

		_myNormal.erase(_myNormal.begin() + n);
		if (temp.getCString() != "") setNormal(temp);
	}
}

void Skill::playNormal()
{
	_isNormal = true;
	Vector<SpriteFrame*> frame;

	for (int i = 0; i <= _mountNormal->atkCount; i++) {
		frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_attack_%d.png", _mountNormal->code.getCString(), i)));
	}
	action1 = Sequence::create(
		Animate::create(Animation::createWithSpriteFrames(frame, 0.1f)),
		CallFunc::create(CC_CALLBACK_0(Skill::playNormalClean, this)),
		nullptr);
	_mountNormal->attack->runAction(action1);
	_mountNormal->attack->setPositionX(_player->getPositionX() + (_mountNormal->attack->boundingBox().size.width / 2 * (_isWay ? 1 : -1)));
	_mountNormal->attack->setPositionY(_player->getPositionY() + _mountNormal->attack->boundingBox().size.height / 5);
}

void Skill::playNormalClean()
{
	_mountNormal->attack->setSpriteFrame(StringUtils::format("%s_attack_0.png", _mountNormal->code.getCString()));
	_isNormal = false;
}
