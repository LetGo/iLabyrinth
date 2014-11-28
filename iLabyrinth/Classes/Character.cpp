/*
 * Character.cpp
 *
 *  Created on: 2013-7-21
 *      Author: a582o_000
 */

#include "Character.h"
#include "LayerGame.h"

Character::Character() {
	// TODO Auto-generated constructor stub

}

Character::~Character() {
	CC_SAFE_RELEASE(this);
}
bool Character::init()
{
	if(!CCSprite::init()){ return false;}

	CCArray* walkFrames = CCArray::create();

	walkFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("CH1.png"));
	walkFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("CH2.png"));
	walkFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("CH3.png"));
	walkFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("CH4.png"));
	walkFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("CH5.png"));
	walkFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("CH6.png"));
	walkFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("CH7.png"));
	walkFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("CH8.png"));

	CCAnimationCache::sharedAnimationCache()->addAnimation(CCAnimation::createWithSpriteFrames(walkFrames),"walk");
	
	this->reset();
	retain();
	return true;
}

u_int Character::opositeSideOfSide(u_int side)
{
	switch ( side )
	{
		case Config::SideTop:
			return Config::SideBottom;
		case Config::SideRight:
			return Config::SideLeft;
		case Config::SideBottom:
			return Config::SideTop;
		case Config::SideLeft:
			return Config::SideRight;
	}

	return side;
}

void Character::rotateToSide(Config::Side side)
{
	this->rotateNode(this,side);
}

void Character::rotateNode(CCNode *node ,Config::Side side)
{
	node->setRotation(side*90);
}

u_int Character::rotationSide()
{
	return (u_int)this->getRotation()/90;
}

