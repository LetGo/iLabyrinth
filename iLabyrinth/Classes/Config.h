/*
 * Config.h
 *
 *  Created on: 2013-7-21
 *      Author: a582o_000
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#include "cocos2d.h"
#define TOTAL_MAPS 39




class Config :public cocos2d::CCObject
{

public:
	cocos2d::CCSet* compleatedMaps;
	float  _scrollOffset;

public:
	Config();
	virtual ~Config();
	static Config* sharedConfig();
	//下面这个宏是获得和设置的 根据cocos2d改得。在"CCPlatformMacros.h"里面
	CC_SYNTHESIZE(float,mscrollOffset,scrollOffset);
	bool canPlayMap(u_int map);
	void setMap(u_int map, bool completed);
	void initIsMapCanPlay();
	bool isIpad();
public:
	typedef enum {
		WalkPathWalk	= 0,
		WalkPathToTop   = 1 << 1,
		WalkPathToRight = 1 << 2,
		WalkPathToBottom= 1 << 3,
		WalkPathToLeft  = 1 << 4,
		WalkPathEntrance= 1 << 5,
		WalkPathExit	= 1 << 6,
		WalkPathNoPath	= 1 << 7,
	} WalkPath;

	typedef enum {
	    ZeroPathToBottom= 1 << 7,
	    ZeroPathToLeft  = 1 << 8,
	    ZeroPathToTop   = 1 << 9,
	    ZeroPathToRight = 1 << 10
	} ZeroPath;

	typedef enum {
		SideTop		= 0,
		SideRight	= 1,
		SideBottom	= 2,
		SideLeft	= 3,
	} Side;
	static float TILE_SIZE(){

		return ( ( Config::sharedConfig()->isIpad() )?64.0f:32.0f );
	}
};

#endif /* CONFIG_H_ */
