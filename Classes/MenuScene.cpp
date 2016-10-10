///Users/mac/Documents/cocos2d-x-2.2.2/projects/King/proj.ios/King.xcodeproj
//  MenuScene.cpp
//  King
//
//  Created by mac on 14-3-26.
//
//

#include "MenuScene.h"
//
//  LoadingScene.cpp
//  GedouKing
//
//  Created by mac on 14-3-26.
//
//

#include "LoadingScene.h"
#include "Define.h"
#include "AboutScene.h"
#include "SelectScene.h"
#include "PersonalAudioEngine.h"
#include "GameData.h"
#include "ShopScene.h"

#include "GreyNode.h"
bool MenuScene::init()
{
    if ( !BaseLayer::init() )
    {
        return false;
    }
    CCSprite* menu_main = CCSprite::create("menu/zhujiemian_bj.png");
	//GreyNode* menu_main = GreyNode::create("menu/zhujiemian_bj.png");
    this->addChild(menu_main,-1);
    menu_main->setPosition(CCPoint(SIZE.width/2,SIZE.height/2));
    return true;
}

void MenuScene::screenShake(int frameNum,int yValue)
{
    CCMoveBy* moveUp = CCMoveBy::create(AttackFrame, ccp(0,yValue));
    CCMoveBy* moveDown = dynamic_cast<CCMoveBy*>(moveUp->reverse());
    CCCallFunc* shakeResume = CCCallFunc::create((GameScene*)this,callfunc_selector(GameScene::resumeShake));
    this->getParent()->runAction(CCSequence::create(CCRepeat::create(CCSequence::create(moveUp,moveDown,NULL), frameNum),shakeResume,NULL));
}

void MenuScene::resumeShake()
{
    this->getParent()->setPositionY(0.0f);
}

void MenuScene::onEnterTransitionDidFinish()
{
    CCSprite* menu_title = CCSprite::create("menu/biaoti.png");
    menu_title->setAnchorPoint(ccp(0, 0.5));
    this->addChild(menu_title,0);
    menu_title->setPosition(CCPoint(SIZE.width*0.05,SIZE.height*0.78));
    menu_title->setScale(2.2f);
  
    menu_title->runAction(CCSequence::create( CCScaleTo::create(0.5f, 1.0f),CCCallFunc::create(this, callfunc_selector( MenuScene::brate  ))  ,NULL) );
    
    CCMenu* menu = CCMenu::create();
    
    beginItem = CCMenuItemImage::create("menu/youxikaishi.png", "menu/youxikaishi.png", this, menu_selector(MenuScene::StartGame));
    menu->addChild(beginItem,2);
    beginItem->setPosition(CCPoint(SIZE.width*1.1,SIZE.height*0.25));
    beginItem->setScale(1.2f);
    beginItem->runAction(CCSequence::create(CCDelayTime::create(0.55f),CCMoveTo::create(0.4f,CCPoint(SIZE.width*0.5,SIZE.height*0.25)),CCCallFunc::create(this, callfunc_selector( MenuScene::begingame  )),  NULL ));
    
    this->addChild(menu);
    menu->setPosition(ccp(0,0));
    
    
    if(KingData->getMusicVolume() > 0)
    {
        music =  CCMenuItemToggle::createWithTarget(this, menu_selector(MenuScene::musicOn ), CCMenuItemImage::create("menu/shengyin.png", "menu/shengyin.png"),CCMenuItemImage::create("menu/shengyin2.png", "menu/shengyin2.png"),NULL);
    }else
    {
        music =  CCMenuItemToggle::createWithTarget(this, menu_selector(MenuScene::musicOn ), CCMenuItemImage::create("menu/shengyin2.png", "menu/shengyin2.png"),CCMenuItemImage::create("menu/shengyin.png", "menu/shengyin.png"),NULL);
    }
    
    
    moreGame = CCMenuItemImage::create("menu/youxiji.png", "menu/youxiji.png", this,NULL);
    

    
    about = CCMenuItemImage::create("menu/guanyu.png", "menu/guanyu.png", this,menu_selector(MenuScene::AboutGame));
    
    //不添加关于
//    menu->addChild(about,2);
//    menu->addChild(moreGame,2);
    menu->addChild(music,2);
    
    about->setPosition(ccp(-0.5*SIZE.width, SIZE.height*0.1));
    
    music->setPosition(ccp(-0.6*SIZE.width, SIZE.height*0.1));
    
//    moreGame->setPosition(ccp(-0.5*SIZE.width, SIZE.height*0.1));
    
    music->runAction(CCMoveBy::create(0.65f, ccp(0.8*SIZE.width, 0)));
    
    about->runAction(CCMoveBy::create(0.77f, ccp(0.7*SIZE.width, 0)));
    
//    moreGame->runAction(CCMoveBy::create(0.90f, ccp(0.6*SIZE.width, 0)));
}

void MenuScene::musicOn(CCObject* pSender)
{
    
    if(KingData->getMusicVolume() > 0)
    {
        IsmusicOn = 0;
    }else
    {
        IsmusicOn = 1;
    }
    if (IsmusicOn == 0)
    {
        PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(-100);
        PersonalAudioEngine::sharedEngine()->setEffectsVolume(-20);
    }
    else if(IsmusicOn == 1)
    {
        PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(100);
        PersonalAudioEngine::sharedEngine()->setEffectsVolume(20);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        
    }
}



void MenuScene::begingame()
{
    
    beginItem->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(0.5, 250),CCFadeTo::create(0.5, 80),NULL )  ));
}

void MenuScene::brate()
{
    screenShake(8,15);
}

void MenuScene::onEnter()
{
    PersonalAudioEngine::sharedEngine()->playBackgroundMusic("music/jiemianbgmusic.mp3",true);
    CCLayer::onEnter();
}

void MenuScene::StartGame(CCObject* pSender)
{
     PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
     bool inbeginner = KingData->getIsbeginer();
     if (inbeginner)
     {
        CCDirector::sharedDirector()->replaceScene(GameScene::scene(1));
     }else
     {
        CCDirector::sharedDirector()->replaceScene(SelectScene::scene());
     }
}

void MenuScene::AboutGame(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(AboutScene::scene());
}

void MenuScene::onExit()
{
    PersonalAudioEngine::sharedEngine()->stopAllEffects();
    PersonalAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    CCLayer::onExit();
}

void MenuScene::loadingBack(CCObject* pSender)
{
   // CCTransitionFade::create(<#float duration#>, <#cocos2d::CCScene *scene#>);
}
cocos2d::CCScene* MenuScene::scene()
{
    CCScene *scene = CCScene::create();
    MenuScene *layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}
