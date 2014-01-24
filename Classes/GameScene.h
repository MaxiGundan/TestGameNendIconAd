#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuButtonCallback(CCObject* pSender);
    void menuRetryCallback(CCObject* pSender);
    void menuEndCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

private:
	cocos2d::CCLabelTTF* questionLabel;
	cocos2d::CCSprite* judgeSpr;
	cocos2d::CCLayer* mainLayer;
	cocos2d::CCLayer* resultLayer;
    
	void initGame();
	void setRandomNum();
	void showResults();
	void cleanResults();
    
	void execAfterHitAction(float dt);  //via schedule_selector
	void execAfterMissAction(CCNode *sendor);  //via callfuncN_selector
    
	const char* getHonorString(int count);

	int gameCount;
	int gameAnswer;
    bool lockMenu;  //avoid repeated hit
};

#endif // __GAME_SCENE_H__
