#include "ItemLayer.h"

Layer * ItemLayer::createLayer()
{
	return ItemLayer::create();
}

bool ItemLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	cache->addSpriteFramesWithFile("Main/아이템칸2.plist");
	cache->addSpriteFramesWithFile("Main/아이템 조합 모션1.plist");
	cache->addSpriteFramesWithFile("Main/아이템 조합 모션2.plist");

	auto bg = Sprite::create("Main/아이템창.png");
	this->addChild(bg);

	_leftUI = Sprite::create("Main/아이템창좌측UI.png");
	_leftUI->setPosition(-232, 49);
	this->addChild(_leftUI);

	for (int i = 0; i < 4; i++) {
		_selItem[i] = new LeftItem;
		_selItem[i]->layer = Layer::create();
		_selItem[i]->layer->setPosition(-382 + i * 100, 266);
		this->addChild(_selItem[i]->layer);

		Vector<SpriteFrame*> frame;

		_selItem[i]->box = Sprite::create("Main/아이템칸.png");
		_selItem[i]->layer->addChild(_selItem[i]->box);

		_selItem[i]->sprite = Sprite::create();
		_selItem[i]->sprite->setScale(1.5);
		_selItem[i]->layer->addChild(_selItem[i]->sprite);

		_selItem[i]->sel = "";
	}

	_rightUI = Sprite::create("Main/아이템창우측UI.png");
	_rightUI->setPosition(151, 0);
	this->addChild(_rightUI);

	_leftBtn = Sprite::create("Main/이동버튼.png");
	_leftBtn->setPosition(55, 285);
	this->addChild(_leftBtn);

	_rightBtn = Sprite::create("Main/이동버튼.png");
	_rightBtn->setFlippedX(true);
	_rightBtn->setPosition(250, 285);
	this->addChild(_rightBtn);

	_pickItemSprite = Sprite::create();
	_pickItemSprite->setScale(1.5);
	this->addChild(_pickItemSprite, 10);

	_selItem[4] = new LeftItem;
	_selItem[4]->layer = Layer::create();
	_selItem[4]->layer->setPosition(-232, 100);
	this->addChild(_selItem[4]->layer);

	_selItem[4]->box = Sprite::createWithSpriteFrameName("아이템칸2_0.png");
	_selItem[4]->box->setScale(2);
	_selItem[4]->layer->addChild(_selItem[4]->box);

	Vector<SpriteFrame*> frame;

	frame.pushBack(cache->spriteFrameByName("아이템칸2_0.png"));
	frame.pushBack(cache->spriteFrameByName("아이템칸2_1.png"));
	frame.pushBack(cache->spriteFrameByName("아이템칸2_2.png"));
	frame.pushBack(cache->spriteFrameByName("아이템칸2_3.png"));

	_selItem[4]->box->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1f))));
	_selItem[4]->box->setVisible(false);

	_selItem[4]->sprite = Sprite::create();
	_selItem[4]->sprite->setScale(1.5);
	_selItem[4]->layer->addChild(_selItem[4]->sprite);

	_makeBtn = Sprite::create("Main/조합버튼.png");
	_makeBtn->setPosition(-232, -277);
	this->addChild(_makeBtn);

	_pickItem = "";
	_selPage = 0;

	_selPt = Vec2(0, 0);

	setRecipe();

	setItem();

	return true;
}

