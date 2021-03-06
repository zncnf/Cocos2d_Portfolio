#pragma once
#include "Cuey.h"

class Pet : public Scene {
private:
	enum STATE {
		STAND,
		MOVE
	};
	struct PET {
		Sprite* sprite;
		String name;
		int standCount, moveCount;
	};

	Layer* _layer;
	Layer* _player;

	vector<PET*> _myPet;

	PET* _mountPet;

	STATE _state;

	bool _isFoot;
	float _jPow;

	int _pickUpDelay;
public:
	Pet();

	void setLayer(Layer* layer, Layer* player);

	void setPet(String name, int n = -1);

	void setStand();
	void setMove();

	void mountPet(int n);

	void tick();

	void setPickUp() { _pickUpDelay = 10; }
	bool getIsPickUp() { return _pickUpDelay == 0 ? true : false; }

	Sprite* getMyPet(int n) { return _myPet[n]->sprite; }
	String getMyPetName(int n) { return _myPet[n]->name; }
	int getMyPetSize() { return _myPet.size(); }

	Sprite* getMountPet() { return _mountPet->sprite; }
	String getMountPetName() { return _mountPet->name; }

	bool getIsStand() { return _state == STAND ? true : false; }
	bool getIsMove() { return _state == MOVE ? true : false; }
};