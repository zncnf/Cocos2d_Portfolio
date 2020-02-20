#pragma once

#include <string>
#include <map>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include "cocos2d.h"
#include "ui/UIEditBox/UIEditBox.h"
#include "ui/CocosGUI.h"
#include "cocos2d/extensions/cocos-ext.h" // for tableView
#include "tinyxml2/tinyxml2.h" // for xml import
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"
#include "network/HttpClient.h"
#include "AudioEngine.h"
#include "Box2d/Box2d.h"

// using namespace
USING_NS_CC; // for cocos2d
USING_NS_CC_EXT; // the same using namespace extension
using namespace std; // for std
using namespace ui; // for ui
using namespace tinyxml2; // for xml import
using namespace cocos2d::network;
using namespace experimental;
// using namespace extension; // for tableView

// is make you can print korean language on cocos2d
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#define cuey Cuey::getInstance()
#define instance Director::getInstance()

class Cuey
{
private:
	Cuey();
	static Cuey* Instance;
	SpriteFrameCache* _cache;
	
public:
	static Cuey* getInstance();

	int rand(int min, int max);
	Size winsize() { return instance->getWinSize(); }
	Texture2D* texture(char* name) { return instance->getTextureCache()->addImage(name); }
	SpriteFrameCache* cache() { return _cache; }
};