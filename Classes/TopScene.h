#pragma once
#include "cocos_framework.h"
#include "Player.h"

class TopScene : public Scene
{
private:
	int _gold, _time;

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TopScene);
};