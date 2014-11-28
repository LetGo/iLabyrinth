/*
 * HelpScene.h
 *
 *  Created on: 2013-7-22
 *      Author: a582o_000
 */

#ifndef HELPSCENE_H_
#define HELPSCENE_H_
#include "cocos2d.h"

class HelpScene :public cocos2d::CCLayer
{
private:
    cocos2d::CCSprite    *_backSprite;
    cocos2d::CCSize      _winSize;
public:
	HelpScene();
	virtual ~HelpScene();
	bool init();
	static cocos2d::CCScene* scene();
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent);
	CREATE_FUNC(HelpScene);
};

#endif /* HELPSCENE_H_ */