void Character::walkByPath(u_int path)
{
	CCPoint pathPart1 = CCPointZero;
	CCPoint pathPart2 = CCPointZero;
	u_int side = -1;

	switch(this->opositeSideOfSide(this->rotationSide()))
	{
	case Config::SideTop: {
		switch ( path ) {
			case Config::WalkPathToRight: {
				pathPart1 = ccp(0, -Config::TILE_SIZE());
				pathPart2 = ccp(Config::TILE_SIZE(), 0);
				side	  = Config::SideRight;
				break;
			}
			case Config::WalkPathToBottom: {
				pathPart1 = ccp(0, -Config::TILE_SIZE());
				pathPart2 = ccp(0, -Config::TILE_SIZE());
				side	  = Config::SideBottom;
				break;
			}
			case Config::WalkPathWalk: {
				pathPart1 = ccp(0, -Config::TILE_SIZE());
				pathPart2 = CCPointZero;
				side	  =Config::SideBottom;
				break;
			}
			case Config::WalkPathToLeft: {
				pathPart1 = ccp(0, -Config::TILE_SIZE());
				pathPart2 = ccp(-Config::TILE_SIZE(), 0);
				side	  = Config::SideLeft;
				break;
			}
		}
		break;
	}
	case Config::SideRight: {
		switch ( path ) {
			case Config::WalkPathToTop: {
				pathPart1 = ccp(-Config::TILE_SIZE(), 0);
				pathPart2 = ccp(0, Config::TILE_SIZE());
				side	  = Config::SideTop;
				break;
			}
			case Config::WalkPathToBottom: {
				pathPart1 = ccp(-Config::TILE_SIZE(), 0);
				pathPart2 = ccp(0, -Config::TILE_SIZE());
				side	  = Config::SideBottom;
				break;
			}
			case Config::WalkPathToLeft: {
				pathPart1 = ccp(-Config::TILE_SIZE(), 0);
				pathPart2 = ccp(-Config::TILE_SIZE(), 0);
				side	  = Config::SideLeft;
				break;
			}
			case Config::WalkPathWalk: {
				pathPart1 = ccp(-Config::TILE_SIZE(), 0);
				pathPart2 = CCPointZero;
				side	  = Config::SideLeft;
				break;
			}
		}
		break;
	}
	case Config::SideBottom: {
		switch ( path ) {
			case Config::WalkPathToTop: {
				pathPart1 = ccp(0, Config::TILE_SIZE());
				pathPart2 = ccp(0, Config::TILE_SIZE());
				side	  = Config::SideTop;
				break;
			}
			case Config::WalkPathWalk: {
				pathPart1 = ccp(0, Config::TILE_SIZE());
				pathPart2 = CCPointZero;
				side	  = Config::SideTop;
				break;
			}
			case Config::WalkPathToRight: {
				pathPart1 = ccp(0, Config::TILE_SIZE());
				pathPart2 = ccp(Config::TILE_SIZE(), 0);
				side	  = Config::SideRight;
				break;
			}
			case Config::WalkPathToLeft: {
				pathPart1 = ccp(0, Config::TILE_SIZE());
				pathPart2 = ccp(-Config::TILE_SIZE(), 0);
				side	  = Config::SideLeft;
				break;
			}
		}
		break;
	}
	case Config::SideLeft:
	{
		switch ( path ) {
			case Config::WalkPathToTop: {
				pathPart1 = ccp(Config::TILE_SIZE(), 0);
				pathPart2 = ccp(0, Config::TILE_SIZE());
				side	  = Config::SideTop;
				break;
			}
			case Config::WalkPathToRight: {
				pathPart1 = ccp(Config::TILE_SIZE(), 0);
				pathPart2 = ccp(Config::TILE_SIZE(), 0);
				side	  = Config::SideRight;
				break;
			}
			case Config::WalkPathWalk: {
				pathPart1 = ccp(Config::TILE_SIZE(), 0);
				pathPart2 = CCPointZero;
				side	  = Config::SideRight;
				break;
			}
			case Config::WalkPathToBottom: {
				pathPart1 = ccp(Config::TILE_SIZE(), 0);
				pathPart2 = ccp(0, -Config::TILE_SIZE());
				side	  = Config::SideBottom;
				break;
			}
		}
		break;
		}
	}

	// Will character walk straight line, or will he will make turn?
	if( pathPart2.x == 0 && pathPart2.y == 0 )
	{
		CCFiniteTimeAction* func1 = CCCallFunc::create((CCLayer*)(this->getParent())->getParent(),callfunc_selector(LayerGame::charWillBeginWalking));
		CCFiniteTimeAction* moveby1 = CCMoveBy::create(0.5f,pathPart1);
		CCFiniteTimeAction* func2 = CCCallFunc::create(this,callfunc_selector(Character::reset));
		CCFiniteTimeAction* func3 = CCCallFunc::create((CCLayer*)(this->getParent())->getParent(),callfunc_selector(LayerGame::charDidFinishWalking));
		CCFiniteTimeAction* sequence = CCSequence::create(func1,moveby1,func2,func3,NULL);
		this->runAction(sequence);
	}else{
		CCFiniteTimeAction* func1 = CCCallFunc::create((CCLayer*)(this->getParent())->getParent(),callfunc_selector(LayerGame::charWillBeginWalking));
		CCFiniteTimeAction* moveby1 = CCMoveBy::create(0.5f,pathPart1);
		CCFiniteTimeAction* funcND = CCCallFuncND::create(this,callfuncND_selector(Character::rotateNode),(void*)side);
		CCFiniteTimeAction* moveby2 = CCMoveBy::create(0.5f,pathPart2);
		CCFiniteTimeAction* func2 = CCCallFunc::create(this,callfunc_selector(Character::reset));
		CCFiniteTimeAction* func3 = CCCallFunc::create((CCLayer*)(this->getParent())->getParent(),callfunc_selector(LayerGame::charDidFinishWalking));
		CCFiniteTimeAction* sequence = CCSequence::create(func1,moveby1,funcND,moveby2,func2,func3,NULL);
		this->runAction(sequence);
	}
}

CCPoint Character::gridPosition()
{
	return ccp( this->getPositionX() /Config::TILE_SIZE(), this->getPositionY() /Config::TILE_SIZE());
}

CCPoint Character::lookingAtGridPosition()
{
	CCPoint _gridPosition = gridPosition();
	u_int slid = this->opositeSideOfSide(this->rotationSide());

	switch ( slid ) {
		case Config::SideTop:
			_gridPosition.y--;
			break;
		case Config::SideRight:
			_gridPosition.x--;
			break;
		case Config::SideBottom:
			_gridPosition.y++;
			break;
		case Config::SideLeft:
			_gridPosition.x++;
			break;
	}
	return _gridPosition;
}

bool Character::isBussy()
{
	return ( this->numberOfRunningActions() != 0 );
}

void Character::updata()
{
	if(ccpDistance(this->getPosition(),_lastFramePos) >= 2)
	{
		this->nextFrame();
		_lastFramePos = this->getPosition();
	}
}
void Character::setCharPosition(CCPoint pos)
{
	this->setPosition(pos);
	if(ccpDistance(pos,_lastFramePos) >= 2)
	{
		this->nextFrame();
		_lastFramePos = pos;
	}
}

void Character::nextFrame()
{
    // Manualy advance animation frame
   this->setDisplayFrameWithAnimationName("walk",_charFrame);
   if( ++_charFrame > 7 )
		_charFrame = 0;
}

void Character::reset()
{
	_charFrame=2;

    // Reset animation frame
    this->setDisplayFrameWithAnimationName("walk",1);
}
