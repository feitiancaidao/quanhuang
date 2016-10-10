//
//  Jihuo.cpp
//  king04
//
//  Created by mac on 14-5-13.
//
//

#include "Jihuo.h"
#include "Define.h"
#include "Hero.h"
#include "Game.h"
#include "GameScene.h"
#include "GameData.h"
#include "SelectScene.h"
#include "GlobleUnits.h"
#include "openalertJni.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
#define ANDROID_CLASS_NAME1 "com/mof/huif/king04"
#define ANDROID_FUNCTION_NAME1 "addXueTong"
//#define ANDROID_FUNCTION_NAME "charge"
#define ANDROID_PARAM_TYPE "(Ljava/lang/String;Ljava/lang/String;)V"

Jihuo::Jihuo()
{
    ispop = false;
}

bool Jihuo::init()
{
    Game::instance()->setJihuolayer(this);
    bg = CCSprite::create("libao/jihuo.png");
    this->addChild(bg);
    bg->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
    bg->setScale(1.2f);
    xiaocha = CCMenuItemImage::create("libao/xx.png", "libao/xx1.png",this,menu_selector(Jihuo::resume));
    goumai = CCMenuItemImage::create("libao/jihuogoumai.png", "libao/jihuogoumai1.png",this,menu_selector(Jihuo::buy));
    CCMenu* menu = CCMenu::create();
    this->addChild(menu);
    menu->setPosition(0, 0);
    menu->addChild(xiaocha);
    xiaocha->setScale(1.5f);
    xiaocha->setPosition(ccp(SIZE.width*0.21, SIZE.height*0.74));
    menu->addChild(goumai);
    goumai->setPosition(ccp(SIZE.width*0.48, SIZE.height*0.28));
    this->scheduleUpdate();
    return true;
}

CCScene* Jihuo::scene(CCRenderTexture *sqr, bool isFlip )
{
    CCScene *scene = CCScene::create();
    Jihuo* layer = Jihuo::create();
    scene->addChild(layer,100);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
    _spr->setPosition(ccp(size.width / 2, size.height / 2));
    _spr->setFlipY(true);  //是否翻转
    _spr->setColor(ccGRAY);  //颜色（变灰暗）
    scene->addChild(_spr);
    return scene;
}

void Jihuo::showInfo(int id)
{
	CCString* str = CCString::createWithFormat("%d", id);
	openalertJni::payRequest(str->getCString());
}

void Jihuo::buy(CCObject* )
{
    showInfo(BUY_Jihuolayer);
}

void Jihuo::resume(CCObject* )
{
    PersonalAudioEngine::sharedEngine()->playEffect("music/backSound.wav");
    CCDirector::sharedDirector()->popScene();
    CCDirector::sharedDirector()->replaceScene(SelectScene::scene());
}

void Jihuo::update(float dt)
{
    if (this->ispop)
    {
        this->jihuo();
    }
}

void Jihuo::jihuo()
{
    gameLayer->juqingThreeEnd();
    Role->fuhuo();
    CCDirector::sharedDirector()->popScene();
    KingData->setIsJihuo(true);
    HUB->jihuo();
    CCUserDefault::sharedUserDefault()->setBoolForKey("isJihuo",KingData->getIsJihuo());
    CCUserDefault::sharedUserDefault()->flush();
}

