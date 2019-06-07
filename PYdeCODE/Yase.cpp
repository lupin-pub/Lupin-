#include "BaseMonster.h"
#include "GameManager.h"
#include "BaseMap.h"
#include "Yase.h"

Yase* Yase::createMonster(std::vector<Point> points, std::vector<std::vector<std::vector<Point>>> sonpath)
{
	auto monster = new Yase();
	if (monster && monster->init())
	{
		monster->setPointsVector(points);
		monster->setMaxHp(3938);
		monster->setCurrHp(3938);
		monster->setMoney(1500);//打死一个英雄加多少钱？
		monster->sonPath = sonpath;
		monster->setForce(179);//攻击值
		monster->setArmor(121);//防御值
		monster->setScope(2);//近程
		//monster->setAttackByTower(true);
		//monster->setAttackBySoldier(true);//唔
		monster->setRunSpeed(20);
		monster->runNextPoint();
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}