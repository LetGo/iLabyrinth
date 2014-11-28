/*
 * WelcomeScene.h
 *
 *  Created on: 2013-7-26
 *      Author: a582o_000
 */

#ifndef WELCOMESCENE_H_
#define WELCOMESCENE_H_
#include "cocos2d.h"

class WelcomeScene :public cocos2d::CCLayer
{
public:
	WelcomeScene();
	virtual ~WelcomeScene();
	static cocos2d::CCScene* scene();
	bool init();
	CREATE_FUNC(WelcomeScene);

	void initConfig();
	void callMenuScene();
};

#endif /* WELCOMESCENE_H_ */