bool ItemLayer::onTouchBegan(Touch * touch, Event * event, bool isUse)
{
	Vec2 pt = touch->getLocation() - this->getPosition();

	if (_pickItem.compare("") == 0) {
		if (_leftBtn->getBoundingBox().containsPoint(pt)) {
			_selPage--;
		}
		if (_rightBtn->getBoundingBox().containsPoint(pt)) {
			_selPage++;
		}
		for (int i = 0; i < _myItem.size(); i++) {
			if (_myItem.at(i)->box->getBoundingBox().containsPoint(pt - _myItem.at(i)->layer->getPosition())) {
				_pickItem = player->getItem()->getName(i + _selPage * 6);
				_pickItemSprite->setTexture(StringUtils::format("Item/%s.png", player->getItem()->getName(i + _selPage * 6).getCString()));
				_pickItemSprite->setPosition(pt);
				_selPt = pt;
				_selItem[4]->box->setVisible(false);
				_selItem[4]->sprite->setVisible(false);
				break;
			}
		}
		if (_makeBtn->getBoundingBox().containsPoint(pt)) {
			for (int i = 0; i < _recipe.size(); i++) {
				vector<String> temp;
				for (int j = 0; j < _recipe.at(i)->material.size(); j++) {
					temp.push_back(_recipe.at(i)->material[j].getCString());
				}
				vector<String> temp2;
				for (int j = 0; j < 4; j++) {
					if (_selItem[j]->sel.compare("") != 0) {
						temp2.push_back(_selItem[j]->sel.getCString());
					}
				}
				for (int j = 0; j < temp.size(); j++) {
					for (int k = 0; k < temp2.size(); k++) {
						if (temp2[k].compare(temp[j].getCString()) == 0) {
							temp.erase(temp.begin() + j--);
							temp2.erase(temp2.begin() + k--);
							break;
						}
					}
				}
				if (temp.size() == 0 && temp2.size() == 0 && player->getGold() >= _recipe.at(i)->gold) {
					_selItem[4]->box->setVisible(false);
					_selItem[4]->sprite->setVisible(false);
					player->appendGold(-_recipe.at(i)->gold);
					auto sprite = Sprite::create();
					sprite->setPosition(_selItem[4]->layer->getPosition() + Vec2(-5, 5));
					sprite->setScale(1.5);
					this->addChild(sprite, 1);

					for (int j = 0; j < 4; j++) {
						if (_selItem[j]->sel.compare("") != 0) {
							auto sprite2 = Sprite::create(StringUtils::format("Item/%s.png", _selItem[j]->sel.getCString()));
							sprite2->setPosition(_selItem[j]->layer->getPosition());
							sprite2->setScale(1.5);
							this->addChild(sprite2);

							sprite2->runAction(Sequence::create(
								DelayTime::create(j*0.2),
								Spawn::create(
									Sequence::create(
										EaseExponentialIn::create(MoveTo::create(1.25, _selItem[4]->layer->getPosition())),
										DelayTime::create(3 - j * 0.2),
										nullptr),
									EaseExponentialIn::create(RotateBy::create(1.3, 360)),
									nullptr),
								RemoveSelf::create(true),
								nullptr));
						}
					}

					Vector<SpriteFrame*> frame[2];

					for (int i = 0; i <= 4; i++) {
						frame[0].pushBack(cache->spriteFrameByName(StringUtils::format("아이템 조합 모션1_%d.png", i)));
					}

					for (int i = 0; i <= 6; i++) {
						frame[1].pushBack(cache->spriteFrameByName(StringUtils::format("아이템 조합 모션2_%d.png", i)));
					}
					sprite->runAction(Sequence::create(
						DelayTime::create(2),
						Repeat::create(Animate::create(Animation::createWithSpriteFrames(frame[0], 0.1f)), 4),
						CallFunc::create(CC_CALLBACK_0(ItemLayer::seMadeItem, this, i)),
						Animate::create(Animation::createWithSpriteFrames(frame[1], 0.13f)),
						RemoveSelf::create(true),
						nullptr
					));
					break;
				}
			}
		}
	}

	setItem();
	return true;
}

void ItemLayer::onTouchMoved(Touch * touch, Event * event, bool isUse)
{
	Vec2 pt = touch->getLocation() - this->getPosition();
	if (_pickItem.compare("") != 0) {
		_pickItemSprite->setPosition(pt);
	}
}

void ItemLayer::onTouchCancelled(Touch * touch, Event * event, bool isUse)
{

}

