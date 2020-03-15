#include "Skill.h"

Skill::Skill()
{
	setNormal("소울 블레이드");

	_mountNormal = new Normal({ 0 });

	mountNormal(0);

	_mountSpecial = new Special({ "" });

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

	_delay = 0;

	_isWay = false;
	_isNormal = false;
	_isAllKill = 0;
	_isShield = false;
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

	if (_mySpecial.size() == 0)_mySpecial.push_back(new Special({}));
	else _mySpecial.insert(_mySpecial.begin() + n, new Special({}));

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
		_mySpecial[n]->ex = "6초간 무적";
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
		_mountNormal->name = _myNormal[n]->name;
		_mountNormal->code = _myNormal[n]->code;
		_mountNormal->atkf = _myNormal[n]->atkf;
		_mountNormal->delay = _myNormal[n]->delay;
		_mountNormal->count = _myNormal[n]->count;
		_mountNormal->atkCount = _myNormal[n]->atkCount;
		_mountNormal->hitCount = _myNormal[n]->hitCount;

		_myNormal.erase(_myNormal.begin() + n);
		if (temp.compare("") != 0) setNormal(temp, n);
	}
}

void Skill::mountSpecial(int n)
{
	if (n < _mySpecial.size()) {
		String temp = _mountSpecial->name;
		_mountSpecial->name = _mySpecial[n]->name;
		_mountSpecial->ex = _mySpecial[n]->ex;
		_mountSpecial->delay = _mySpecial[n]->delay;

		_mySpecial.erase(_mySpecial.begin() + n);
		if (temp.compare("") != 0) setSpecial(temp, n);
	}
}

void Skill::playNormal()
{
	AudioEngine::play2d(StringUtils::format("Sound/%s_use.mp3", _mountNormal->name.getCString()), false, 1.0f);

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
	_mountNormal->attack->setSpriteFrame(StringUtils::format("%s_attack_0.png", _mountNormal->code.getCString()));
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
	AudioEngine::play2d(StringUtils::format("Sound/%s_hit.mp3", _mountNormal->name.getCString()), false, 1.0f);
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

void Skill::playSpecial(bool isGame)
{
	if (_delay <= 0 || !isGame) {
		AudioEngine::play2d(StringUtils::format("Sound/%s_use.mp3", _mountSpecial->name.getCString()), false, 1.0f);
		_delay = _mountSpecial->delay;
		if(!isGame) setSkillClean();
		vector<Vector<SpriteFrame*>> frame;
		if (_mountSpecial->name.compare("다크 포그") == 0) {
			frame.push_back({});
			for (int i = 0; i <= 33; i++) {
				frame.back().pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_attack_%d.png", _mountSpecial->name.getCString(), i)));
			}
			for (int i = 0; i < 4; i++) {
				auto attack = Sprite::create();
				if (isGame) attack->setPosition(_player->getPositionX() - 1050 + 700 * i, 445);
				else {
					if (i != 0) break;
					attack->setScale(0.5);
					attack->setPosition(460, 420);
					attack->setTag(50);
				}
				_layer->addChild(attack);
				setIsAllKill(1);
				attack->runAction(Spawn::create(
					Sequence::create(
						Animate::create(Animation::createWithSpriteFrames(frame[0], 0.1f)),
						RemoveSelf::create(true),
						nullptr),
					Sequence::create(
						DelayTime::create(2),
						CallFunc::create(CC_CALLBACK_0(Skill::setIsAllKill, this, 2)),
						nullptr),
					nullptr));
			}
			if (isGame) {
				auto bgColor = Sprite::createWithTexture(nullptr, Rect(-2500, -2500, 5000, 5000));
				bgColor->setColor(Color3B::BLACK);
				bgColor->setOpacity(0);
				_layer->addChild(bgColor, 30);
				bgColor->runAction(Sequence::create(
					FadeTo::create(0.5, 100),
					DelayTime::create(2.4),
					FadeTo::create(0.5, 0),
					RemoveSelf::create(true),
					nullptr
				));
			}
		}
		else if (_mountSpecial->name.compare("쉘터") == 0) {
			frame.push_back({});
			for (int i = 0; i <= 13; i++) {
				frame.back().pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_0_%d.png", _mountSpecial->name.getCString(), i)));
			}
			frame.push_back({});
			for (int i = 0; i <= 10; i++) {
				frame.back().pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_1_%d.png", _mountSpecial->name.getCString(), i)));
			}
			frame.push_back({});
			for (int i = 0; i <= 12; i++) {
				frame.back().pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_2_%d.png", _mountSpecial->name.getCString(), i)));
			}
			auto shield = Sprite::create();
			shield->setAnchorPoint(Vec2(0.865, 0.005));
			shield->setPosition(140, -50);
			shield->setColor(Color3B(250, 250, 255));
			shield->setTag(50);
			_player->addChild(shield, 100);

			_isShield = true;

			shield->runAction(Sequence::create(
				Animate::create(Animation::createWithSpriteFrames(frame[0], 0.1f)),
				Repeat::create(Animate::create(Animation::createWithSpriteFrames(frame[1], 0.1f)), 3),
				Animate::create(Animation::createWithSpriteFrames(frame[2], 0.1f)),
				CallFunc::create(CC_CALLBACK_0(Skill::setIsShield, this, false)),
				RemoveSelf::create(true),
				nullptr));
		}
	}
}

void Skill::tick(float delta)
{
	if (_delay > 0) _delay -= delta;
}
