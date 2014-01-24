#include "GameScene.h"
#include "TitleScene.h"

// Icon Ad
#define SHOW_ICON_ADS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IconAdManagerC.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "IconAdNative.h"
#endif

USING_NS_CC;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    //create main layer
    mainLayer = CCLayer::create();
    this->addChild(mainLayer, 0);

    //Label
    questionLabel = CCLabelTTF::create("?", "Helvetica", 240.0);
	questionLabel->setPosition(ccp(visibleSize.width/2, visibleSize.height*3/4));
    mainLayer->addChild(questionLabel, 2);
    
    //register SpriteFrame(数が多いときはTexturePackerとか使って.plistとスプライトシートを読み込むほうが楽)
    CCSprite *spr1 = CCSprite::create("atari.png");
    CCSprite *spr2 = CCSprite::create("hazure.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spr1->displayFrame(), "atari.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spr2->displayFrame(), "hazure.png");

    //Sprite
    judgeSpr = CCSprite::create();  //empty object
    judgeSpr->setVisible(false);
    judgeSpr->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    mainLayer->addChild(judgeSpr,100);
    
    //Buttons
	CCArray *itemArr = CCArray::createWithCapacity(5);
	for(int i = 0; i < 5; i++)
	{
		char strbuf[16];
		sprintf(strbuf,"%d",i+1);
		CCLabelTTF *playLabel = CCLabelTTF::create(strbuf, "Helvetica", 100.0);
		CCMenuItemLabel *playItem = CCMenuItemLabel::create(playLabel, this, menu_selector(GameScene::menuButtonCallback));
		playItem->setColor(ccc3(255, 255, 255));
		playItem->setTag(i+1);
		itemArr->addObject(playItem);
	}
    
	CCMenu *pMenu = CCMenu::createWithArray(itemArr);
	pMenu->setPosition(ccp(visibleSize.width/2, visibleSize.height/4));
	pMenu->alignItemsHorizontallyWithPadding(visibleSize.width/10);
    mainLayer->addChild(pMenu, 1);
    
	initGame();

    return true;
}


void GameScene::initGame()
{
	//setup parameters
	srand((unsigned int)time(NULL));
    setRandomNum();
    questionLabel->setString("?");

	gameCount = 0;
    
    lockMenu = false;
}

void GameScene::setRandomNum()
{
	gameAnswer = ((int)(CCRANDOM_0_1()*5.0f) % 5) + 1;
}

void GameScene::showResults()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//show shade layer
	resultLayer = CCLayer::create();
	CCLayerColor* shade = CCLayerColor::create(ccc4(255, 255, 255, 64));
	resultLayer->addChild(shade, 10);

	//register objects
	char strbuf[128];
	snprintf(strbuf,sizeof(strbuf),"%d回目で当たり",gameCount);
    CCLabelTTF* pNumLabel = CCLabelTTF::create(strbuf, "Helvetica", 48);
	pNumLabel->setColor(ccc3(255, 255, 255));
	pNumLabel->setPosition(ccp(visibleSize.width/2, visibleSize.height*3/4));
	resultLayer->addChild(pNumLabel,60);

	const char* honorStr = getHonorString(gameCount);
    CCLabelTTF* pHonorLabel = CCLabelTTF::create(honorStr, "Helvetica", 120);
	pHonorLabel->setColor(ccc3(100, 255, 100));
	pHonorLabel->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	resultLayer->addChild(pHonorLabel,60);
    
    //Menu
    CCLabelTTF *retryLabel = CCLabelTTF::create("Retry", "Helvetica", 80);
    CCMenuItemLabel *retryItem = CCMenuItemLabel::create(retryLabel, this, menu_selector(GameScene::menuRetryCallback));
    retryItem->setColor(ccc3(255, 100, 100));
    CCLabelTTF *endLabel = CCLabelTTF::create("End", "Helvetica", 80);
    CCMenuItemLabel *endItem = CCMenuItemLabel::create(endLabel, this, menu_selector(GameScene::menuEndCallback));
    endItem->setColor(ccc3(255, 100, 100));
    CCMenu *pMenu = CCMenu::create(retryItem,endItem,NULL);
    
    pMenu->setPosition(ccp(visibleSize.width/2, visibleSize.height/4));
    pMenu->alignItemsHorizontallyWithPadding(visibleSize.width/10);
    resultLayer->addChild(pMenu, 60);

	//show layer
	this->addChild(resultLayer,50);
    
