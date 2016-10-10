//
//  ShopBuy2.cpp
//  king04
//
//  Created by mac on 14-5-12.
//
//

#include "ShopBuy2.h"
#include "Define.h"
#include "GlobleUnits.h"
#include "openalertJni.h"
#include "TextInfos.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
#define ANDROID_CLASS_NAME1 "gedou/mofeng/com/king05"
#define ANDROID_FUNCTION_NAME1 "addXueTong"
//#define ANDROID_FUNCTION_NAME "charge"
#define ANDROID_PARAM_TYPE "(Ljava/lang/String;Ljava/lang/String;)V"

ShopBuy2::ShopBuy2()
{
    
}

bool ShopBuy2::init()
{
    bg = CCSprite::create("libao/dalibao.png");
    this->addChild(bg);
    bg->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
    bg->setScale(1.2f);
    xiaocha = CCMenuItemImage::create("libao/xxx.png", "libao/xxx1.png",this,menu_selector(ShopBuy2::resume));
    goumai = CCMenuItemImage::create("libao/goumai.png", "libao/goumai1.png",this,menu_selector(ShopBuy2::buy));
    CCMenu* menu = CCMenu::create();
    this->addChild(menu);
    menu->setPosition(0, 0);
    menu->addChild(xiaocha);
    xiaocha->setScale(1.5f);
    xiaocha->setPosition(ccp(SIZE.width*0.21, SIZE.height*0.74));
    menu->addChild(goumai);
    goumai->setPosition(ccp(SIZE.width*0.38, SIZE.height*0.28));
    return true;
}

CCScene* ShopBuy2::scene(CCRenderTexture *sqr, bool isFlip )
{
    CCScene *scene = CCScene::create();
    ShopBuy2* layer = ShopBuy2::create();
    scene->addChild(layer,100);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
    _spr->setPosition(ccp(size.width / 2, size.height / 2));
    _spr->setFlipY(true);  //是否翻转
    _spr->setColor(ccGRAY);  //颜色（变灰暗）
    scene->addChild(_spr);
    return scene;
}

void ShopBuy2::showInfo(int id)
{
	CCString* str = CCString::createWithFormat("%d", id);
	openalertJni::payRequest(str->getCString());

}

void ShopBuy2::buy(CCObject* )
{
	showInfo(BUY_Dalibao);
}

void ShopBuy2::resume(CCObject* )
{
   
    PersonalAudioEngine::sharedEngine()->playEffect("music/backSound.wav");
    CCDirector::sharedDirector()->popScene();
}