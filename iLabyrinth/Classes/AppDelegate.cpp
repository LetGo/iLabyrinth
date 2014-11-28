#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
//#include "MenuScene.h"
#include "WelcomeScene.h"
#include "Config.h"
USING_NS_CC;
using namespace CocosDenshion;
AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();

  //  pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

     pDirector->setOpenGLView(pEGLView);
     if(Config::sharedConfig()->isIpad()){
    	 pEGLView->setDesignResolutionSize(960, 640, kResolutionExactFit);
     }
     else{
    	 pEGLView->setDesignResolutionSize(480, 320, kResolutionExactFit);
     }
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    pDirector->setProjection(kCCDirectorProjection2D);
    

    CCTexture2D::setDefaultAlphaPixelFormat(kTexture2DPixelFormat_RGBA8888);
   
//Config::sharedConfig()->initIsMapCanPlay();
// Preload sounds
  //  SimpleAudioEngine::sharedEngine()->preloadEffect("clic.caf");   
  
  
  //	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

  	//if(Config::sharedConfig()->isIpad()){
 // 		cache->addSpriteFramesWithFile("sprites~ipad.plist");
//  	}else
//		cache->addSpriteFramesWithFile("sprites.plist");


    CCScene *pScene = WelcomeScene::scene();
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();

}
