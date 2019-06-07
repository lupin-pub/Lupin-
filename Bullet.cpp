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
	sprite = Sprite::createWithSpriteFrameName("");//子弹图片
	addChild(sprite);
	return true;
}

void Bullet::removeBullet()//攻击！
{
	bool isMissed = true;
	auto instance = GameManager::getInstance();
	//bullet所在矩形区域
	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2,
		                   this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height/ 2,
		                   this->sprite->getContentSize().width,
		                   this->sprite->getContentSize().height);//就矩形了就不用物理引擎了
	auto monsterVector = instance->monsterVector;//啥意思啊

	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterRect = monster->baseSprite->getBoundingBox();
		if (monsterRect.intersectsRect(bulletRect) && monster->getState()!=7)
		{
			auto currHp = monster->getCurrHp();

			currHp = currHp - this->getMaxForce();//受到攻击Hp减少

			if (currHp <= 0)
			{
				currHp = 0;
			}
			monster->setCurrHp(currHp);

			monster->getHpBar()->setPersentage((currHp / monster->getMaxHp()) * 100);//更新Hp
			//monster->getHurt();     Wow!血腥场面！
			isMissed = false;//击中
				if (currHp == 0)
				{
					monster->death();
				}
			break;
		}
	}
	//不管击不击中都消失
	this->removeFromParent();
	/*if (isMissed)
	{
		//若未击中
	}
	else
	{
		this->removeFromParent();
	}*/

}

void Bullet::shoot()
{
	runAction(Sequence::create(bulletAction, CallFuncN::create(CC_CALLBACK_0(Bullet::removeBullet, this)), NULL));//BulletAction沿直线飞行 removeBullet判断击中并子弹消失
}


