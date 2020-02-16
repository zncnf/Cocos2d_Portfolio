#pragma once
#include "cocos_framework.h"
#include "Player.h"

class TopScene : public Scene
{
private:
	Layer* _layer;
	Sprite *_bg, *_map;

	int _gold, _time;

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TopScene);

private:
	void tick(float delta);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};