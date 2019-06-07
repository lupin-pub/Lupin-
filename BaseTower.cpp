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

		if (distance < currMinDistant&&monster->getAttackByTower())//�����ķ�Χ���ҿ��Ա�����
		{
			currMinDistant = distance;//�����������
			monsterTemp = monster;//Ŀǰ�����Ĺ���
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
	auto instance = GameManager::getInstance();//GamneManager������Ĳ�֪���� Ӧ�û��еİ�
	checkNearestMonster();
	//char temp1[20];
	//sprintf(temp1,"")
	if (nearestMonster != NULL && nearestMonster->getCurrHp() > 0)
	{
		auto currBullet = ArrowTowerBullet();//���ɹ���
		Point shootVector= nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();//�����
		auto pVectr = currBullet->getPosition() - shootVector;//��֪������
		auto moveToAction = MoveTo::create(0.5f, shootVector);
		currBullet->runAction(moveToAction);
		currBullet->shoot;//removeBullet!!
		//currBullet->setPosition();//������
		currBullet = NULL;
	}
}