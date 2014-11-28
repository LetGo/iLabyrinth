/*
 * PickMapScene.cpp
 *
 *  Created on: 2013-7-21
 *      Author: a582o_000
 */

#include "PickMapScene.h"
#include "Config.h"
#include "MenuScene.h"
#include "GameScene.h"
USING_NS_CC;

PickMapScene::PickMapScene() {
	//CCLog("PickMapScene++");
}

PickMapScene::~PickMapScene() {
	//CCLog("PickMapScene--");
	CC_SAFE_RELEASE(mapArray);
}

CCScene* PickMapScene::scene()
{
    CCScene *scene = CCScene::create();

    PickMapScene *layer = PickMapScene::create();

    scene->addChild(layer);

    return scene;
}

bool PickMapScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    mapArray = CCArray::create();
    mapArray->retain();



    setTouchEnabled(true);

    this->setPosition(ccp(this->getPositionX(),Config::sharedConfig()->getscrollOffset()));
    winSize = CCDirector::sharedDirector()->getWinSize();

    //Add background
    if(Config::sharedConfig()->isIpad()){
    	 backgroundLayer = CCSpriteBatchNode::create("sprites~ipad.png");

    }else{
    	backgroundLayer = CCSpriteBatchNode::create("sprites.png");
    }
    backgroundLayer->getTexture()->setAliasTexParameters();
    addChild(backgroundLayer);

    {
     	CCSprite* sand1 = CCSprite::createWithSpriteFrameName("sand.png");
     	sand1->setAnchorPoint(CCPointZero);
     	sand1->setPosition(CCPointZero);
     	backgroundLayer->addChild(sand1);

		CCSprite* sand2 = CCSprite::createWithSpriteFrameName("sand.png");
		sand2->setAnchorPoint(CCPointZero);
		sand2->setPosition(ccp(0,-sand1->boundingBox().size.height+1));
		backgroundLayer->addChild(sand2);

		CCSprite* sand3 = CCSprite::createWithSpriteFrameName("sand.png");
		sand3->setAnchorPoint(CCPointZero);
		sand3->setPosition(ccp(0,sand2->boundingBox().origin.y-sand2->boundingBox().size.height));
		backgroundLayer->addChild(sand3);
     }
     backSprite = CCSprite::createWithSpriteFrameName("back2.png");
     backSprite->setAnchorPoint(ccp(1,1));
     backSprite->setPosition(ccp(winSize.width, winSize.height));
     backgroundLayer->addChild(backSprite);

     float top = 0;

     {
     	float left = 0;
     	for(u_int no =1;no<=4;no++)
     	{
			CCSprite* map = this->addBunttonOfMapNo(no,CCPointZero);
			if(!left)
				left = map->boundingBox().size.width;
			if(!top)
				top = winSize.height -map->boundingBox().size.height *0.8f;
			map->setPosition(ccp(left,top));

			CCSprite* feets = CCSprite::createWithSpriteFrameName("pedos.png");
			feets->setRotation(90);
			feets->setPosition(ccp(map->getPositionX()+map->boundingBox().size.width/2+feets->boundingBox().size.width/1.6f,map->getPositionY()));
			//this->addChild(feets);
			backgroundLayer->addChild(feets);
			left += map->boundingBox().size.width +feets->boundingBox().size.width *1.4f;

			if( no == 4 )
			{
				feets->setPosition(ccp(feets->getPositionX(), feets->getPositionY() -map->boundingBox().size.height /2));
				feets->setRotation(150);
				top -= map->boundingBox().size.height *1.2f;
			}
     	}
     }


     {
    	 float left = 0;
    	 for(u_int no =5; no<=9;no++)
    	 {
    		 CCSprite* map = this->addBunttonOfMapNo(14-no,CCPointZero);
    		 if(!left)
    			 left = map->boundingBox().size.width/2;
    		 map->setPosition(ccp(left,top));

    		 CCSprite* feets = CCSprite::createWithSpriteFrameName("pedos.png");
    		 feets->setRotation(90*3);
    		 feets->setPosition(ccp(map->getPositionX()-map->boundingBox().size.width/2-feets->boundingBox().size.width/1.6f,map->getPositionY()));
    		 //this->addChild(feets);
    		 backgroundLayer->addChild(feets);
    		 left += map->boundingBox().size.width+feets->boundingBox().size.width*1.4f;

    		 if(5 == no)
    		 {
    			 feets->setPosition(ccp(map->getPositionX(),map->getPositionY()-map->boundingBox().size.height/1.3f));
    			 feets->setRotation(90*2);
    		 }else if(9 == no)
    		 {
    			 top -= map->boundingBox().size.height*1.5f;
    		 }
    	 }
     }

     {
    	 float left = 0;
    	 for(u_int no=10;no<=14;no++)
    	 {
    		 CCSprite* map = this->addBunttonOfMapNo(no,CCPointZero);
    		 if(!left)
    			 left = map->boundingBox().size.width/2;
    		 map->setPosition(ccp(left,top));

    		 CCSprite* feets = CCSprite::createWithSpriteFrameName("pedos.png");
    		 feets->setRotation(90);
    		 feets->setPosition(ccp(map->getPositionX()+map->boundingBox().size.width/2+feets->boundingBox().size.width/1.6f,map->getPositionY()));
    		// this->addChild(feets);
    		 backgroundLayer->addChild(feets);
    		 left += map->boundingBox().size.width+feets->boundingBox().size.width*1.4f;
    		 if(no == 14 )
    		 {
    			 feets->setPosition(ccp(map->getPositionX(),map->getPositionY()-map->boundingBox().size.height/1.3f));
    			 feets->setRotation(90*2);

    			 top -= map->boundingBox().size.height*1.5f;
    		 }
    	 }

     }


     {
    	 float left = 0;
    	 for(u_int no=15;no<=19;no++)
    	 {
    		 CCSprite* map = this->addBunttonOfMapNo(34-no,CCPointZero);
    		 if(!left)
    			 left = map->boundingBox().size.width/2;

    		 map->setPosition(ccp(left,top));

    		 CCSprite* feets = CCSprite::createWithSpriteFrameName("pedos.png");
    		 feets->setRotation(90*3);
    		 feets->setPosition(ccp(map->getPositionX()-map->boundingBox().size.width/2-feets->boundingBox().size.width/1.6f,map->getPositionY()));
    		 //this->addChild(feets);
    		 backgroundLayer->addChild(feets);

    		 left += map->boundingBox().size.width+feets->boundingBox().size.width*1.4f;

    		 if(15 == no)
    		 {
    			 feets->setPosition(ccp(map->getPositionX(),map->getPositionY()-map->boundingBox().size.height/1.3f));
    			 feets->setRotation(90*2);
    		 }else if(19 == no)
    		 {
    			 top -= map->boundingBox().size.height*1.5f;
    		 }

    	 }

     }

     {
    	 float left = 0;
    	 for(u_int no=20;no<=24;no++)
    	 {
    		 CCSprite* map = this->addBunttonOfMapNo(no,CCPointZero);
    		 if(!left)
    			 left = map->boundingBox().size.width/2;
    		 map->setPosition(ccp(left,top));

    		 CCSprite* feets = CCSprite::createWithSpriteFrameName("pedos.png");
    		 feets->setRotation(90);
    		 feets->setPosition(ccp(map->getPositionX()+map->boundingBox().size.width/2+feets->boundingBox().size.width/1.6f,map->getPositionY()));
    		 //this->addChild(feets);
    		 backgroundLayer->addChild(feets);

    		 left += map->boundingBox().size.width+feets->boundingBox().size.width*1.4f;

    		 if(no == 24 )
    		 {
    			 feets->setPosition(ccp(map->getPositionX(),map->getPositionY()-map->boundingBox().size.height/1.3f));
    			 feets->setRotation(90*2);

    			 top -= map->boundingBox().size.height*1.5f;
    		 }
    	 }

     }

     {
     	 float left = 0;
     	 for(u_int no=25;no<=29;no++)
     	 {
     		 CCSprite* map = this->addBunttonOfMapNo(54-no,CCPointZero);
     		 if(!left)
     			 left = map->boundingBox().size.width/2;

     		 map->setPosition(ccp(left,top));

     		 CCSprite* feets = CCSprite::createWithSpriteFrameName("pedos.png");
     		 feets->setRotation(90*3);
     		 feets->setPosition(ccp(map->getPositionX()-map->boundingBox().size.width/2-feets->boundingBox().size.width/1.6f,map->getPositionY()));
     		 //this->addChild(feets);
     		backgroundLayer->addChild(feets);

     		 left += map->boundingBox().size.width+feets->boundingBox().size.width*1.4f;

     		 if(25 == no)
     		 {
     			 feets->setPosition(ccp(map->getPositionX(),map->getPositionY()-map->boundingBox().size.height/1.3f));
     			 feets->setRotation(90*2);
     		 }else if(29 == no)
     		 {
     			 top -= map->boundingBox().size.height*1.5f;
     		 }

     	 }

      }


     {
    	 float left = 0;
    	 for(u_int no=30;no<=34;no++)
    	 {
    		 CCSprite* map = this->addBunttonOfMapNo(no,CCPointZero);
    		 if(!left)
    			 left = map->boundingBox().size.width/2;
    		 map->setPosition(ccp(left,top));

    		 CCSprite* feets = CCSprite::createWithSpriteFrameName("pedos.png");
    		 feets->setRotation(90);
    		 feets->setPosition(ccp(map->getPositionX()+map->boundingBox().size.width/2+feets->boundingBox().size.width/1.6f,map->getPositionY()));
    		 //this->addChild(feets);
    		 backgroundLayer->addChild(feets);

    		 left += map->boundingBox().size.width+feets->boundingBox().size.width*1.4f;

    		 if(no == 34 )
    		 {
    			 feets->setPosition(ccp(map->getPositionX(),map->getPositionY()-map->boundingBox().size.height/1.3f));
    			 feets->setRotation(90*2);

    			 top -= map->boundingBox().size.height*1.5f;
    		 }
    	 }

     }

     {
     	 float left = 0;
     	 for(u_int no=35;no<=39;no++)
     	 {
     		 CCSprite* map = this->addBunttonOfMapNo(74-no,CCPointZero);
     		 if(!left)
     			 left = map->boundingBox().size.width/2;

     		 map->setPosition(ccp(left,top));

     		 CCSprite* feets = CCSprite::createWithSpriteFrameName("pedos.png");
     		 feets->setRotation(90*3);
     		 feets->setPosition(ccp(map->getPositionX()-map->boundingBox().size.width/2-feets->boundingBox().size.width/1.6f,map->getPositionY()));
     		 //this->addChild(feets);
     		backgroundLayer->addChild(feets);

     		 left += map->boundingBox().size.width+feets->boundingBox().size.width*1.4f;

     		 if(35 == no)
     		 {
     			 feets->setVisible(false);
     			 //feets->setPosition(ccp(map->getPositionX(),map->getPositionY()-map->boundingBox().size.height/1.3f));
     			 //feets->setRotation(90*2);
     		 }else if(39 == no)
     		 {
     			 //top -= map->boundingBox().size.height*1.5f;
     		 }

     	 }

      }

     // Calculate where last map button placed
     _lowestPoint = top;
     CCObject* object;
     CCARRAY_FOREACH(this->getChildren(),object)
     {
    	 CCNode* node = dynamic_cast<CCNode*>(object);
    	 if(node->isEqual(backgroundLayer))
    		 continue;
    	 _lowestPoint = MIN(_lowestPoint,node->boundingBox().origin.y);
     }
     _lowestPoint = abs((int)(_lowestPoint-20));
    return true;
}

