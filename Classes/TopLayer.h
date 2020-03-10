#pragma once
#include "Cuey.h"
#include "Player.h"

class TopLayer : public Layer
{
private:


public:
	static Layer* createLayer();
	virtual bool init();

	CREATE_FUNC(TopLayer);
};