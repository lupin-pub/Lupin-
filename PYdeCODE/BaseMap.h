#ifndef __BASE_MAP_H__
#define __BASE_MAP_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class BaseMap :public cocos2d::Layer
{
public:
	CREATE_FUNC(BaseMap);
	//绑定其他的层？

protected:
	std::vector<std::vector<Vector<GroupMonster*>>> waveVector;//存储每一波敌人信息容器
	std::vector<std::vector<std::vector<Point>>> path;//敌人路线
	virtual void addWaves(float dt);
	virtual void addMonsters(float dt);
	void initMap();//初始化地图
	virtual void onExitTransitionDidStart();
	virtual void onExit() {};
};

class GroupMonster :public cocos2d::Node
{
public:
	static GroupMonster* initGroupEnemy(int type/*,int road*/);
	CREATE_FUNC(GroupMonster);//保存怪物类型
};

#endif