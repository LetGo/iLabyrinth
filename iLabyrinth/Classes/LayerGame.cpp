/*
 * LayerGame.cpp
 *
 *  Created on: 2013-7-21
 *      Author: a582o_000
 */

#include "LayerGame.h"
#include "Config.h"
#include "PickMapScene.h"
#include "wchar.h"
USING_NS_CC;

LayerGame::LayerGame() {
	CCLog("LayerGame++");

}

LayerGame::~LayerGame() {
	CCLog("LayerGame--");
	CC_SAFE_RELEASE(_mapTiles);
}

bool LayerGame::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);
	//setTouchMode(kCCTouchesOneByOne);

	_winSize = CCDirector::sharedDirector()->getWinSize();
	_mapTiles =CCDictionary::create();
	_mapTiles->retain();
	if(Config::sharedConfig()->isIpad()){
		_backgroundLayer = CCSpriteBatchNode::create("sprites~ipad.png");
	}else{
		_backgroundLayer = CCSpriteBatchNode::create("sprites.png");
	}

	_backgroundLayer->getTexture()->setAliasTexParameters();
	addChild(_backgroundLayer);

	_backSprite = CCSprite::createWithSpriteFrameName("back.png");
	_backSprite->setAnchorPoint(ccp(0,0));
	_backSprite->setPosition(ccp(Config::sharedConfig()->isIpad()?_winSize.width-85:_winSize.width-42,Config::sharedConfig()->isIpad()?15:10));
	_backgroundLayer->addChild(_backSprite,10);


	return true;
}

void LayerGame::loadMapNo(u_int mapNo)
{
	//Reset
	_mapTiles->removeAllObjects();
	for(u_int y=0;y<100;y++)
	{
		for(u_int x=0;x<100;x++)
		{
			for(u_int s=0;s<4;s++)
			{
				_map[x][y][s] = Config::WalkPathNoPath;
			}
		}
	}

	//Load
	_mapNo =mapNo;

	//Add bacaground
	CCSprite* sprite = CCSprite::createWithSpriteFrameName("sand.png");
	sprite->setAnchorPoint(CCPointZero);
	sprite->setPosition(ccp(0,0));
	_backgroundLayer->addChild(sprite);

	//Add character
	_char = Character::create();
	_backgroundLayer->addChild(_char,10);

	//Add title
	char mapStr[50] = {0};

	sprintf(mapStr, "map%02d.plist",mapNo);

	string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(mapStr);
	CCDictionary* dict = CCDictionary::createWithContentsOfFile(path.c_str());

	u_int width;
	u_int height = dict->count();
	for(u_int tr=0;tr<height;tr++)
	{
		char trStr[50] = {0};
		sprintf(trStr, "tr%u",tr);
		CCDictionary* trdata = (CCDictionary*)dict->objectForKey(trStr);

		width = trdata->count();
		for(u_int td=0;td<width;td++)
		{
			char tdStr[50] = {0};
			sprintf(tdStr, "td%u",td);
			CCString* tdString =(CCString*)trdata->objectForKey(tdStr);
			CCArray* array = CCArray::create();
			string s = tdString->getCString();
			vector<string> vec;
		    StringSplit(s,'|',vec);
		    for(int i=0;i<(int)vec.size();i++)
		    {
		    	CCString* s = CCString::create(vec[i]);
		    	array->addObject(s);

		    }
			this->addTiledWithData(array,td,tr);
		}

	}

    // Update oriantations for "Special" tiles
	this->rotateChar();
	this->rotateExit();
	this->schedule(schedule_selector(LayerGame::move),0.1f);
}