void ItemLayer::onTouchEnded(Touch * touch, Event * event, bool isUse)
{
	Vec2 pt = touch->getLocation() - this->getPosition();

	if (_pickItem.compare("") == 0) {
		for (int i = 0; i < 4; i++) {
			if (_selItem[i]->box->getBoundingBox().containsPoint(pt - _selItem[i]->layer->getPosition())) {
				if (_selItem[i]->sel.compare("") != 0) {
					player->getItem()->setItem(_selItem[i]->sel.getCString());
					_selItem[i]->sel = "";
					_selItem[i]->sprite->setPosition(9999, 9999);
					_selItem[4]->box->setVisible(false);
					_selItem[4]->sprite->setVisible(false);
				}
				break;
			}
		}
	} else {
		for (int i = 0; i < 4; i++) {
			if (_selItem[i]->box->getBoundingBox().containsPoint(pt - _selItem[i]->layer->getPosition())) {
				if (_selItem[i]->sel.compare("") != 0) {
					player->getItem()->setItem(_selItem[i]->sel.getCString());
				}
				_selItem[i]->sel = _pickItem;
				_selItem[i]->sprite->setTexture(StringUtils::format("Item/%s_icon.png", _selItem[i]->sel.getCString()));
				_selItem[i]->sprite->setPosition(_selItem[i]->box->getPosition());
				player->getItem()->removeItem(_selItem[i]->sel.getCString());
				_selItem[4]->box->setVisible(false);
				_selItem[4]->sprite->setVisible(false);
				break;
			}
		}
		if (_selPt == pt) {
			for (int i = 0; i < 4; i++) {
				if (_selItem[i]->sel.compare("") == 0) {
					_selItem[i]->sel = _pickItem;
					_selItem[i]->sprite->setTexture(StringUtils::format("Item/%s_icon.png", _selItem[i]->sel.getCString()));
					_selItem[i]->sprite->setPosition(_selItem[i]->box->getPosition());
					player->getItem()->removeItem(_selItem[i]->sel.getCString());
					break;
				}
			}
		}
		pt = Vec2(0, 0);
		_pickItem = "";
		_pickItemSprite->setPosition(9999, 9999);
	}
	for (int i = 0; i < _selRecipe.size(); i++) {
		_selRecipe[i]->removeFromParentAndCleanup(true);
	}
	_selRecipe.clear();

	for (int i = 0; i < _recipe.size(); i++) {//레시피
		vector<String> temp;
		bool isItem = false;
		for (int j = 0; j < 4; j++) {
			if (_selItem[j]->sel.compare("") != 0) {
				temp.push_back(_selItem[j]->sel.getCString());
				isItem = true;
			}
		}
		String mat = "";
		int ln = 1;
		for (int j = 0; j < _recipe.at(i)->material.size(); j++) {
			if (mat.compare("") != 0) {
				mat.append(" + ");
			}
			if(StringUtils::format("%s%s + %d", mat.getCString(), _recipe.at(i)->material[j].getCString(), _recipe.at(i)->gold).length() > 70 * ln) {
				mat.append("\n");
				ln++;
			}
			mat.append(_recipe.at(i)->material[j].getCString());
			for (int k = 0; k < temp.size(); k++) {
				if (_recipe.at(i)->material[j].compare(temp[k].getCString()) == 0) {
					temp.erase(temp.begin() + k);
					break;
				}
			}
		}
		if (temp.size() == 0 && isItem) {
			_selRecipe.push_back({ Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 14) });
			_selRecipe.back()->setString(StringUtils::format("%s = %s + %dG", _recipe.at(i)->complete.getCString(), mat.getCString(), (int)_recipe.at(i)->gold));
			_selRecipe.back()->setAnchorPoint(Vec2(0, 1));
			int n = _selRecipe.size();
			_selRecipe.back()->setPosition(-420, -220 + (n * 45));
			_selRecipe.back()->setColor(Color3B(100, 100, 100));
			this->addChild(_selRecipe.back());
		}
	}
	_makeBtn->setTexture("Main/조합버튼.png");
	for (int i = 0; i < _recipe.size(); i++) {
		vector<String> temp;
		for (int j = 0; j < _recipe.at(i)->material.size(); j++) {
			temp.push_back(_recipe.at(i)->material[j].getCString());
		}
		vector<String> temp2;
		for (int j = 0; j < 4; j++) {
			if (_selItem[j]->sel.compare("") != 0) {
				temp2.push_back(_selItem[j]->sel.getCString());
			}
		}
		for (int j = 0; j < temp.size(); j++) {
			for (int k = 0; k < temp2.size(); k++) {
				if (temp2[k].compare(temp[j].getCString()) == 0) {
					temp.erase(temp.begin() + j--);
					temp2.erase(temp2.begin() + k--);
					break;
				}
			}
		}
		if (temp.size() == 0 && temp2.size() == 0 && player->getGold() >= _recipe.at(i)->gold) {
			_makeBtn->setTexture("Main/조합버튼on.png");
			break;
		} 
	}

	setItem();
}

