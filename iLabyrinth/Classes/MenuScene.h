/*
 * MenuScene.h
 *
 *  Created on: 2013-7-21
 *      Author: a582o_000
 */

#ifndef MENUSCENE_H_
#define MENUSCENE_H_
#include "cocos2d.h"

typedef enum
{
	MenuButtonPlay =1,
	MenuButtonHlep,
	MenuButtonPlayHeaven,
}MenuButtton;

class MenuScene :public cocos2d::CCLayer
{
private:
	cocos2d::CCSpriteBatchNode	*backgroundLayer;
public:
	MenuScene();
	virtual ~MenuScene();
	bool init();
	static cocos2d::CCScene* scene();
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void keyBackClicked();
	CREATE_FUNC(MenuScene);
};

#endif /* MENUSCENE_H_ */
