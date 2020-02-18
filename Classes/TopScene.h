#pragma once
#include "Cuey.h"
#include "Player.h"
#include "Monster.h"

#define PTM_RATIO 32

class TopScene : public Scene
{
private:
	Layer* _layer;
	Sprite *_bg, *_map;

	Vector<Monster*> _monster;

	b2World* _world;

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