void ItemLayer::setItem()
{
	for (int i = 0; i < _myItem.size(); i++) {
		_myItem.at(i)->layer->removeFromParentAndCleanup(true);
	}
	_myItem.clear();
	for (int i = _selPage*6; i < player->getItem()->getItemSize(); i++) {
		if (_myItem.size() >= 6) break;
		_myItem.push_back(new RightItem({ Layer::create() }));
		_myItem.back()->layer->setPosition(50, 232 - 96 * (i - _selPage * 6));
		this->addChild(_myItem.back()->layer);

		_myItem.back()->box = Sprite::create("Main/아이템칸.png");
		_myItem.back()->box->setPositionY(-22);
		_myItem.back()->layer->addChild(_myItem.back()->box);

		_myItem.back()->sprite = Sprite::createWithTexture(cuey->texture(&StringUtils::format("Item/%s_icon.png", player->getItem()->getName(i).getCString())[0]));
		_myItem.back()->sprite->setPositionY(-22);
		_myItem.back()->sprite->setScale(1.5f);
		_myItem.back()->layer->addChild(_myItem.back()->sprite);

		_myItem.back()->label = Label::createWithTTF(player->getItem()->getName(i).getCString(), "fonts/Maplestory Bold.ttf", 20);
		_myItem.back()->label->setAnchorPoint(Vec2(0, 0.5));
		_myItem.back()->label->setPositionX(60);
		_myItem.back()->label->setColor(Color3B(50, 50, 50));
		_myItem.back()->layer->addChild(_myItem.back()->label);

		_myItem.back()->label2 = Label::createWithTTF("", "fonts/Maplestory Bold.ttf", 15);
		_myItem.back()->label2->setString(StringUtils::format("수량 : %d", player->getItem()->getCount(i)));
		_myItem.back()->label2->setAnchorPoint(Vec2(0, 0.5));
		_myItem.back()->label2->setPosition(50, -35);
		_myItem.back()->label2->setColor(Color3B(100, 100, 100));
		_myItem.back()->layer->addChild(_myItem.back()->label2);
	}
	_leftBtn->setPositionY(_selPage != 0 ? 285 : 9999);
	_rightBtn->setPositionY(player->getItem()->getItemSize() > (_selPage + 1) * 6 ? 285 : 9999);
}

void ItemLayer::seMadeItem(int n)
{
	if (_recipe.at(n)->kind.compare("일반스킬") == 0) {
		player->getSkill()->setNormal(_recipe.at(n)->complete);
		_selItem[4]->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", player->getSkill()->getMyNormalCode(player->getSkill()->getMyNormalSize() - 1).getCString()));
	}
	else if (_recipe.at(n)->kind.compare("필살기") == 0) {
		player->getSkill()->setSpecial(_recipe.at(n)->complete);
		_selItem[4]->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", _recipe.at(n)->complete.getCString()));
	}
	else if (_recipe.at(n)->kind.compare("무기") == 0) {
		player->getEquip()->setWeapon(_recipe.at(n)->complete);
		_selItem[4]->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", player->getEquip()->getMyWeaponCode(player->getEquip()->getMyWeaponSize() - 1).getCString()));
	}
	else if (_recipe.at(n)->kind.compare("옷") == 0) {
		player->getEquip()->setArmor(_recipe.at(n)->complete);
		_selItem[4]->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", player->getEquip()->getMyArmorCode(player->getEquip()->getMyArmorSize() - 1).getCString()));
	}
	else if (_recipe.at(n)->kind.compare("신발") == 0) {
		player->getEquip()->setShoes(_recipe.at(n)->complete);
		_selItem[4]->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", player->getEquip()->getMyShoesCode(player->getEquip()->getMyShoesSize() - 1).getCString()));
	}
	else if (_recipe.at(n)->kind.compare("펫") == 0) {
		player->getPet()->setPet(_recipe.at(n)->complete);
		_selItem[4]->sprite->setSpriteFrame(StringUtils::format("%s_icon.png", _recipe.at(n)->complete.getCString()));
	}
	_selItem[4]->box->setVisible(true);
	_selItem[4]->sprite->setVisible(true);
}

