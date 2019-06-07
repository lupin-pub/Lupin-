#include "CatSprite.h"
#include "HelloWorldScene.h"//��hello�Ǳ�hello
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

CatSprite::CatSprite() :
	_numBones(0),
	_facingForwardAnimation(nullptr),
	_facingBackAnimation(nullptr),
	_facingLeftAnimation(nullptr),
	_facingRightAnimation(nullptr),
	_curAnimation(nullptr),
	_curAnimate(nullptr)
{
}

CatSprite::~CatSprite()
{
	CC_SAFE_RELEASE_NULL(_facingForwardAnimation);
	CC_SAFE_RELEASE_NULL(_facingBackAnimation);
	CC_SAFE_RELEASE_NULL(_facingLeftAnimation);
	CC_SAFE_RELEASE_NULL(_facingRightAnimation);
}

CatSprite *CatSprite::createWithLayer(HelloWorld *layer)
{
	CatSprite *pRet = new CatSprite();
	if (pRet && pRet->initWithLayer(layer))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}

bool CatSprite::initWithLayer(HelloWorld *layer)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!this->initWithSpriteFrameName("cat_forward_1.png"));

		_layer = layer;

		_facingForwardAnimation = this->createCatAnimation("forward");
		_facingForwardAnimation->retain();
		_facingBackAnimation = this->createCatAnimation("back");
		_facingBackAnimation->retain();
		_facingLeftAnimation = this->createCatAnimation("left");
		_facingLeftAnimation->retain();
		_facingRightAnimation = this->createCatAnimation("right");
		_facingRightAnimation->retain();

		bRet = true;
	} while (0);

	return bRet;
}

void CatSprite::moveToward(const Point &target)
{
	this->stopActionByTag(1);

	Point fromTileCoord = _layer->tileCoordForPosition(this->getPosition());
	Point toTileCoord = _layer->tileCoordForPosition(target);

	if (fromTileCoord == toTileCoord)
	{
		CCLOG("You're already there! :P");
		return;
	}

	if (!_layer->isValidTileCoord(toTileCoord) || _layer->isWallAtTileCoord(toTileCoord))
	{
		SimpleAudioEngine::getInstance()->playEffect("hitWall.wav");
		return;
	}

	CCLOG("From: %f, %f", fromTileCoord.x, fromTileCoord.y);
	CCLOG("To: %f, %f", toTileCoord.x, toTileCoord.y);

	//bool pathFound = false;
	_spOpenSteps.clear();
	_spClosedSteps.clear();

	// ���ȣ����è�ķ������굽open�б�
	this->insertInOpenSteps(ShortestPathStep::createWithPosition(fromTileCoord));

	do
	{
		// �õ���С��Fֵ����
		// ��Ϊ�������б���һ������������С��Fֵ
		ShortestPathStep *currentStep = _spOpenSteps.at(0);

		// ��ӵ�ǰ���赽closed�б�
		_spClosedSteps.pushBack(currentStep);

		// ������open�б������Ƴ�
		// ��Ҫע����ǣ������Ҫ�ȴ�open�б������Ƴ���ӦС�Ķ�����ڴ�
		_spOpenSteps.erase(0);

		// �����ǰ������Ŀ�귽�����꣬��ô�������
		if (currentStep->getPosition() == toTileCoord)
		{
			//pathFound = true;
			this->constructPathAndStartAnimationFromStep(currentStep);
			//ShortestPathStep *tmpStep = currentStep;
			//CCLOG("PATH FOUND :");
			//do
			//{
			//    CCLOG("%s", tmpStep->getDescription().c_str());
			//    tmpStep = tmpStep->getParent(); // ����
			//} while (tmpStep);                  // ֱ��û����һ��

			_spOpenSteps.clear();
			_spClosedSteps.clear();
			break;
		}

		// �õ���ǰ��������ڷ�������
		PointArray *adjSteps = _layer->walkableAdjacentTilesCoordForTileCoord(currentStep->getPosition());
		for (ssize_t i = 0; i < adjSteps->count(); ++i)
		{
			ShortestPathStep *step = ShortestPathStep::createWithPosition(adjSteps->getControlPointAtIndex(i));

			// ��鲽���ǲ����Ѿ���closed�б�
			if (this->getStepIndex(_spClosedSteps, step) != -1)
			{
				continue;
			}

			// ����ӵ�ǰ���赽�˲���ĳɱ�
			int moveCost = this->costToMoveFromStepToAdjacentStep(currentStep, step);

			// ���˲����Ƿ��Ѿ���open�б�
			ssize_t index = this->getStepIndex(_spOpenSteps, step);

			// ����open�б������
			if (index == -1)
			{
				// ���õ�ǰ������Ϊ��һ������
				step->setParent(currentStep);

				// Gֵ��ͬ����һ����Gֵ + ����һ��������ĳɱ�
				step->setGScore(currentStep->getGScore() + moveCost);

				// Hֵ���ǴӴ˲��赽Ŀ�귽��������ƶ�������ֵ
				step->setHScore(this->computeHScoreFromCoordToCoord(step->getPosition(), toTileCoord));

				// ������ӵ�open�б�
				this->insertInOpenSteps(step);
			}
			else
			{
				// ��ȡ�ɵĲ��裬��ֵ�Ѿ������
				step = _spOpenSteps.at(index);

				// ���Gֵ�Ƿ���ڵ�ǰ���赽�˲����ֵ
				if ((currentStep->getGScore() + moveCost) < step->getGScore())
				{
					// Gֵ��ͬ����һ����Gֵ + ����һ��������ĳɱ�
					step->setGScore(currentStep->getGScore() + moveCost);

					// ��ΪGֵ�ı��ˣ�FֵҲ����Ÿı�
					// ����Ϊ�˱���open�б�������Ҫ���˲����Ƴ��������°������

					// ���Ƴ�֮ǰ����Ҫ�ȱ�������
					step->retain();

					// ���ڿ��Է����Ƴ������õ��ı��ͷ�
					_spOpenSteps.erase(index);

					// ���°������
					this->insertInOpenSteps(step);

					// ���ڿ����ͷ����ˣ���Ϊopen�б�Ӧ�ó�����
					step->release();
				}
			}
		}
	} while (_spOpenSteps.size() > 0);

	//if (!pathFound)
	if (_shortestPath.empty())
	{
		SimpleAudioEngine::getInstance()->playEffect("hitWall.wav");
	}
}