void LayerGame::addTiledWithData(CCArray* data,u_int x,u_int y)
{
	u_int side0 = atoi(((CCString*)data->objectAtIndex(0))->getCString());
	u_int side1 = atoi(((CCString*)data->objectAtIndex(1))->getCString());;
	u_int side2 = atoi(((CCString*)data->objectAtIndex(2))->getCString());;
	u_int side3 = atoi(((CCString*)data->objectAtIndex(3))->getCString());;

    // Remove helpers (white lines in map editor)
    if( side0 & Config::ZeroPathToTop )     side0 ^= Config::ZeroPathToTop;
    if( side0 & Config::ZeroPathToRight )   side0 ^= Config::ZeroPathToRight;
    if( side0 & Config::ZeroPathToBottom )  side0 ^= Config::ZeroPathToBottom;
    if( side0 & Config::ZeroPathToLeft )    side0 ^= Config::ZeroPathToLeft;

    if( side1 & Config::ZeroPathToTop )     side1 ^= Config::ZeroPathToTop;
    if( side1 & Config::ZeroPathToRight )   side1 ^= Config::ZeroPathToRight;
    if( side1 &	Config::ZeroPathToBottom )  side1 ^= Config::ZeroPathToBottom;
    if( side1 & Config::ZeroPathToLeft )    side1 ^= Config::ZeroPathToLeft;

    if( side2 & Config::ZeroPathToTop )     side2 ^= Config::ZeroPathToTop;
    if( side2 & Config::ZeroPathToRight )   side2 ^= Config::ZeroPathToRight;
    if( side2 & Config::ZeroPathToBottom )  side2 ^= Config::ZeroPathToBottom;
    if( side2 & Config::ZeroPathToLeft )    side2 ^= Config::ZeroPathToLeft;

    if( side3 & Config::ZeroPathToTop )     side3 ^= Config::ZeroPathToTop;
    if( side3 & Config::ZeroPathToRight )   side3 ^= Config::ZeroPathToRight;
    if( side3 & Config::ZeroPathToBottom )  side3 ^= Config::ZeroPathToBottom;
    if( side3 & Config::ZeroPathToLeft )    side3 ^= Config::ZeroPathToLeft;
    // Possition of tile in points
	CCPoint tilePos = ccp(x *Config::TILE_SIZE() +Config::TILE_SIZE() /2, y *Config::TILE_SIZE() +Config::TILE_SIZE() /2);

	string sz = ((CCString*)data->objectAtIndex(0))->getCString();
	string s = "S";
	if( side0 == Config::WalkPathEntrance )
	{

		_char->setCharPosition(tilePos);
		_map[x][y][0] = Config::WalkPathEntrance;
		_map[x][y][1] = Config::WalkPathEntrance;
		_map[x][y][2] = Config::WalkPathEntrance;
		_map[x][y][3] = Config::WalkPathEntrance;

		return;
	}
	else if( side0 == Config::WalkPathExit ){
		_exit = CCSprite::createWithSpriteFrameName("pedos.png");
//if(_exit) CCLog("pedos++++++++++++++");
		_exit->setColor(ccBLACK);
		_exit->setPosition(tilePos);
		_backgroundLayer->addChild(_exit);

		_map[x][y][0] = Config::WalkPathExit;
		_map[x][y][1] = Config::WalkPathExit;
		_map[x][y][2] = Config::WalkPathExit;
		_map[x][y][3] = Config::WalkPathExit;

		return;
	}
	else if( sz.substr(0,1) == s )
	{
		char str[20];
		sprintf(str,"%s.png",((CCString*)data->objectAtIndex(0))->getCString());
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
//if(sprite) CCLog("wall++++++++++++++%s.png",((CCString*)data->objectAtIndex(0))->getCString());
		sprite->setPosition(tilePos);
		_backgroundLayer->addChild(sprite);

        // Animated texture
		if( data->objectAtIndex(0)->isEqual(CCString::create("S21")) )
		{
			char str[20];
			sprintf(str,"%s.png",((CCString*)data->objectAtIndex(0))->getCString());
			CCSprite *upperSprite = CCSprite::createWithSpriteFrameName(str);
if(upperSprite) CCLog("upperSprite++++++++++++++%s.png",((CCString*)data->objectAtIndex(0))->getCString());
			upperSprite->setPosition(tilePos);
			_backgroundLayer->addChild(upperSprite);

//			CCArray *animFrames = CCArray::create();
//			animFrames->retain();
//			animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("S21_2.png"));
//			animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("S21_3.png"));
//			animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("S21_4.png"));
//			animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("S21_5.png"));
//			animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("S21_6.png"));
//			animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("S21_7.png"));
//			animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("S21_8.png"));
//			CCAnimation* animation= CCAnimation::create(animFrames,0.5f);
//			upperSprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
//			CC_SAFE_RELEASE(animFrames);
		}

		_map[x][y][0] = Config::WalkPathNoPath;
		_map[x][y][1] = Config::WalkPathNoPath;
		_map[x][y][2] = Config::WalkPathNoPath;
		_map[x][y][3] = Config::WalkPathNoPath;

		return;
	}
	else if( side0 == Config::WalkPathWalk && side1 == Config::WalkPathWalk && side2 == Config::WalkPathWalk && side3 == Config::WalkPathWalk ){
		_map[x][y][0] = Config::WalkPathWalk;
		_map[x][y][1] = Config::WalkPathWalk;
		_map[x][y][2] = Config::WalkPathWalk;
		_map[x][y][3] = Config::WalkPathWalk;

		return;
	}
//CCLog("------------------s");

	//construct map
	_map[x][y][0] = side0;
	_map[x][y][1] = side1;
	_map[x][y][2] = side2;
	_map[x][y][3] = side3;
	char str[20]={0};
	//0 Side
	if( side0 & Config::WalkPathToRight ){

		sprintf(str,"A%u.png",Config::WalkPathToRight);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
//		if(sprite) CCLog("sprite-------A%u.png",Config::WalkPathToRight);
		this->setPath(sprite ,0 ,x ,y);
	}
	if( side0 & Config::WalkPathToBottom ){
		sprintf(str,"A%u.png",Config::WalkPathToBottom);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
//		if(sprite) CCLog("sprite-------A%u.png",Config::WalkPathToBottom);
		this->setPath(sprite ,0 ,x ,y);
	}
	if( side0 & Config::WalkPathToLeft ){
		sprintf(str,"A%u.png",Config::WalkPathToLeft);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
//		if(sprite) CCLog("sprite-------A%u.png",Config::WalkPathToLeft);
		this->setPath(sprite ,0 ,x ,y);
	}

	//1 Side
	if( side1 & Config::WalkPathToTop ){
		sprintf(str,"B%u.png",Config::WalkPathToTop);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
//		if(sprite) CCLog("sprite-------B%u.png",Config::WalkPathToTop);
		this->setPath(sprite ,1 ,x ,y);
	}
	if( side1 & Config::WalkPathToBottom ){
		sprintf(str,"B%u.png",Config::WalkPathToBottom);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
///		if(sprite) CCLog("sprite-------B%u.png",Config::WalkPathToBottom);
		this->setPath(sprite ,1 ,x ,y);
	}
	if( side1 & Config::WalkPathToLeft ){
		sprintf(str,"B%u.png",Config::WalkPathToLeft);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
//	if(sprite) CCLog("sprite-------B%u.png",Config::WalkPathToLeft);
		this->setPath(sprite ,1 ,x ,y);
	}

	//2 Side
	if( side2 & Config::WalkPathToTop ){
		sprintf(str,"C%u.png",Config::WalkPathToTop);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
//		if(sprite) CCLog("sprite-------B%u.png",Config::WalkPathToTop);
		this->setPath(sprite ,2 ,x ,y);
	}
	if( side2 & Config::WalkPathToRight ){
		sprintf(str,"C%u.png",Config::WalkPathToRight);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
//		if(sprite) CCLog("sprite-------B%u.png",Config::WalkPathToRight);
		this->setPath(sprite ,2 ,x ,y);
	}
	if( side2 &Config:: WalkPathToLeft ){
		sprintf(str,"C%u.png",Config::WalkPathToLeft);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
//		if(sprite) CCLog("sprite-------B%u.png",Config::WalkPathToLeft);
		this->setPath(sprite ,2 ,x ,y);
	}

	//3 Side
	if( side3 & Config::WalkPathToTop ){
		sprintf(str,"D%u.png",Config::WalkPathToTop);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
//		if(sprite) CCLog("sprite-------D%u.png",Config::WalkPathToTop);
		this->setPath(sprite ,3 ,x ,y);
	}
	if( side3 & Config::WalkPathToRight ){
		sprintf(str,"D%u.png",Config::WalkPathToRight);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
//		if(sprite) CCLog("sprite-------D%u.png",Config::WalkPathToRight);
		this->setPath(sprite ,3 ,x ,y);
	}
	if( side3 & Config::WalkPathToBottom ){
		sprintf(str,"D%u.png",Config::WalkPathToBottom);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(str);
//		if(sprite) CCLog("sprite-------D%u.png",Config::WalkPathToBottom);
		this->setPath(sprite ,3 ,x ,y);
	}
}

