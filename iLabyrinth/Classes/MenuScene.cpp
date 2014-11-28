/*
 * MenuScene.cpp
 *
 *  Created on: 2013-7-21
 *      Author: a582o_000
 */

#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "PickMapScene.h"
#include "HelpScene.h"
#include "Config.h"
#include "jni/JniHelper.h"
using namespace CocosDenshion;
USING_NS_CC;

MenuScene::MenuScene() {
	//CCLog("MenuScene++");

}

MenuScene::~MenuScene()
{
	//CCLog("MenuScene--");
}

cocos2d::CCScene* MenuScene::scene()
{
    CCScene *scene = CCScene::create();

    MenuScene *layer = MenuScene::create();

    scene->addChild(layer);

    return scene;
}

bool MenuScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    setTouchEnabled(true);
    setKeypadEnabled(true);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //add background
    CCSprite* sprite;
    if(Config::sharedConfig()->isIpad()){
    	sprite = CCSprite::create("menu~ipad.png");
    }
    else{
    	sprite = CCSprite::create("menu.png");
    }
    sprite->setAnchorPoint(CCPointZero);
    addChild(sprite);

    if(Config::sharedConfig()->isIpad()){
    	 backgroundLayer = CCSpriteBatchNode::create("sprites~ipad.png");
    }
    else{
    	 backgroundLayer = CCSpriteBatchNode::create("sprites.png");
    }

    backgroundLayer->getTexture()->setAliasTexParameters();//设置无锯齿
    addChild(backgroundLayer);

    //add play btn
    CCSprite* playSprite = CCSprite::createWithSpriteFrameName("play.png");
    playSprite->setAnchorPoint(ccp(0.5f,0.0f));
    playSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
    playSprite->setTag(MenuButtonPlay);
    backgroundLayer->addChild(playSprite);

    //add help btn
    CCSprite* helpSprite = CCSprite::createWithSpriteFrameName("help.png");
    helpSprite->setAnchorPoint(ccp(0.5f,1.0f));
    helpSprite->setPosition(ccp(winSize.width/2,winSize.height/2-helpSprite->boundingBox().size.height/2));
	helpSprite->setTag(MenuButtonHlep);
	backgroundLayer->addChild(helpSprite);

    return true;
}

void MenuScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if(!pTouches||!pTouches->count())
	{
	    return;
	}
	cocos2d::CCTouch* pTouch = (cocos2d::CCTouch*)(pTouches->anyObject());
	CCPoint touchPoint = backgroundLayer->convertTouchToNodeSpace(pTouch);
	CCObject * object;
	CCARRAY_FOREACH(backgroundLayer->getDescendants(),object)
	{
		CCSprite* menuSprite = dynamic_cast<CCSprite*>(object);
		CCScene* scene = NULL;
		if(menuSprite->boundingBox().containsPoint(touchPoint))
		{
			menuSprite->setColor(ccGREEN);
		//	SimpleAudioEngine::sharedEngine()->playEffect("click.caf");
			switch(menuSprite->getTag())
			{
				case MenuButtonPlay:
					scene = PickMapScene::scene();
					break;
				case MenuButtonHlep:
					scene = HelpScene::scene();
					break;
			}
		}
		if(scene != NULL)
		{
			CCDirector::sharedDirector()->replaceScene(CCTransitionSplitRows::create(1.0f,scene));
			return ;
		}

	}
}

void MenuScene::keyBackClicked()
{
	JniMethodInfo jmi;
    if(JniHelper::getMethodInfo(jmi , "com/uestc/game/iLabyrinth" , "end" , "([Ljava/lang/String;)V"))
    {
        jmi.env->CallStaticVoidMethod(jmi.classID , jmi.methodID , NULL);
    }

	CCDirector::sharedDirector()->end();
}


