#pragma once
#include "Cuey.h"
#include "Player.h"

class SkillLayer : public Layer
{
private:
	struct LeftSkill {
		Layer* layer;
		Sprite* sprite;
		Label* label;
		Label* label2;
	};

	Sprite* _leftUI;

	Sprite *_rightUI_normal, *_rightUI_special;
	
	Sprite *_normalBtn, *_specialBtn;

public:
	static Layer* createLayer();
	virtual bool init();

	CREATE_FUNC(SkillLayer);

	virtual bool onTouchBegan(Touch* touch, Event* event, bool isUse);

	virtual void onTouchMoved(Touch* touch, Event* event, bool isUse);

	virtual void onTouchCancelled(Touch* touch, Event* event, bool isUse);

	virtual void onTouchEnded(Touch* touch, Event* event, bool isUse);
};