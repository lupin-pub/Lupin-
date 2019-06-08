#include "BaseMonster.h"
#include "SimpleAudioEngine.h"
#include "BaseMap.h"
#include "GameManager.h"

USING_NS_CC;

BaseMonster::BaseMonster()
	:baseSprite(NULL),//啥
	pointCounter(0),//这是个啥
	runSpeed(0)
	, maxHp(0)
	, currHp(0)
	, armor(0)
	, hpPercentage(100)
	, hpBar(NULL)
	, lastState(stateNone)
	//, attackBySoldier(true)//这俩
	//, attackByTower(true)//应该能合并
	, isAttacking(false)
	, isSlowed(false)
	, money(0)
{}

BaseMonster::~BaseMonster()
{}

bool BaseMonster::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}


void BaseMonster::createAndSetHpBar()
{
	hpBgSprite = Sprite::createWithSpriteFrameName("");//好东西！之前见过的！！！哪见的不记得了嘤嘤嘤

	hpBgSprite->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height));
	baseSprite->addChild(hpBgSprite);

	hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName(""));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));//开始点 左中？
	hpBar->setBarChangeRate(Point(1, 0));//水平方向展开
	hpBar->setPercentage(hpPercentage);
	hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2));
	hpBgSprite->addChild(hpBar);
}

/*bool BaseMonster::beAttacked(BaseMonster* attacker)
{
	if (attacker->getMonsterColor() == this->getMonsterColor)
	{
		return false;
	}
	else
		return true;
}
*/

void BaseMonster::checkNearestMonster()
{
	auto instance = GameManager::getInstance();
	if (this->getMonsterColor() == 1)
	{
		auto monsterBlueVector = instance->monsterBlueVector;

		auto currMinDistant = this->scope;


		nearestMonster = NULL;
		for (int i = 0; i < monsterBlueVector.size(); i++)
		{
			auto monster = monsterBlueVector.at(i);
			double distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());

			if (distance < currMinDistant&&monster->getState() != 7)//在塔的范围内且可以被攻击
			{
				currMinDistant = distance;//攻击最近怪物
				monsterTemp = monster;//目前攻击的怪物
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

			if (distance < currMinDistant&&monster->getState() != 7)//在塔的范围内且可以被攻击
			{
				currMinDistant = distance;//攻击最近怪物
				monsterTemp = monster;//目前攻击的怪物
			}
		}
		nearestMonster = monsterTemp;
	}
}