void LayerGame::rotateChar()
{
	//Rotate
	for(u_int y=0;y<100;y++)
	{
		for(u_int x=0;x<100;x++)
		{
			if(_map[x][y][0] == Config::WalkPathEntrance)
			{
				//check where char can go
				if(y!=0 && _map[x][y-1][Config::SideTop] && !(_map[x][y-1][Config::SideTop&Config::WalkPathNoPath]))
				{
					_char->rotateToSide(Config::SideBottom);
					return;
				}else if(_map[x][y+1][Config::SideBottom] && !(_map[x][y+1][Config::SideBottom] & Config::WalkPathNoPath) )
				{
					_char->rotateToSide(Config::SideTop);
					return;
				}else if( x != 0 && _map[x-1][y][Config::SideRight] && !(_map[x-1][y][Config::SideRight] & Config::WalkPathNoPath) ){
					_char->rotateToSide(Config::SideLeft);
					return;
				}else if( _map[x+1][y][Config::SideLeft] && !(_map[x+1][y][Config::SideLeft] & Config::WalkPathNoPath) ){
					_char->rotateToSide(Config::SideRight);
					return;
				}
			}
		}
	}
}

void LayerGame::rotateExit()
{
	// Rotate exit
	for( u_int y=0; y<100; y++ )
	{
		for( u_int x=0; x<100; x++ )
		{
			if( _map[x][y][0] == Config::WalkPathExit )
			{

				//check where char can go
				if( y != 0 && _map[x][y-1][Config::SideTop] && !(_map[x][y-1][Config::SideTop] & Config::WalkPathNoPath) )
				{
					_exit->setRotation( Config::SideTop *90);
				}else if( _map[x][y+1][Config::SideBottom] && !(_map[x][y+1][Config::SideBottom] & Config::WalkPathNoPath) )
				{
					_exit->setRotation( Config::SideBottom *90);
				}
				else if( x != 0 && _map[x-1][y][Config::SideRight] && !(_map[x-1][y][Config::SideRight] & Config::WalkPathNoPath) ){
					_exit->setRotation( Config::SideRight *90);
				}else if( _map[x+1][y][Config::SideLeft] == 0 || !(_map[x+1][y][Config::SideLeft] & Config::WalkPathNoPath) ){
					_exit->setRotation( Config::SideLeft *90);
				}else if( y == 0 )
				{
					_exit->setRotation( Config::SideBottom *90);
                }

				return;
			}
		}
	}
}