CCSprite* PickMapScene::addBunttonOfMapNo(u_int no,CCPoint pos)
{
	CCSprite* map = NULL;
	CCSprite* lockSprite = NULL;
	CCLabelTTF* mapNo = NULL;

	if(Config::sharedConfig()->canPlayMap(no))
	{
		map = CCSprite::createWithSpriteFrameName("map.png");
		map->setTag(no);
		mapNo = CCLabelTTF::create(CCString::createWithFormat("%u",no)->getCString(),"MarkerFelt-Thin",Config::sharedConfig()->isIpad()?42:22);
		mapNo->setColor(ccc3(91,90,51));
		mapNo->setPosition(ccp(map->boundingBox().size.width/2,map->boundingBox().size.height/2));
		map->addChild(mapNo);
	}else
	{
		map = CCSprite::createWithSpriteFrameName("map_locked.png");
		lockSprite = CCSprite::createWithSpriteFrameName("lock.png");
		lockSprite->setPosition(ccp(map->boundingBox().size.width/2,map->boundingBox().size.height/2));
		map->addChild(lockSprite);
	}

	if( Config::sharedConfig()->isIpad())
	{
		 map->setScale(0.9f);
	}
	map->setPosition(pos);
	this->addChild(map);
	mapArray->addObject(map);
	return map;
}

void PickMapScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	_didScroll = false;
	cocos2d::CCTouch* pTouch = (cocos2d::CCTouch*)(pTouches->anyObject());
	_touchDownLocation =  backgroundLayer->convertTouchToNodeSpace(pTouch);
}

void PickMapScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

	if(pTouches->count() == 1)
	{
		CCTouch* touch = (cocos2d::CCTouch*)(pTouches->anyObject());

		CCPoint touchUpLocation = this->convertTouchToNodeSpace(touch);

		if(_didScroll == false && ccpDistance(_touchDownLocation,touchUpLocation)<20)
			return ;

		CCPoint touchLocation = touch->getLocationInView();
		CCPoint prevLocation = touch->getPreviousLocationInView();

		touchLocation = this->convertToNodeSpace(touchLocation);
		prevLocation  = this->convertToNodeSpace(prevLocation);

		touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation);
		prevLocation  = CCDirector::sharedDirector()->convertToGL( prevLocation);


		CCPoint newPos = ccpAdd(this->getPosition(),ccpSub(touchLocation, prevLocation));

		if(newPos.y<0)
			newPos.y = 0;
		if(newPos.y>_lowestPoint)
			newPos.y = _lowestPoint;

		if(this->getPositionY() != newPos.y )
		{
			newPos.x = this->getPositionX();

			this->setPosition(newPos);
			_didScroll = true;
			Config::sharedConfig()->setscrollOffset(newPos.y);
		}
	}
}
void PickMapScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if(_didScroll)
		return;
	CCTouch* touch = (cocos2d::CCTouch*)(pTouches->anyObject());
	CCPoint touchPoint = this->convertTouchToNodeSpace(touch);

	CCObject * object = NULL;
	CCLog("TTT GGG%d",mapArray->count());
	CCARRAY_FOREACH(mapArray,object)
	{
		CCSprite* sprite = dynamic_cast<CCSprite*>(object);

		if( sprite->getTag() <= 0 || sprite->isVisible() == false ) continue;
		if(sprite->boundingBox().containsPoint(touchPoint))
		{
			sprite->setColor(ccGREEN);
		//	CCLog("TTT GGG%d",sprite->getTag());
			CCDirector::sharedDirector()->replaceScene(CCTransitionSplitRows::create(1.0f,GameScene::createWithMap(sprite->getTag())));
			return;
		}

	}

	if(backSprite->boundingBox().containsPoint(touchPoint))
	{
		backSprite->setColor(ccGREEN);
		CCDirector::sharedDirector()->replaceScene(CCTransitionSplitRows::create(1.0f,MenuScene::scene()));
		return ;
	}
}
