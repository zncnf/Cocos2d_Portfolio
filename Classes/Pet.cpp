#include "Pet.h"

Pet::Pet()
{
	cache->addSpriteFramesWithFile("Pet/寥煙.plist");
	cache->addSpriteFramesWithFile("Pet/際塑 睡辦.plist");

	setPet("際塑 睡辦");

	_mountPet = new PET({ 0 });

	mountPet(0);
}

void Pet::setLayer(Layer * layer, Layer* player)
{
	_layer = layer;
	_player = player;

	_mountPet->sprite = Sprite::create();

	_player->getParent()->addChild(_mountPet->sprite, 30);
	_mountPet->sprite->setPositionX(_player->getPositionX());
	_mountPet->sprite->setPositionY(_player->getPositionY()+1);

	_isFoot = false;
	_jPow = 0;

	_pickUpDelay = 0;

	setStand();

}

void Pet::setPet(String name, int n)
{
	if (n == -1) n = _myPet.size();
	else if (_myPet.size() == 0) n = 0;

	if (_myPet.size() == 0)_myPet.push_back(new PET({ 0 }));
	else _myPet.insert(_myPet.begin() + n, new PET({ 0 }));

	_myPet[n]->name = name;

	if (name.compare("寥煙") == 0) {
		_myPet[n]->standCount = 3;
		_myPet[n]->moveCount = 7;
	}
	else if (name.compare("際塑 睡辦") == 0) {
		_myPet[n]->standCount = 4;
		_myPet[n]->moveCount = 4;
	}

	_myPet[n]->sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_stand_0.png", name.getCString()));
}

void Pet::setStand()
{
	_state = STAND;

	_mountPet->sprite->cleanup();
	
	Vector<SpriteFrame*> frame;

	for (int i = 0; i <= _mountPet->standCount; i++) {
		frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_stand_%d.png", _mountPet->name.getCString(), i)));
	}
	_mountPet->sprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f))));

	frame.clear();
}

void Pet::setMove()
{
	_state = MOVE;

	_mountPet->sprite->cleanup();

	Vector<SpriteFrame*> frame;

	for (int i = 0; i <= _mountPet->moveCount; i++) {
		frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("%s_move_%d.png", _mountPet->name.getCString(), i)));
	}
	_mountPet->sprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f))));

	frame.clear();
}

void Pet::mountPet(int n)
{
	if (n < _myPet.size()) {
		String temp = _mountPet->name;
		_mountPet->name = _myPet[n]->name;
		_mountPet->standCount = _myPet[n]->standCount;
		_mountPet->moveCount = _myPet[n]->moveCount;

		_myPet.erase(_myPet.begin() + n);
		if (temp.compare("") != 0) setPet(temp, n);
	}
}

void Pet::tick()
{
	if (_pickUpDelay > 0) _pickUpDelay--;

	if (!_isFoot) {
		_jPow += 0.3f;
		_mountPet->sprite->setPositionY(_mountPet->sprite->getPositionY() -_jPow);
		if (_mountPet->sprite->getPositionY() + _mountPet->sprite->getContentSize().height / 2 < 207) {
			_mountPet->sprite->setPositionY(207 - _mountPet->sprite->getContentSize().height);
			_isFoot = true;
			_jPow = 0;
		}
	}
}
