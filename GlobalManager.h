#include "cocos2d.h"

#define GM() GlobalManager::getInstance()

class GlobalManager :public cocos2d::Ref
{
public:
	GlobalManager();
	virtual ~GlobalManager();
	virtual bool init();
	static GlobalManager* getInstance();



};
