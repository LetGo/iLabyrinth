/*
 * PickMapScene.h
 *
 *  Created on: 2013-7-21
 *      Author: a582o_000
 */

#ifndef PICKMAPSCENE_H_
#define PICKMAPSCENE_H_
#include "cocos2d.h"

class PickMapScene :public cocos2d::CCLayer{
private:
	cocos2d::CCSpriteBatchNode	*backgroundLayer;
	cocos2d::CCSize winSize;
	cocos2d::CCSprite* backSprite;
	cocos2d::CCArray* mapArray;

	cocos2d::CCPoint _touchDownLocation;
	bool _didScroll;
	float _lowestPoint;
public:
	PickMapScene();
	virtual ~PickMapScene();
	bool init();
	static cocos2d::CCScene* scene();
	cocos2d::CCSprite* addBunttonOfMapNo(u_int no,cocos2d::CCPoint pos);
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	CREATE_FUNC(PickMapScene);
};

#endif /* PICKMAPSCENE_H_ */
