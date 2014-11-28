/*
 * Config.cpp
 *
 *  Created on: 2013-7-21
 *      Author: a582o_000
 */

#include "Config.h"
USING_NS_CC;

static  Config *g_config = NULL;

Config::Config()
{
    compleatedMaps = CCSet::create();
    compleatedMaps->retain();
    _scrollOffset = 0;
    setscrollOffset(_scrollOffset);
}

Config::~Config()
{
	CC_SAFE_RELEASE(compleatedMaps);

}

Config* Config::sharedConfig()
{
    if (!g_config)
    {
        g_config = new Config();
    }

    return g_config;
}

bool Config::isIpad()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize ipadSize;
	ipadSize.setSize(960,640);
	if(winSize.width>=ipadSize.width&&winSize.height>=winSize.height){

		return true;
	}
	return false;
}
void Config::initIsMapCanPlay()
{
	if(!CCUserDefault::sharedUserDefault()->getBoolForKey("1")){
		CCUserDefault::sharedUserDefault()->setBoolForKey("1",true);
		CCUserDefault::sharedUserDefault()->setBoolForKey("2",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("3",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("4",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("5",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("6",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("7",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("8",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("9",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("10",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("11",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("12",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("13",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("14",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("15",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("16",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("17",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("18",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("19",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("20",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("21",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("22",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("23",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("24",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("25",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("26",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("27",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("28",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("29",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("30",false);

		CCUserDefault::sharedUserDefault()->setBoolForKey("31",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("32",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("33",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("34",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("35",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("36",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("37",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("38",false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("39",false);
		CCUserDefault::sharedUserDefault()->flush();
	}
}
void Config::setMap(u_int map, bool completed)
{
	char mapNo[10];
	sprintf(mapNo,"%d",map+1);
	CCUserDefault::sharedUserDefault()->setBoolForKey(mapNo,completed);
	CCUserDefault::sharedUserDefault()->flush();
}

bool Config::canPlayMap(u_int map)
{
	char mapNo[10];
	sprintf(mapNo,"%d",map);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(mapNo);
}
