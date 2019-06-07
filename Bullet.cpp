#include "Bullet.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"

USING_NS_CC;

bool Bullet::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("");//�ӵ�ͼƬ
	addChild(sprite);
	return true;
}

void Bullet::removeBullet()//������
{
	bool isMissed = true;
	auto instance = GameManager::getInstance();
	//bullet���ھ�������
	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2,
		                   this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height/ 2,
		                   this->sprite->getContentSize().width,
		                   this->sprite->getContentSize().height);//�;����˾Ͳ�������������
	auto monsterVector = instance->monsterVector;//ɶ��˼��

	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterRect = monster->baseSprite->getBoundingBox();
		if (monsterRect.intersectsRect(bulletRect) && monster->getState()!=7)
		{
			auto currHp = monster->getCurrHp();

			currHp = currHp - this->getMaxForce();//�ܵ�����Hp����

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

void Bullet::shoot()
{
	runAction(Sequence::create(bulletAction, CallFuncN::create(CC_CALLBACK_0(Bullet::removeBullet, this)), NULL));//BulletAction��ֱ�߷��� removeBullet�жϻ��в��ӵ���ʧ
}


