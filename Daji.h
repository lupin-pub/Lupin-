#ifndef _DAJI_H_
#define _DAJI_H_

#include "BaseMonster.h"

class Daji : public BaseMonster
{
public:
	virtual bool init() override;
	static Daji* createMonster(std::vector<Point> points, std::vector<std::vector<std::vector<Point>>> sonPath);
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
