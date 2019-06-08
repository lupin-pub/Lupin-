#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"

USING_NS_CC;

class Bullet :public cocos2d::Sprite
{
public:
	Bullet();
	~Bullet();
	virtual bool init();
	CREATE_FUNC(Bullet);
	//int BulletColor;

protected:
	CC_SYNTHESIZE(int, maxForce, MaxForce);//������
	CC_SYNTHESIZE(int, bulletScope, BulletScope);//������Χ
	CC_SYNTHESIZE(Spawn*, bulletAction, BulletAction);//���ж���
	Sprite* sprite;//��ͼ
	virtual void shoot() {};
	virtual void removeBullet() {};

};

#endif
