#ifndef __BASE_MAP_H__
#define __BASE_MAP_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class BaseMap :public cocos2d::Layer
{
public:
	CREATE_FUNC(BaseMap);
	//�������Ĳ㣿

protected:
	std::vector<std::vector<Vector<GroupMonster*>>> waveVector;//�洢ÿһ��������Ϣ����
	std::vector<std::vector<std::vector<Point>>> path;//����·��
	virtual void addWaves(float dt);
	virtual void addMonsters(float dt);
	void initMap();//��ʼ����ͼ
	virtual void onExitTransitionDidStart();
	virtual void onExit() {};
};

class GroupMonster :public cocos2d::Node
{
public:
	static GroupMonster* initGroupEnemy(int type/*,int road*/);
	CREATE_FUNC(GroupMonster);//�����������
};

#endif