void ItemLayer::setRecipe()
{
	_recipe.push_back(new Recipe({ "일반스킬", "파이널 블로우" }));
	_recipe.back()->material.push_back({ "달팽이의 껍질" });
	_recipe.back()->material.push_back({ "달팽이의 껍질" });
	_recipe.back()->material.push_back({ "돼지의 머리" });
	_recipe.back()->material.push_back({ "돼지의 머리" });
	_recipe.back()->gold = 500;

	_recipe.push_back(new Recipe({ "일반스킬", "디바이드" }));
	_recipe.back()->material.push_back({ "어둠의 크리스탈" });
	_recipe.back()->material.push_back({ "어둠의 조각" });
	_recipe.back()->material.push_back({ "어둠의 조각" });
	_recipe.back()->gold = 1500;

	_recipe.push_back(new Recipe({ "필살기", "쉘터" }));
	_recipe.back()->material.push_back({ "돼지의 머리" });
	_recipe.back()->material.push_back({ "좀비의 잃어버린 금니" });
	_recipe.back()->material.push_back({ "좀비의 잃어버린 금니" });
	_recipe.back()->material.push_back({ "어둠의 크리스탈" });
	_recipe.back()->gold = 1600;

	_recipe.push_back(new Recipe({ "필살기", "다크 포그" }));
	_recipe.back()->material.push_back({ "어둠의 돌" });
	_recipe.back()->material.push_back({ "어둠의 날개" });
	_recipe.back()->material.push_back({ "어둠의 조각" });
	_recipe.back()->gold = 1800;

	_recipe.push_back(new Recipe({ "무기", "튜브" }));
	_recipe.back()->material.push_back({ "달팽이의 껍질" });
	_recipe.back()->material.push_back({ "달팽이의 껍질" });
	_recipe.back()->material.push_back({ "달팽이의 껍질" });
	_recipe.back()->material.push_back({ "돼지의 머리" });
	_recipe.back()->gold = 300;

	_recipe.push_back(new Recipe({ "무기", "태극부채" }));
	_recipe.back()->material.push_back({ "어둠의 날개" });
	_recipe.back()->material.push_back({ "어둠의 날개" });
	_recipe.back()->material.push_back({ "좀비의 잃어버린 어금니" });
	_recipe.back()->gold = 1000;

	_recipe.push_back(new Recipe({ "옷", "사령관 슈트" }));
	_recipe.back()->material.push_back({ "돼지의 머리" });
	_recipe.back()->material.push_back({ "좀비의 잃어버린 어금니" });
	_recipe.back()->material.push_back({ "좀비의 잃어버린 금니" });
	_recipe.back()->gold = 800;

	_recipe.push_back(new Recipe({ "옷", "나이트 매지션" }));
	_recipe.back()->material.push_back({ "부러진 뿔" });
	_recipe.back()->material.push_back({ "어둠의 날개" });
	_recipe.back()->material.push_back({ "어둠의 조각" });
	_recipe.back()->material.push_back({ "어둠의 조각" });
	_recipe.back()->gold = 1500;

	_recipe.push_back(new Recipe({ "신발", "무한의 포톤 신발" }));
	_recipe.back()->material.push_back({ "돼지의 머리" });
	_recipe.back()->material.push_back({ "좀비의 잃어버린 어금니" });
	_recipe.back()->material.push_back({ "좀비의 잃어버린 어금니" });
	_recipe.back()->gold = 1000;

	_recipe.push_back(new Recipe({ "신발", "슈퍼 부스터 운동화" }));
	_recipe.back()->material.push_back({ "부러진 뿔" });
	_recipe.back()->material.push_back({ "부러진 뿔" });
	_recipe.back()->material.push_back({ "어둠의 돌" });
	_recipe.back()->material.push_back({ "어둠의 조각" });
	_recipe.back()->gold = 1600;

	_recipe.push_back(new Recipe({ "펫", "백록" }));
	_recipe.back()->material.push_back({ "좀비의 잃어버린 금니" });
	_recipe.back()->material.push_back({ "좀비의 잃어버린 금니" });
	_recipe.back()->material.push_back({ "어둠의 조각" });
	_recipe.back()->gold = 1000;

	_recipe.push_back(new Recipe({ "펫", "쁘띠 부우" }));
	_recipe.back()->material.push_back({ "좀비의 잃어버린 금니" });
	_recipe.back()->material.push_back({ "좀비의 잃어버린 금니" });
	_recipe.back()->material.push_back({ "어둠의 크리스탈" });
	_recipe.back()->gold = 1000;

}