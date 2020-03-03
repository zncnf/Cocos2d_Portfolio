#pragma once
#include "Cuey.h"
#include "TopScene.h"
#include "Player.h"

class IntroScene : public Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(IntroScene);
};