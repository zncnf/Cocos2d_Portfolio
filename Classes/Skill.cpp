#include "Skill.h"

Skill::Skill()
{
	setNormal("파이널 블로우");

	_mountNormal = new Normal({ 0 });

	setSpecial("다크 포그");

	//_mountSpecial = new Special({ 0 });

	mountNormal(0);

	//mountSpecial(0);
}

void Skill::setLayer(Layer* layer, Layer* player)
{
	_layer = layer;
	_player = player;

	_mountNormal->attack = Sprite::createWithSpriteFrameName(StringUtils::format("%s_attack_0.png", _mountNormal->code.getCString()));
	_mountNormal->attack->setPosition(_player->getPosition());
	_mountNormal->attack->setVisible(false);

	_layer->addChild(_mountNormal->attack, 1);

	_mountNormal->rect = Sprite::createWithTexture(nullptr, _mountNormal->attack->boundingBox());
	_mountNormal->rect->setPositionX((-_mountNormal->attack->boundingBox().size.width / 2));
	_mountNormal->rect->setColor(Color3B::RED);
	_mountNormal->rect->setOpacity(70);
	_mountNormal->rect->setTag(15);
	_mountNormal->rect->setVisible(false);
	_player->addChild(_mountNormal->rect, -1);

	_isWay = false;
	_isNormal = false;
}

void Skill::setNormal(String name, int n)
{
	if (n == -1) n = _myNormal.size();
	else if (_myNormal.size() == 0) n = 0;

	if (_myNormal.size() == 0)_myNormal.push_back(new Normal({ 0 }));
	else _myNormal.insert(_myNormal.begin() + n, new Normal({ 0 }));

	_myNormal[n]->name = name;
	if (name.compare("소울 블레이드") == 0) {
		cache->addSpriteFramesWithFile("Skill/Normal/soulBlade.plist");
		_myNormal[n]->name = "소울 블레이드";
		_myNormal[n]->code = "soulBlade";
		_myNormal[n]->atkf = 1.0f;
		_myNormal[n]->delay = 0.45f;
		_myNormal[n]->count = 1;
		_myNormal[n]->atkCount = 11;
		_myNormal[n]->hitCount = 3;
	} else if (name.compare("파이널 블로우") == 0) {
		cache->addSpriteFramesWithFile("Skill/Normal/파이널 블로우.plist");
		_myNormal[n]->name = "파이널 블로우";
		_myNormal[n]->code = "파이널 블로우";
		_myNormal[n]->atkf = 1.3f;
		_myNormal[n]->delay = 0.7f;
		_myNormal[n]->count = 3;
		_myNormal[n]->atkCount = 7;
		_myNormal[n]->hitCount = 4;
	}
	else if (name.compare("디바이드") == 0) {
		cache->addSpriteFramesWithFile("Skill/Normal/divide1.plist");
		cache->addSpriteFramesWithFile("Skill/Normal/divide2.plist");
		_myNormal[n]->name = "디바이드";
		_myNormal[n]->code = "divide";
		_myNormal[n]->atkf = 1.5f;
		_myNormal[n]->delay = 0.7f;
		_myNormal[n]->count = 6;
		_myNormal[n]->atkCount = 9;
		_myNormal[n]->hitCount = 5;
	}

	_myNormal[n]->attack = Sprite::createWithSpriteFrameName(StringUtils::format("%s_attack_0.png", _myNormal[n]->code.getCString()));
	_myNormal[n]->hit = Sprite::createWithSpriteFrameName(StringUtils::format("%s_hit_0.png", _myNormal[n]->code.getCString()));
}

void Skill::setSpecial(String name, int n)
{
	if (n == -1) n = _mySpecial.size();
	else if (_mySpecial.size() == 0) n = 0;

	if (_mySpecial.size() == 0)_mySpecial.push_back(new Special({ 0 }));
	else _mySpecial.insert(_mySpecial.begin() + n, new Special({ 0 }));

	_mySpecial[n]->name = name;
	if (name.compare("다크 포그") == 0) {
		for (int i = 1; i <= 12; i++) {
			cache->addSpriteFramesWithFile(StringUtils::format("Skill/Special/다크 포그%d.plist", i));
		}
		_mySpecial[n]->name = "다크 포그";
		_mySpecial[n]->ex = "몬스터 전멸";
		_mySpecial[n]->delay = 5.0f;
	} else if (name.compare("쉘터") == 0) {
		cache->addSpriteFramesWithFile("Skill/Special/쉘터.plist");
		_mySpecial[n]->name = "쉘터";
		_mySpecial[n]->ex = "5초간 무적";
		_mySpecial[n]->delay = 5.0f;
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
		_mountNormal->delay = _myNormal[n]->delay;
		_mountNormal->count = _myNormal[n]->count;
		_mountNormal->code = _myNormal[n]->code;
		_mountNormal->attack = _myNormal[n]->attack;
		_mountNormal->hit = _myNormal[n]->hit;
		_mountNormal->name = _myNormal[n]->name;
		_mountNormal->atkCount = _myNormal[n]->atkCount;
		_mountNormal->hitCount = _myNormal[n]->hitCount;

		_myNormal.erase(_myNormal.begin() + n);
		if (temp.compare("") != 0) setNormal(temp, n);
	}
}

void Skill::mountSpecial(int n)
{
	if (n < _mySpecial.size()) {
		String temp = _mountNormal->name;
		_mountSpecial->name = _mySpecial[n]->name;
		_mountSpecial->ex = _mySpecial[n]->ex;
		_mountSpecial->delay = _mySpecial[n]->delay;

		_mySpecial.erase(_mySpecial.begin() + n);
		if (temp.compare("") != 0) setSpecial(temp, n);
	}
}

void Skill::playNormal()
{
	_isNormal = true;
	_mountNormal->attack->setVisible(true);
	_mountNormal->attack->cleanup();

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
	_mountNormal->attack->setVisible(false);
	_isNormal = false;
}

void Skill::playNormalHit(Vec2 pt)
{
	Vector<SpriteFrame*> frame;

	for (int i = 0; i <= _mountNormal->hitCount; i++) {
		frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_hit_%d.png", _mountNormal->code.getCString(), i)));
	}

	Sprite* hitEffect = Sprite::create();
	_layer->addChild(hitEffect);

	hitEffect->setPosition(pt);
	hitEffect->runAction(Sequence::create(
		Animate::create(Animation::createWithSpriteFrames(frame, 0.1f)),
		CallFunc::create(CC_CALLBACK_0(Skill::playNormalHitClean, this, hitEffect)),
		nullptr));
}

void Skill::playNormalHitClean(Sprite* sprite)
{
	_layer->removeChild(sprite);
}
