#include "BaseMonster.h"
#include "GameManager.h"
#include "BaseMap.h"
#include "Houyi.h"

Houyi* Houyi::createMonster(std::vector<Point> points, std::vector<std::vector<std::vector<Point>>> sonpath)
{
	auto monster = new Houyi();
	if (monster && monster->init())
	{
		//monster->setPointsVector(points);
		monster->setMaxHp(3182);
		monster->setCurrHp(3182);
		monster->setMoney(1500);//����һ��Ӣ�ۼӶ���Ǯ��
		monster->sonPath = sonpath;
		monster->setForce(180);//����ֵ
		monster->setArmor(66);//����ֵ
		monster->setScope(5);//Զ��
		//monster->setAttackByTower(true);
		//monster->setAttackBySoldier(true);//��
		monster->setRunSpeed(20);
		monster->runNextPoint();
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}
void BaseMonster::removeBullet()//������ �̳в��Ķ� ��д˭�����֣�
{
	bool isMissed = true;
	auto instance = GameManager::getInstance();
	auto spriteBullet = Sprite::create("");
	addChild(spriteBullet);

	//bullet���ھ�������
	auto bulletRect = Rect(spriteBullet->getPositionX() + this->getPositionX() - spriteBullet->getContentSize().width / 2,
		spriteBullet->getPositionY() + this->getPositionY() - spriteBullet->getContentSize().height / 2,
		spriteBullet->getContentSize().width,//�Բ����� ��Ҳ��֪��
		spriteBullet->getContentSize().height);//�;����˾Ͳ�������������
	if (this->getMonsterColor() == 1)//red
	{
		auto monsterBlueVector = instance->monsterBlueVector;

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
					monster->death();//��ʧ�� vector�Ƴ���
					GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + monster->getMoney();
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
					GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + monster->getMoney();
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