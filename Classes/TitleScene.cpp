#include "TitleScene.h"
#include "GameScene.h"

USING_NS_CC;

CCScene* TitleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TitleScene *layer = TitleScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(TitleScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width-40 ,
                                origin.y + visibleSize.height-40) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
#endif
    /////////////////////////////
    // 3. add your codes below...
    CCLabelTTF *playLabel = CCLabelTTF::create("Play Game", "Helvetica", 80);
    CCMenuItemLabel *playItem = CCMenuItemLabel::create(playLabel, this, menu_selector(TitleScene::menuPlayGameCallback));
    playItem->setColor(ccc3(255, 100, 100));
	CCMenu *itemMenu = CCMenu::createWithItem(playItem);
	itemMenu->setPosition(ccp(visibleSize.width/2, visibleSize.height/2- playLabel->getContentSize().height/2));
    
    this->addChild(itemMenu, 1);

    // add the background image
    CCSprite* titleSpr = CCSprite::create("title.png");

    // position the sprite on the center of the screen
    titleSpr->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height*3/4 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(titleSpr, 0);
    
    
    CCLabelTTF *authorLabel = CCLabelTTF::create("Maxi Gundan Presents.", "Helvetica", 20);
    authorLabel->setColor(ccc3(255, 255, 255));
    authorLabel->setPosition(ccp(visibleSize.width/2 + origin.x, titleSpr->getPosition().y-titleSpr->getContentSize().height/2 - authorLabel->getContentSize().height/2 + origin.y));
    this->addChild(authorLabel);
    
    return true;
}


void TitleScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCDirector::sharedDirector()->end();
#endif
}
void TitleScene::menuPlayGameCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f,GameScene::scene()));
}
