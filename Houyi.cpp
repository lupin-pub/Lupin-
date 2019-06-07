#include "BaseMonster.h"
#include "GameManager.h"
#include "BaseMap.h"
#include "Houyi.h"

Houyi* Houyi::createMonster(std::vector<Point> points, std::vector<std::vector<std::vector<Point>>> sonpath)
{
	auto monster = new Houyi();
	if (monster && monster->init())
	{
		monster->setPointsVector(points);
		monster->setMaxHp(3182);
		monster->setCurrHp(3182);
		monster->setMoney(1500);//打死一个英雄加多少钱？
		monster->sonPath = sonpath;
		monster->setForce(180);//攻击值
		monster->setArmor(66);//防御值
		monster->setAttackByTower(true);
		monster->setAttackBySoldier(true);//唔
		monster->setRunSpeed(20);
		monster->runNextPoint();
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}