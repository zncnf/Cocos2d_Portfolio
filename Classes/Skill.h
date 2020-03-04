#pragma once
#include "Cuey.h"

class Skill : public Scene
{
private:
	struct Normal {
		Sprite *icon;
		Sprite *attack, *hit, *rect;
		String name, code;
		float atkf, delay;
		int count, atkCount, hitCount;
	};

	enum SPECIALKIND {
		ATTACK = 0,
		BUF
	};

	struct Special {
		SPECIALKIND kind;
		Sprite *icon;
		Sprite *sprite, *Hit;
		String name, code;
		float statsf, delay;
	};

	struct Passive {
		Sprite *icon;
		Sprite* sprite;
		String name, code;
		float statsf;
	};

	Layer* _layer;
	Layer* _player;

	bool _isWay;
	bool _isNormal;

	Action *action1;
	Animate *action2, *action3, *action4;

	vector<Normal*> _myNormal;
	vector<Special*> _mySpecial;
	vector<Passive*> _myPassive;

	Normal* _mountNormal;
	Special* _mountSpecial;
	Passive* _mountPassive;

public:
	Skill(Layer* player);

	void setLayer(Layer* layer);
	void releaseLayer();
	void setNormal(String name);
	void setSpecial(String name);
	void setPassive(String name);

	void setWay(bool way);

	void mountNormal(int n);
	void mountSpecial(int n);
	void mountPassive(int n);

	void playNormal();
	void playNormalClean();
	void playNormalHit(Vec2 pt);
	void playNormalHitClean(Sprite* sprite);

	void viewRect(bool view) { 
		_mountNormal->rect->setVisible(view);
	}

	bool getIsNormal() { return _isNormal; }

	int getMyNormalSize() { return _myNormal.size(); }
	Sprite* getMyNormalIcon(int n) { return _myNormal.at(n)->icon; }
	String getMyNormalName(int n) { return _myNormal.at(n)->name; }
	float getMyNormalAtkf(int n) { return _myNormal.at(n)->atkf; }

	int getMySpecialSize() { return _mySpecial.size(); }
	Sprite* getMySpecialIcon(int n) { return _mySpecial.at(n)->icon; }
	String getMySpecialName(int n) { return _mySpecial.at(n)->name; }
	/*float getMySpecialAtk(int n) { return _mySpecial.at(n)->life; }*/

	int getMyPassiveSize() { return _myPassive.size(); }
	Sprite* getMyPassiveIcon(int n) { return _myPassive.at(n)->icon; }
	String getMyPassiveName(int n) { return _myPassive.at(n)->name; }
	/*float getMyPassiveAtk(int n) { return _myPassive.at(n)->speed; }*/

	Rect getNormalRect() {
		return Rect(_player->getPositionX() + _mountNormal->rect->boundingBox().getMinX(), _player->getPositionY() + _mountNormal->rect->boundingBox().getMinY(),
			_mountNormal->rect->getContentSize().width, _mountNormal->rect->getContentSize().height);
	}
	float getNormalAtkf() { return _mountNormal->atkf; }
	int getNormalCount() { return _mountNormal->count; }
	int getNormalAtkCount() { return _mountNormal->atkCount; }
	float getNormalDelay() { return _mountNormal->delay; }
};