void LayerGame::setPath(CCSprite* path,u_int side, u_int x,u_int y)
{
	CCPoint tilePos = ccp(x *Config::TILE_SIZE()+Config::TILE_SIZE()/2,y *Config::TILE_SIZE()+Config::TILE_SIZE()/2);
	CCString* posName = CCString::createWithFormat("%i|%i|%i%",x,y,side);

	if(!_mapTiles->objectForKey(posName->getCString()))
	{
		_mapTiles->setObject(CCArray::createWithCapacity(4),posName->getCString());
	}

	_mapTiles->setObject(path,posName->getCString());
	path->setPosition(tilePos);
	_backgroundLayer->addChild(path);
}

void LayerGame::mapCompleated()
{
	Config::sharedConfig()->setMap(_mapNo,true);
	if(_mapNo == TOTAL_MAPS)
	{
		//CCDirector::sharedDirector()->replaceScene();
	}else
	{
		CCDirector::sharedDirector()->replaceScene(CCTransitionSplitRows::create(1.0f,PickMapScene::scene()));
	}
}

void LayerGame::onEnter()
{
	CCLayer::onEnter();
}
//onEnterTransitionDidFinish方法会在调用onEnter方法后调用。 如果使用了过渡场景，则onEnterTransitionDidFinish方法会在过渡效果结束以后调用。
void LayerGame::onEnterTransitionDidFinish()
{

	this->charDidFinishWalking();
	CCLayer::onEnterTransitionDidFinish();
}
void LayerGame::charWillBeginWalking()
{

	// Looking at
	CCPoint lookingAt = _char->lookingAtGridPosition();
	CCString *posName = CCString:: createWithFormat("%i|%i|%i",(int)lookingAt.x,(int)lookingAt.y,_char->opositeSideOfSide(_char->rotationSide()));

	CCDictElement* elment;
	CCDICT_FOREACH(_mapTiles,elment)
	{
		CCString* str = CCString::create(elment->getStrKey());
		if(str->isEqual(posName))
		{
			CCSprite* path = (CCSprite*)_mapTiles->objectForKey(elment->getStrKey());
			path->setScale(1.0f);
			path->setColor(ccWHITE);
			_backgroundLayer->reorderChild(path,0);
			return;
		}
	}

}

