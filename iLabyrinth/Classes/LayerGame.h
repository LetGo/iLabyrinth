/*
 * LayerGame.h
 *
 *  Created on: 2013-7-21
 *      Author: a582o_000
 */

#ifndef LAYERGAME_H_
#define LAYERGAME_H_
#include "cocos2d.h"
#include "Character.h"
#include <vector>
#include "string.h"
USING_NS_CC;
using namespace std;

class LayerGame:public cocos2d::CCLayer {
private:
	CCSize 				_winSize;
	CCSpriteBatchNode  	*_backgroundLayer;
	Character  			*_char;
	CCSprite	       	*_exit;
	CCSprite       		*_backSprite;

	u_int				_mapNo;
	CCDictionary		*_mapTiles;
	u_int          		_map[100][100][4];
	u_int          		_possiblePaths;

    u_int          		_crossRoads;

public:
	LayerGame();
	virtual ~LayerGame();
	bool init();

	void loadMapNo(u_int map);
	void addTiledWithData(CCArray* data,u_int x,u_int y);
	void mapCompleated();
	void setPath(CCSprite* path,u_int side, u_int x,u_int y);

	void rotateChar();
	void rotateExit();
	void StringSplit(string s,char splitchar,vector<string>& vec);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

    void charDidFinishWalking();
    void charWillBeginWalking();


    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();

    void move(CCObject* pSender);
	CREATE_FUNC(LayerGame);
};

#endif /* LAYERGAME_H_ */
