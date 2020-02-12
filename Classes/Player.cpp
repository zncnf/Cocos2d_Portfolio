#include "Player.h"

Player* Player::Instance = nullptr;

Player::Player()
{
	_cache = SpriteFrameCache::getInstance();
	_cache->addSpriteFramesWithFile("Monster/grinSnail.plist");

	_player = Sprite::createWithSpriteFrameName(StringUtils::format("%s_move_0.png", "grinSnail"));
	_player->setPosition(500, 500);

	Vector<SpriteFrame*> frame;

	//¸ØÃã
	frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("grinSnail_stand_0.png"));
	_stand = Animate::create(Animation::createWithSpriteFrames(frame, 0.08f));
	frame.clear();

	//ÀÌµ¿
	for (int i = 0; i < 5; i++) {
		frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("grinSnail_move_%d.png", i)));
	}
	_move = Animate::create(Animation::createWithSpriteFrames(frame, 0.08f));
	frame.clear();

	//ÇÇ°Ý
	frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("grinSnail_hit_0.png"));
	_hit = Animate::create(Animation::createWithSpriteFrames(frame, 0.08f));
	frame.clear();

	//Á×À½
	for (int i = 0; i < 18; i++) {
		frame.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(StringUtils::format("grinSnail_die_%d.png", i)));
	}
	_die = Animate::create(Animation::createWithSpriteFrames(frame, 0.08f));
	frame.clear();

	_lv = 1;
	_exp = 1;
	_expm = 1;
	_gold = 1;
	_item.push_back(new Item());
}

Player * Player::getInstance()
{
	if (Instance == nullptr) {
		Instance = new Player();
	}
	return Instance;
}

void Player::setLayer(Layer * layer)
{
	layer->addChild(_player);
	auto action = RepeatForever::create(Sequence::create(
		_stand,
		DelayTime::create(0.01),
		_move,
		DelayTime::create(0.01),
		_hit,
		DelayTime::create(0.01),
		_die,
		DelayTime::create(0.01),
		nullptr)
	);
	_player->runAction(action);
}
