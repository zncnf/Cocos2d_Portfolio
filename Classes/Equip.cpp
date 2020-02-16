#include "Equip.h"

Equip::Equip()
{
	_cache = SpriteFrameCache::getInstance(); 
	_cache->addSpriteFramesWithFile("Equip/Weapon/stick.plist");
	_cache->addSpriteFramesWithFile("Equip/Weapon/tube.plist");
	_cache->addSpriteFramesWithFile("Equip/Shoes/luminous.plist");
	_cache->addSpriteFramesWithFile("Equip/Armor/commander.plist");


}
