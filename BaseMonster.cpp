#include "BaseMonster.h"
#include "SimpleAudioEngine.h"
#include "BaseMap.h"

USING_NS_CC;

BaseMonster::BaseMonster()
	:baseSprite(NULL),//ɶ
	pointCounter(0),//���Ǹ�ɶ
	runSpeed(0)
	, maxHp(0)
	, currHp(0)
	, armor(0)
	, hpPercentage(100)
	, hpBar(NULL)
	, lastState(stateNone)
	//, attackBySoldier(true)//����
	//, attackByTower(true)//Ӧ���ܺϲ�
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
	hpBgSprite = Sprite::createWithSpriteFrameName("");//�ö�����֮ǰ�����ģ������ļ��Ĳ��ǵ���������

	hpBgSprite->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height));
	baseSprite->addChild(hpBgSprite);

	hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName(""));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));//��ʼ�� ���У�
	hpBar->setBarChangeRate(Point(1, 0));//ˮƽ����չ��
	hpBar->setPercentage(hpPercentage);
	hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2));
	hpBgSprite->addChild(hpBar);
}

bool BaseMonster::beAttacked(BaseMonster* attacker)
{
	if (attacker->getMonsterColor() == this->getMonsterColor)
	{
		return false;
	}
	else
		return true;
}