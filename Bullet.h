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
	CC_SYNTHESIZE(int, maxForce, MaxForce);//¹¥»÷Á¦
	CC_SYNTHESIZE(int, bulletScope, BulletScope);//¹¥»÷·¶Î§
	CC_SYNTHESIZE(Spawn*, bulletAction, BulletAction);//·ÉÐÐ¶¯»­
	Sprite* sprite;//ÌùÍ¼
	virtual void shoot() {};
	virtual void removeBullet() {};

};

#endif