#ifdef SHOW_ICON_ADS
    //先読みしていたIconAdを画面内に移動 0=画面上端
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IconAdLocateView(0);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Cocos2dExt::IconAdNative::locateView(0);
#endif
#endif
}

void GameScene::cleanResults()
{
	resultLayer->removeFromParentAndCleanup(true);
}

const char* GameScene::getHonorString(int count)
{
	if(count<=1) {
		return "まぐれ";
	}else if(count<=3) {
		return "偶然";
	}else if(count<=5) {
		return "平凡";
	}else if(count<=10) {
		return "鈍い";
	}
	return "アホ";
}

void GameScene::menuButtonCallback(CCObject* pSender)
{
    if (lockMenu)
        return;
    else
        lockMenu = true;
        
    // show answer
    char strbuf[16];
    sprintf(strbuf, "%d", gameAnswer);
    questionLabel->setString(strbuf);
    
    // inc count
	gameCount++;
    
    // judgement
	CCMenuItemLabel *pMenuItem = (CCMenuItemLabel*)pSender;
	int tag = pMenuItem->getTag();
	if(tag == gameAnswer)
	{
		//あたり
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("atari.png");
        judgeSpr->setDisplayFrame(frame);
        judgeSpr->setVisible(true);
        
        CCScaleTo* scaleto = CCScaleTo::create(0.5f,1.0f);
        CCEaseBounceOut* ease = CCEaseBounceOut::create(scaleto);
        judgeSpr->setScale(0.5f);
        judgeSpr->runAction(ease);
        
        //action wait の代わり
        this->scheduleOnce(schedule_selector(GameScene::execAfterHitAction), 1.5);

#ifdef SHOW_ICON_ADS
        //「あたり」表示中にアイコンデータを画面外に先読み
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        IconAdCreateView(ICNAD_POS_INVALID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        Cocos2dExt::IconAdNative::createView(ICNAD_POS_INVALID);
#endif
#endif

	}
	else
	{
		//はずれ
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hazure.png");
        judgeSpr->setDisplayFrame(frame);
        judgeSpr->setVisible(true);
        
        //mukatsuku effect
        CCJumpBy* jumpby = CCJumpBy::create(0.5f, ccp(0, 0), 40, 3);
        CCCallFuncN *callFunc = CCCallFuncN::create(this, callfuncN_selector(GameScene::execAfterMissAction));
        CCFiniteTimeAction *seq = CCSequence::create(jumpby,callFunc, NULL);
        judgeSpr->runAction(seq);
	}
}

void GameScene::execAfterHitAction(float dt)
{
    //hide game layer
    mainLayer->setVisible(false);
    
    showResults();
}

void GameScene::execAfterMissAction(CCNode *sendor)
{
    judgeSpr->setVisible(false);
    
    setRandomNum();
    questionLabel->setString("?");
    
    lockMenu = false;
}

void GameScene::menuRetryCallback(CCObject* pSender)
{
#ifdef SHOW_ICON_ADS
    //一旦画面外に移動してからリイース(万が一表示が消えないとか起こった場合に分からないように)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IconAdLocateView(ICNAD_POS_INVALID);
    IconAdReleaseView();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Cocos2dExt::IconAdNative::locateView(ICNAD_POS_INVALID);
    Cocos2dExt::IconAdNative::releaseView();
#endif
#endif

    judgeSpr->setVisible(false);
    mainLayer->setVisible(true);
	cleanResults();
	initGame();
}
void GameScene::menuEndCallback(CCObject* pSender)
{
#ifdef SHOW_ICON_ADS
    //Retry時と同じ処理で良い
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IconAdLocateView(ICNAD_POS_INVALID);
    IconAdReleaseView();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Cocos2dExt::IconAdNative::locateView(ICNAD_POS_INVALID);
    Cocos2dExt::IconAdNative::releaseView();
#endif
#endif

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f,TitleScene::scene()));
	cleanResults();
}