Animation *CatSprite::createCatAnimation(const char *animType)
{
	Animation *animation = Animation::create();
	for (int i = 1; i <= 2; ++i)
	{
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("cat_%s_%d.png", animType, i)));
	}
	animation->setDelayPerUnit(0.2f);
	return animation;
}

void CatSprite::runAnimation(Animation *animation)
{
	if (_curAnimation == animation)
	{
		return;
	}

	_curAnimation = animation;
	if (_curAnimate != nullptr)
	{
		this->stopAction(_curAnimate);
	}

	_curAnimate = RepeatForever::create(Animate::create(animation));
	this->runAction(_curAnimate);
}

void CatSprite::insertInOpenSteps(CatSprite::ShortestPathStep *step)
{
	int stepFScore = step->getFScore();
	ssize_t count = _spOpenSteps.size();
	ssize_t i = 0;
	for (; i < count; ++i)
	{
		if (stepFScore <= _spOpenSteps.at(i)->getFScore())
		{
			break;
		}
	}
	_spOpenSteps.insert(i, step);
}

int CatSprite::computeHScoreFromCoordToCoord(const Point &fromCoord, const Point &toCoord)
{
	// ����ʹ�������ٷ���������ӵ�ǰ���赽��Ŀ�경�裬��ˮƽ�ʹ�ֱ�����ܵĲ���
	// �����˿�����·�ϵĸ����ϰ�
	return abs(toCoord.x - fromCoord.x) + abs(toCoord.y - fromCoord.y);
}

int CatSprite::costToMoveFromStepToAdjacentStep(const ShortestPathStep *fromStep, const ShortestPathStep *toStep)
{
	return ((fromStep->getPosition().x != toStep->getPosition().x)
		&& (fromStep->getPosition().y != toStep->getPosition().y)) ? 14 : 10;
}

ssize_t CatSprite::getStepIndex(const cocos2d::Vector<CatSprite::ShortestPathStep *> &steps, const CatSprite::ShortestPathStep *step)
{
	for (ssize_t i = 0; i < steps.size(); ++i)
	{
		if (steps.at(i)->isEqual(step))
		{
			return i;
		}
	}
	return -1;
}

