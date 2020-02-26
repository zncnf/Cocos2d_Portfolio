#include "Skill.h"

Skill::Skill(Layer * layer)
{
	cache->addSpriteFramesWithFile("Skill/Normal/soulBlade.plist");

	_layer = layer;

	setNormal("소울 블레이드");

	_mountNormal = new Normal({ 0 });

	_mountNormal->attack = _myNormal.back()->attack;

	mountNormal(0);

	_layer->addChild(_mountNormal->attack);
}

void Skill::setNormal(String name)
{
	if (name.compare("소울 블레이드") == 0) {
		_myNormal.push_back(new Normal({
		Sprite::createWithSpriteFrameName("soulBlade_icon.png"),
		Sprite::createWithSpriteFrameName("soulBlade_attack_0.png"),
		Sprite::createWithSpriteFrameName("soulBlade_hit_0.png"),
		"소울 블레이드",
		"soulBlade",
		1.0f, 1, 11, 3}));
	}
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
	Vector<SpriteFrame*> frame;

	for (int i = 0; i <= _mountNormal->atkCount; i++) {
		frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_attack_%d.png", _mountNormal->code.getCString(), i)));
	}
	action1 = Animate::create(Animation::createWithSpriteFrames(frame, 0.1f));
	_mountNormal->attack->runAction(action1);
}
