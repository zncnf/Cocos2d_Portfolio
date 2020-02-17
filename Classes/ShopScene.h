#pragma once
#include "Cuey.h"
#include "Player.h"

class ShopScene : public Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ShopScene);
};