void CatSprite::constructPathAndStartAnimationFromStep(CatSprite::ShortestPathStep *step)
{
	_shortestPath.clear();

	do
	{
		// ��ʼλ�ò�Ҫ�������
		if (step->getParent())
		{
			// ���ǲ��뵽����0��λ�ã��Ա㷴ת·��
			_shortestPath.insert(0, step);
		}
		step = step->getParent();   // ����
	} while (step);                 // ֱ��û����һ��

	for (const ShortestPathStep *s : _shortestPath)
	{
		CCLOG("%s", s->getDescription().c_str());
	}

	this->popStepAndAnimate();
}

void CatSprite::popStepAndAnimate()
{
	Point currentPosition = _layer->tileCoordForPosition(this->getPosition());

	if (_layer->isBoneAtTilecoord(currentPosition))
	{
		SimpleAudioEngine::getInstance()->playEffect("pickup.wav");
		_numBones++;
		_layer->showNumBones(_numBones);
		_layer->removeObjectAtTileCoord(currentPosition);
	}
	else if (_layer->isDogAtTilecoord(currentPosition))
	{
		if (_numBones == 0)
		{
			_layer->loseGame();
			return;
		}
		else
		{
			_numBones--;
			_layer->showNumBones(_numBones);
			_layer->removeObjectAtTileCoord(currentPosition);
			SimpleAudioEngine::getInstance()->playEffect("catAttack.wav");
		}
	}
	else if (_layer->isExitAtTilecoord(currentPosition))
	{
		_layer->winGame();
		return;
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect("step.wav");
	}

	// ����Ƿ�����·��������Ҫǰ��
	if (_shortestPath.size() == 0)
	{
		return;
	}

	// �õ���һ���ƶ��Ĳ���
	ShortestPathStep *s = _shortestPath.at(0);

	Point futurePosition = s->getPosition();
	Point diff = futurePosition - currentPosition;
	if (abs(diff.x) > abs(diff.y))
	{
		if (diff.x > 0)
		{
			this->runAnimation(_facingRightAnimation);
		}
		else
		{
			this->runAnimation(_facingLeftAnimation);
		}
	}
	else
	{
		if (diff.y > 0)
		{
			this->runAnimation(_facingForwardAnimation);
		}
		else
		{
			this->runAnimation(_facingBackAnimation);
		}
	}

	// ׼�������ͻص�
	MoveTo *moveAction = MoveTo::create(0.4f, _layer->positionForTileCoord(s->getPosition()));
	CallFunc *moveCallback = CallFunc::create(CC_CALLBACK_0(CatSprite::popStepAndAnimate, this));

	// �Ƴ�����
	_shortestPath.erase(0);

	// ���ж���
	Sequence *moveSequence = Sequence::create(moveAction, moveCallback, nullptr);
	moveSequence->setTag(1);
	this->runAction(moveSequence);
}

CatSprite::ShortestPathStep::ShortestPathStep() :
	_position(Point::ZERO),
	_gScore(0),
	_hScore(0),
	_parent(nullptr)
{
}

CatSprite::ShortestPathStep::~ShortestPathStep()
{
}

CatSprite::ShortestPathStep *CatSprite::ShortestPathStep::createWithPosition(const Point &pos)
{
	ShortestPathStep *pRet = new ShortestPathStep();
	if (pRet && pRet->initWithPosition(pos))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}

bool CatSprite::ShortestPathStep::initWithPosition(const Point &pos)
{
	bool bRet = false;
	do
	{
		this->setPosition(pos);

		bRet = true;
	} while (0);

	return bRet;
}

int CatSprite::ShortestPathStep::getFScore() const
{
	return this->getGScore() + this->getHScore();
}

bool CatSprite::ShortestPathStep::isEqual(const CatSprite::ShortestPathStep *other) const
{
	return this->getPosition() == other->getPosition();
}

std::string CatSprite::ShortestPathStep::getDescription() const
{
	return StringUtils::format("pos=[%.0f;%.0f]  g=%d  h=%d  f=%d",
		this->getPosition().x, this->getPosition().y,
		this->getGScore(), this->getHScore(), this->getFScore());
}
