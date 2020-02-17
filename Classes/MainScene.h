#pragma once
#include "Cuey.h"
#include "Player.h"

class MainScene : public Scene
{
private:
	Layer* _layer;

	int _gold, _time;

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);
};