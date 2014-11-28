/*
 * GameScene.cpp
 *
 *  Created on: 2013-7-21
 *      Author: a582o_000
 */

#include "GameScene.h"

GameScene::GameScene() {
	// TODO Auto-generated constructor stub
//	CCLog("GameScene++");
}

GameScene::~GameScene() {
	//CCLog("GameScene--");
}

GameScene* GameScene::createWithMap(u_int map)
{
    GameScene *pRet = new GameScene();
    if (pRet && pRet->initWithMap(map))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = 0;
        return 0;
    }
}

bool GameScene::initWithMap(u_int mapNo)
{
	if(!CCScene::init())
	{
		return false;
	}
	_gameLayer = LayerGame::create();
	_gameLayer->loadMapNo(mapNo);
	addChild(_gameLayer);
	return true;
}
