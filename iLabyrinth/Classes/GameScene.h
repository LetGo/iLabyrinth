/*
 * GameScene.h
 *
 *  Created on: 2013-7-21
 *      Author: a582o_000
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_
#include "cocos2d.h"
#include "LayerGame.h"

class GameScene:public cocos2d::CCScene
{
private:
	LayerGame* _gameLayer;
public:
	GameScene();
	virtual ~GameScene();
	static GameScene* createWithMap(u_int map);
	bool initWithMap(u_int mapNo);
	//CREATE_FUNC(GameScene);
};

#endif /* GAMESCENE_H_ */
