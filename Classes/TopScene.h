#pragma once
#include "cocos_framework.h"
#include "Player.h"

class TopScene : public Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TopScene);
};