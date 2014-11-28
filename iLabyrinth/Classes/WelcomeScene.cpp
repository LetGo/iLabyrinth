/*
 * WelcomeScene.cpp
 *
 *  Created on: 2013-7-26
 *      Author: a582o_000
 */

#include "WelcomeScene.h"
#include "Config.h"
#include "MenuScene.h"
USING_NS_CC;
WelcomeScene::WelcomeScene() {
	// TODO Auto-generated constructor stub

}

WelcomeScene::~WelcomeScene() {
	// TODO Auto-generated destructor stub
}

CCScene* WelcomeScene::scene()
{
	CCScene* scene = CCScene::create();
	WelcomeScene* layer = WelcomeScene::create();
	scene->addChild(layer);
	return scene;
}
bool WelcomeScene::init()
{
	if(!CCLayer::init()){
		return false;
	}
	CCSprite* sprite;
	if(Config::sharedConfig()->isIpad()){
		sprite = CCSprite::create("Default@2x.png");
	}else{
		sprite = CCSprite::create("Default.png");
	}
	sprite->setAnchorPoint(CCPointZero);
	sprite->setPosition(CCPointZero);
	addChild(sprite);
	CCFiniteTimeAction* func1 = CCCallFunc::create(this,callfunc_selector(WelcomeScene::initConfig));
	CCFiniteTimeAction* func2 = CCCallFunc::create(this,callfunc_selector(WelcomeScene::callMenuScene));

	this->runAction(CCSequence::create(func1,func2,NULL));
	return true;
}

void WelcomeScene::initConfig()
{
	Config::sharedConfig()->initIsMapCanPlay();
  	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
  	if(Config::sharedConfig()->isIpad()){
  		cache->addSpriteFramesWithFile("sprites~ipad.plist");
  	}else
		cache->addSpriteFramesWithFile("sprites.plist");
}
void WelcomeScene::callMenuScene()
{
	CCScene* scene = MenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(1.0f,scene));
}
