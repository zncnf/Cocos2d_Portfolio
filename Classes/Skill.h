#pragma once
#include "Cuey.h"

class Skill : public Scene
{
private:
	struct Normal {
		Sprite *attack, *hit, *rect;
		String name, code;
		float atkf, delay;
		int count, atkCount, hitCount;
	};

	struct Special {
		String name, ex;
		float delay;
	};

	Layer* _layer;
	Layer* _player;

	float _delay;

	bool _isWay;
	bool _isNormal;

	int _isAllKill;
	bool _isShield;

	Action *action1;
	Animate *action2, *action3, *action4;

	vector<Normal*> _myNormal;
	vector<Special*> _mySpecial;

	Normal* _mountNormal;
	Special* _mountSpecial;

public:
	Skill();

	void setLayer(Layer* layer, Layer* player);

	void setNormal(String name, int n = -1);
	void setSpecial(String name, int n = -1);

	void setWay(bool way);

	void mountNormal(int n);
	void mountSpecial(int n);

	void playNormal();
	void playNormalClean();
	void playNormalHit(Vec2 pt);
	void playNormalHitClean(Sprite* sprite);

	void playSpecial(bool isGame = true);

	void tick(float delta);

	void viewRect(bool view) { 
		_mountNormal->rect->setVisible(view);
	}

	bool getIsNormal() { return _isNormal; }

	int getMyNormalSize() { return _myNormal.size(); }
	String getMyNormalName(int n) { return _myNormal.at(n)->name; }
	String getMyNormalCode(int n) { return _myNormal.at(n)->code; }
	float getMyNormalAtkf(int n) { return _myNormal.at(n)->atkf; }
	int getMyNormalCount(int n) { return _myNormal.at(n)->count; }
	int getMyNormalAtkCount(int n) { return _myNormal.at(n)->atkCount; }
	float getMyNormalDelay(int n) { return _myNormal.at(n)->delay; }

	int getMySpecialSize() { return _mySpecial.size(); }
	String getMySpecialName(int n) { return _mySpecial.at(n)->name; }
	String getMySpecialEx(int n) { return _mySpecial.at(n)->ex; }
	float getMySpecialDelay(int n) { return _mySpecial.at(n)->delay; }

	Rect getNormalRect() {
		return Rect(_player->getPositionX() + _mountNormal->rect->boundingBox().getMinX(), _player->getPositionY() + _mountNormal->rect->boundingBox().getMinY(),
			_mountNormal->rect->getContentSize().width, _mountNormal->rect->getContentSize().height);
	}
	String getNormalName() { return _mountNormal->name; }
	String getNormalCode() { return _mountNormal->code; }
	float getNormalAtkf() { return _mountNormal->atkf; }
	int getNormalCount() { return _mountNormal->count; }
	int getNormalAtkCount() { return _mountNormal->atkCount; }
	float getNormalDelay() { return _mountNormal->delay; }

	String getSpecialName() { return _mountSpecial->name; }
	String getSpecialEx() { return _mountSpecial->ex; }
	float getSpecialDelay() { return _mountSpecial->delay; }

	void setIsAllKill(int isKill) { _isAllKill = isKill; }
	int getIsAllKill() { return _isAllKill; }

	void setIsShield(bool isShield) { _isShield = isShield; }
	bool getIsShield() { return _isShield; }

	void setSkillClean() {
		if(_layer->getChildByTag(50) != nullptr) _layer->removeChildByTag(50, true);
		if (_player->getChildByTag(50) != nullptr) _player->removeChildByTag(50, true);
		_mountNormal->attack->setVisible(false);
	}

	float getDelay() { return _delay; }
};