void LayerGame::charDidFinishWalking()
{
	//Standing on
	u_int x = _char->gridPosition().x;
	u_int y = _char->gridPosition().y;

	// Check if we entered exit
	if( _map[x][y][0] == Config::WalkPathExit ){
		this->mapCompleated();
		return;
	}

	// Where character looking at
	x	= _char->lookingAtGridPosition().x;
	y	= _char->lookingAtGridPosition().y;

    // What are possibile patches
	_possiblePaths = _map[x][y][_char->opositeSideOfSide(_char->rotationSide())];

	if(	  _possiblePaths == Config::WalkPathToTop
	   || _possiblePaths == Config::WalkPathToRight
	   || _possiblePaths == Config::WalkPathToBottom
	   || _possiblePaths == Config::WalkPathToLeft
	   || _possiblePaths == Config::WalkPathWalk
	){
		// If player can go one way only - go there
		_char->walkByPath(_possiblePaths);
		return;
	}
	else{
        // Highlite where player can go
		CCString *posName = CCString:: createWithFormat("%i|%i|%i",x,y,_char->opositeSideOfSide(_char->rotationSide()));

		CCDictElement* elment;
		CCDICT_FOREACH(_mapTiles,elment)
		{
			CCString* str = CCString::create(elment->getStrKey());
			if(str->isEqual(posName))
			{
				CCSprite* path = (CCSprite*)_mapTiles->objectForKey(elment->getStrKey());
				path->setColor(ccGREEN);
				_backgroundLayer->reorderChild(path,1);
				return;
			}


		}
	}
}

void LayerGame::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch = (cocos2d::CCTouch*)(pTouches->anyObject());
	CCPoint touchPoint = this->convertTouchToNodeSpace(touch);

	 // Is back button clicked?
	if(_backSprite->boundingBox().containsPoint(touchPoint))
	{
		CCDirector::sharedDirector()->replaceScene(CCTransitionSplitRows::create(1.0f,PickMapScene::scene()));
		return;
	}

	// If character still animating don't do anything
	if( _char->isBussy() )
		return;

	CCPoint charPoint = _char->getPosition();
	//Adjust char point to way hes looking
	switch ( _char->rotationSide() )
	{
		case Config::SideTop:
			charPoint.y += Config::TILE_SIZE();
			break;
		case Config::SideRight:
			charPoint.x += Config::TILE_SIZE();
			break;
		case Config::SideBottom:
			charPoint.y -= Config::TILE_SIZE();
			break;
		case Config::SideLeft:
			charPoint.x -= Config::TILE_SIZE();
			break;
	}

	int xDistance = touchPoint.x -charPoint.x;
	int yDistance = touchPoint.y -charPoint.y;
	u_int  side;

	if( abs(xDistance) > abs(yDistance) )
	{
		if( xDistance > 0 )
			side = Config::SideRight;
		else
			side = Config::SideLeft;
	 }
	 else if( yDistance > 0 )
		 side = Config::SideTop;
	 else if( yDistance < 0 )
		 side = Config::SideBottom;



	// Looking at
	u_int x	= _char->lookingAtGridPosition().x;
	u_int y	= _char->lookingAtGridPosition().y;

	_possiblePaths = _map[x][y][_char->opositeSideOfSide(_char->rotationSide())];

	// Can we walk
	if( (side == Config::SideTop) && (_possiblePaths & Config::WalkPathToTop) ){
		_char->walkByPath(Config::WalkPathToTop);
	}else if( side == Config::SideRight && (_possiblePaths & Config::WalkPathToRight) ){
		_char->walkByPath(Config::WalkPathToRight);
	}else if( side == Config::SideBottom && (_possiblePaths & Config::WalkPathToBottom) ){
		_char->walkByPath(Config::WalkPathToBottom);
	}else if( side == Config::SideLeft && (_possiblePaths & Config::WalkPathToLeft) ){
		_char->walkByPath(Config::WalkPathToLeft);
	}

}

void LayerGame::StringSplit(string s,char splitchar,vector<string>& vec)
{
	if(vec.size()>0)//保证vec是空的
	   vec.clear();
	int length = s.length();
	int start=0;
	for(int i=0;i<length;i++)
	{
	   if(s[i] == splitchar && i == 0)//第一个就遇到分割符
	   {
		start += 1;
	   }
	   else if(s[i] == splitchar)
	   {
		vec.push_back(s.substr(start,i - start));
		start = i+1;
	   }
	   else if(i == length-1)//到达尾部
	   {
		vec.push_back(s.substr(start,i+1 - start));
	   }
	}
}

void LayerGame::move(CCObject* pSender)
{
	_char->updata();
}
