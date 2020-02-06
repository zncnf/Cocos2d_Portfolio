//물리엔진 실험

#pragma once

#include "cocos_framework.h"
#include "Box2d/Box2d.h"

#define PTM_RATIO 32

class TrainingPhysics : public Scene {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TrainingPhysics);

	Size winSize;
	Texture2D* texture;
	b2World* _world;

	void onEnter();
	void onExit();
	void tick(float dt);

	bool onTouchBegan(Touch* touch, Event* event);
	void addNewSpriteAtPosition(Vec2 location);

	~TrainingPhysics();
};