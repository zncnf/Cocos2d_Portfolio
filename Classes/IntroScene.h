#pragma once
#include "Cuey.h"
#include "MainScene.h"
#include "TopScene.h"
#include "Player.h"

class IntroScene : public Scene
{
private:
	Sprite *grade, *grade2, *message;

	int _bgm;

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(IntroScene);

private:
	void allUserFadeIn();
	void allUserFadeOut();
	void gotoTopScene();
};