#include "Player.h"

Player* Player::Instance = nullptr;

Player::Player()
{
	_player = Sprite::create("HelloWorld.png");
	_player->setPosition(500, 500);
	this->addChild(_player);

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
