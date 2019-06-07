#include "BaseMonster.h"
#include "GameManager.h"
#include "BaseMap.h"
#include "ShortSoldier.h"

ShortSoldier* ShortSoldier::createMonster(std::vector<Point> points, std::vector<std::vector<std::vector<Point>>> sonpath)
{
	auto monster = new ShortSoldier();
	if (monster && monster->init())
	{
		monster->setPointsVector(points);
		monster->setMaxHp(870);
		monster->setCurrHp(870);
		monster->setMoney(500);//打死一个小兵加多少钱？
		monster->sonPath = sonpath;
		monster->setForce(123);//攻击值
		monster->setArmor(33);//防御值
		monster->setScope(2);//近程
		//monster->setAttackByTower(true);
		//monster->setAttackBySoldier(true);//唔
		monster->setRunSpeed(15);
		monster->runNextPoint();
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}