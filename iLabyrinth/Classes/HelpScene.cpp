/*
 * HelpScene.cpp
 *
 *  Created on: 2013-7-22
 *      Author: a582o_000
 */

#include "HelpScene.h"
#include "MenuScene.h"
#include "Config.h"
USING_NS_CC;
HelpScene::HelpScene() {
	// TODO Auto-generated constructor stub

}

HelpScene::~HelpScene() {
	// TODO Auto-generated destructor stub
}

CCScene* HelpScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    HelpScene *layer = HelpScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelpScene::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);
	_winSize = CCDirector::sharedDirector()->getWinSize();

    CCSprite* sprite;
    if(Config::sharedConfig()->isIpad()){
    	sprite = CCSprite::create("menu~ipad.png");
    }
    else{
    	sprite = CCSprite::create("menu.png");
    }
	sprite->setAnchorPoint(CCPointZero);
	addChild(sprite);

	CCSpriteBatchNode *backgroundLayer ;
    if(Config::sharedConfig()->isIpad()){
    	 backgroundLayer = CCSpriteBatchNode::create("sprites~ipad.png");
    }
    else{
    	 backgroundLayer = CCSpriteBatchNode::create("sprites.png");
    }
	backgroundLayer->getTexture()->setAliasTexParameters();
	addChild(backgroundLayer);

	_backSprite = CCSprite::createWithSpriteFrameName("back2.png");
	_backSprite->setAnchorPoint(ccp(1,1));
	_backSprite->setPosition(ccp(_winSize.width,_winSize.height));
	backgroundLayer->addChild(_backSprite);

	CCLabelTTF *lable = CCLabelTTF::create(CCString::createWithContentsOfFile("about")->getCString(),
											"Arial",
											Config::sharedConfig()->isIpad()?32:15,
											ccp(_winSize.width-20,_winSize.height),
											kCCTextAlignmentCenter);
	lable->setAnchorPoint(ccp(0.5f,1.0f));
	lable->setPosition(ccp(_winSize.width/2,_winSize.height-70));
	lable->setColor(ccBLACK);
	addChild(lable);
	return true;
}

void HelpScene::ccTouchesEnded(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent)
{
	cocos2d::CCTouch* pTouch = (cocos2d::CCTouch*)(pTouches->anyObject());
	CCPoint touchPoint =this->convertTouchToNodeSpace(pTouch);

	CCSize mySize = _backSprite->getTexture()->getContentSize();
	mySize.width  *= 0.5;
	mySize.height *= 0.5;
	CCRect frame = CCRect(_backSprite->getPositionX() -mySize.width *_backSprite->getAnchorPoint().x, _backSprite->getPositionY() -mySize.height *_backSprite->getAnchorPoint().y, mySize.width, mySize.height);
		if( frame.containsPoint(touchPoint) ){

			_backSprite->setColor(ccGREEN);

			CCDirector::sharedDirector()->replaceScene(CCTransitionSplitRows::create(1.0f,MenuScene::scene()));
			return;
		}
}















