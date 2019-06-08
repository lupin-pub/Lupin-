#include "BaseMap.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void BaseMap::waveEvent()
{
	schedule(schedule_selector(BaseMap::addMonsters), 60.0f);
}

void BaseMap::addMonsters()
{
	auto sprite1 = ShortSoldier::createMonster(Point(0, 0));
	auto sprite2 = ShortSoldier::createMonster(Point(0, 0));
	auto sprite3 = LongSoldier::createMonster(Point(0, 0));
	auto sprite4 = LongSoldier::createMonster(Point(0, 0));
}