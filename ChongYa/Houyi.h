#ifndef _HOUYI_H_
#define _HOUYI_H_

#include "BaseMonster.h"

class Houyi : public BaseMonster
{
public:
	virtual bool init() override;
	static Houyi* createMonster(std::vector<Point> points, std::vector<std::vector<std::vector<Point>>> sonPath);
	void getHurt();
	void death();
	void explosion();
	void beforeSkill(float dt);
	void skill();
	void afterSkill();
	std::vector<std::vector<std::vector<Point>>> sonPath;
	void addSons();
	Sprite* cloud;
	void frozen();
	Point location;
	void changePositionLeft();
	void changePositionRight();
	int skillTag;
};

#endif
