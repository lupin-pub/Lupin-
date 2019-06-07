#include "BaseTower.h"
#include "SimpleAudioEngine.h"
#include "Bullet.h"
#include "BaseMap.h"
#include "GameManager.h"

USING_NS_CC;

void BaseTower::checkNearestMonster()
{
	auto instance = GameManager::getInstance();
	auto monsterVector = instance->monsterVector;

	auto currMinDistant = this->scope;


	nearestMonster = NULL;
	for (int i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		double distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());

		if (distance < currMinDistant&&monster->getAttackByTower())//在塔的范围内且可以被攻击
		{
			currMinDistant = distance;//攻击最近怪物
			monsterTemp = monster;//目前攻击的怪物
		}
	}
	nearestMonster = monsterTemp;
}

/*void BaseTower::onEnter()
{

}*/

/*void SimpleArrowTower::buildingAnimation()
{
	auto building = Sprite::create();
	auto constructing = Sprite::createWithSpriteFrameName("BlueDefense.png");

}*/

void BaseTower::shoot(float dt)
{
	auto instance = GameManager::getInstance();//GamneManager我是真的不知道啊 应该会有的吧
	checkNearestMonster();
	//char temp1[20];
	//sprintf(temp1,"")
	if (nearestMonster != NULL && nearestMonster->getCurrHp() > 0)
	{
		auto currBullet = ArrowTowerBullet();//生成弓箭
		Point shootVector= nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();//两点间
		auto pVectr = currBullet->getPosition() - shootVector;//不知道干嘛
		auto moveToAction = MoveTo::create(0.5f, shootVector);
		currBullet->runAction(moveToAction);
		currBullet->shoot;//removeBullet!!
		//currBullet->setPosition();//塔顶上
		currBullet = NULL;
	}
}