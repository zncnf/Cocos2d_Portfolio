#include "Pet.h"

Pet::Pet()
{
	cache->addSpriteFramesWithFile("Pet/¹é·Ï.plist");
	cache->addSpriteFramesWithFile("Pet/»Ú¶ì ºÎ¿ì.plist");

	setPet("¹é·Ï");

	_mountPet = new PET({ 0 });

	mountPet(0);
}

void Pet::setLayer(Layer * layer, Layer* player)
{
	_layer = layer;
	_player = player;

	_mountPet->sprite = Sprite::create();

	_layer->addChild(_mountPet->sprite, 30);
	_mountPet->sprite->setPositionX(_player->getPositionX());
	_mountPet->sprite->setPositionY(_player->getPositionY()+1);

	_pickUpDelay = 0;

	setStand();
	setFall();
}

void Pet::setPet(String name)
{
	_myPet.push_back(new PET({
		Sprite::createWithSpriteFrameName(StringUtils::format("%s_stand_0.png", name.getCString())),
		name }));
	if (name.compare("¹é·Ï") == 0) {
		_myPet.back()->standCount = 3;
		_myPet.back()->moveCount = 7;
	};
	if (name.compare("»Ú¶ì ºÎ¿ì") == 0) {
		_myPet.back()->standCount = 4;
		_myPet.back()->moveCount = 4;
	};
}

void Pet::setFall()
{
	if (_mountPet->sprite->getPositionY() != _player->getPositionY() - 32) {
		_mountPet->sprite->runAction(Sequence::create(
			MoveTo::create(0.05, Vec2(_player->getPosition().x, _player->getPositionY() - 32)),
			CallFunc::create(CC_CALLBACK_0(Pet::setFall, this)),
			nullptr
		));
	}
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
		if (temp.compare("") != 0) setPet(temp);
	}
}

void Pet::tick()
{
	if (_pickUpDelay > 0) _pickUpDelay--;
}

Rect Pet::getRect()
{
	log("%f, %f", _mountPet->sprite->boundingBox().getMinX(), _mountPet->sprite->boundingBox().getMidY());
	return Rect(-_mountPet->sprite->boundingBox().getMinX(), -_mountPet->sprite->boundingBox().getMinY() - 200,
		_mountPet->sprite->getContentSize().width*200, _mountPet->sprite->getContentSize().height*200);
}
