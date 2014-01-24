#include "AppDelegate.h"
//#include "HelloWorldScene.h"
#include "TitleScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IconAdManagerC.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "IconAdNative.h"
#endif

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

	//全面に調整
    CCLOG("WinSize=%fx%f",pDirector->getWinSize().width,pDirector->getWinSize().height);
    CCLOG("FrameSize=%fx%f",pEGLView->getFrameSize().width,pEGLView->getFrameSize().height);
    double   asp = (double)pEGLView->getFrameSize().height/(double)pEGLView->getFrameSize().width;
    if (asp>=1136.0/640.0) {
		//iPhone 4inch と同じかそれより縦長はiPhone 4inchと一緒にする(Androidもだいたいここ)
        pEGLView->setDesignResolutionSize(640, 1136, kResolutionShowAll);
        CCLOG("setDesignResolutionSize=%dx%d",640,1136);
    }else if(asp<=1024.0/768.0) {
		//iPad と同じかそれより横長はiPadと一緒にする(ただし横幅640として全面拡大);
        pEGLView->setDesignResolutionSize(640, 854, kResolutionShowAll);
        CCLOG("setDesignResolutionSize=%dx%d",640,854);
    }else {
		//それ以外は横640として全面拡大(iPhone 3.5inchもここ)
        int height = (int)(640.0*asp);
        pEGLView->setDesignResolutionSize(640, height, kResolutionShowAll);
        CCLOG("setDesignResolutionSize=%dx%d",640,height);
    }
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = TitleScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

	//アイコン広告 pause
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IconAdPauseView();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Cocos2dExt::IconAdNative::pauseView();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

	//アイコン広告 resume
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IconAdResumeView();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Cocos2dExt::IconAdNative::resumeView();
#endif
}
