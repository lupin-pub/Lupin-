#include "BaseTower.h"
#include "SimpleAudioEngine.h"
#include "BaseMap.h"
#include "GameManager.h"

USING_NS_CC;

/*BaseTower::BaseTower()
{
	this->setScope(6.0);//�������д��
}
*/

void BaseTower::initTower()
{
	this->setScope(6.0);
	towerBase = Sprite::create("");
	spriteBullet = Sprite::create("");

	//���ʵ�� λ�� ��Щ��Ҫ��ôŪ��

	towerBase->addChild(spriteBullet);
	addChild(towerBase);

}

void BaseTower::checkNearestMonster()
{
	auto instance = GameManager::getInstance();
	if (this->getTowerColor() == 1)
	{
		auto monsterBlueVector = instance->monsterBlueVector;

		auto currMinDistant = this->scope;


		nearestMonster = NULL;
		for (int i = 0; i < monsterBlueVector.size(); i++)
		{
			auto monster = monsterBlueVector.at(i);
			double distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());

			if (distance < currMinDistant&&monster->getState()!=7)//�����ķ�Χ���ҿ��Ա�����
			{
				currMinDistant = distance;//�����������
				monsterTemp = monster;//Ŀǰ�����Ĺ���
			}
		}
		nearestMonster = monsterTemp;
	}
	else
	{
		auto monsterRedVector = instance->monsterRedVector;


		auto currMinDistant = this->scope;


		nearestMonster = NULL;
		for (int i = 0; i < monsterRedVector.size(); i++)
		{
			auto monster = monsterRedVector.at(i);
			double distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());

			if (distance < currMinDistant&&monster->getState()!=7)//�����ķ�Χ���ҿ��Ա�����
			{
				currMinDistant = distance;//�����������
				monsterTemp = monster;//Ŀǰ�����Ĺ���
			}
		}
		nearestMonster = monsterTemp;
	}
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
	auto instance = GameManager::getInstance();//
	checkNearestMonster();
	//char temp1[20];
	//sprintf(temp1,"")
	if (nearestMonster != NULL && nearestMonster->getCurrHp() > 0)
	{
		//auto currBullet = ArrowTowerBullet();//���ɹ���
		Point shootVector= nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();//�����
		//auto pVectr = currBullet->getPosition() - shootVector;//��֪������
		auto moveToAction = MoveTo::create(0.5f, shootVector);//�Ҿ�����moveby��
		//currBullet->runAction(moveToAction);
		//currBullet->shoot;//removeBullet!!
		//currBullet->setPosition();//������
		//currBullet = NULL;
	}
	runAction(Sequence::create(moveToAction, CallFuncN::create(CC_CALLBACK_0(Bullet::removeBullet, this)), NULL));//BulletAction��ֱ�߷��� removeBullet�жϻ��в��ӵ���ʧ
}

void BaseTower::removeBullet()//������
{
	bool isMissed = true;
	auto instance = GameManager::getInstance();
	//bullet���ھ�������
	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height / 2,
		this->spriteBullet->getContentSize().width,
		this->spriteBullet->getContentSize().height);//�;����˾Ͳ�������������
	if (this->getTowerColor() == 1)//red
	{
		auto monsterBlueVector = instance->monsterBlueVector;//ɶ��˼��

		for (int j = 0; j < monsterBlueVector.size(); j++)
		{
			auto monster = monsterBlueVector.at(j);
			auto monsterRect = monster->baseSprite->getBoundingBox();
			if (monsterRect.intersectsRect(bulletRect) && monster->getState() != 7)
			{
				auto currHp = monster->getCurrHp();

				currHp = currHp - this->getForce();//�ܵ�����Hp����

				if (currHp <= 0)
				{
					currHp = 0;
				}
				monster->setCurrHp(currHp);

				monster->getHpBar()->setPersentage((currHp / monster->getMaxHp()) * 100);//����Hp
				//monster->getHurt();     Wow!Ѫ�ȳ��棡
				isMissed = false;//����
				if (currHp == 0)
				{
					monster->death();
				}
				break;
			}
		}
	}
	else
	{
		auto monsterRedVector = instance->monsterRedVector;//ɶ��˼��

		for (int j = 0; j < monsterRedVector.size(); j++)
		{
			auto monster = monsterRedVector.at(j);
			auto monsterRect = monster->baseSprite->getBoundingBox();
			if (monsterRect.intersectsRect(bulletRect) && monster->getState() != 7)
			{
				auto currHp = monster->getCurrHp();

				currHp = currHp - this->getForce();//�ܵ�����Hp����

				if (currHp <= 0)
				{
					currHp = 0;
				}
				monster->setCurrHp(currHp);

				monster->getHpBar()->setPersentage((currHp / monster->getMaxHp()) * 100);//����Hp
				//monster->getHurt();     Wow!Ѫ�ȳ��棡
				isMissed = false;//����
				if (currHp == 0)
				{
					monster->death();
				}
				break;
			}
		}
	}
	//���ܻ������ж���ʧ
	this->removeFromParent();
	/*if (isMissed)
	{
		//��δ����
	}
	else
	{
		this->removeFromParent();
	}*/

}

/*void BaseTower::shoot()
{
	runAction(Sequence::create(bulletAction, CallFuncN::create(CC_CALLBACK_0(Bullet::removeBullet, this)), NULL));//BulletAction��ֱ�߷��� removeBullet�жϻ��в��ӵ���ʧ
}*/