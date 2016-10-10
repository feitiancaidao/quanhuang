//
//  Card.cpp
//  king04
//
//  Created by mac on 14-5-27.
//
//

#include "Card.h"
#include "Define.h"
#include "GlobleUnits.h"
#include "TextInfos.h"
#include "GameData.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
#define ANDROID_CLASS_NAME1 "gedou/mofeng/com/king05"
#define ANDROID_FUNCTION_NAME1 "addXueTong"
//#define ANDROID_FUNCTION_NAME "charge"
#define ANDROID_PARAM_TYPE "(Ljava/lang/String;Ljava/lang/String;)V"

Card* Card::create(int id)
{
    Card* card = new Card();
    card->init(id);
    card->autorelease();
    return card;
}
bool Card::init(int id)
{
    if (!CCLayer::init())
    {
        return false;
    }
    this->id = id;
    bg = CCSprite::create(cards[id].c_str());
    this->addChild(bg);
    button = CCMenuItemImage::create("card/huodeanniu1.png", "card/huodeanniu2.png", this,menu_selector(Card::huode));
    CCMenu* menu = CCMenu::create();
    this->addChild(menu);
    menu->setPosition(ccp(0, 0));
    menu->addChild(button);
    button->setPosition(ccp(SIZE.width/2, SIZE.height*0.25));
    bg->setPosition(ccp(SIZE.width/2, SIZE.height*0.5));
    xiaocha = CCMenuItemImage::create("dalibao/x1.png", "dalibao/x2.png",this,menu_selector(Card::remove));
    menu->addChild(xiaocha);
    xiaocha->setScale(1.5f);
    xiaocha->setPosition(ccp(SIZE.width*0.77, SIZE.height*0.74));
    
    return true;
}

CCScene* Card::scene(CCRenderTexture *sqr, bool isFlip ,int id)
{
    CCScene *scene = CCScene::create();
    Card* layer = Card::create(id);
    scene->addChild(layer,100);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
    _spr->setPosition(ccp(size.width / 2, size.height / 2));
    _spr->setFlipY(true);  //是否翻转
    scene->addChild(_spr);
    return scene;
}

void Card::remove(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void Card::huode(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
    if (this->id == 0)
    {
       // showInfo(24);
		KingData->settmpshoushen(true);
    }
	else if (this->id == 1)
    {
       // showInfo(8);
		KingData->settmpbazhinv(true);
		if (HUB != NULL)
		{
			CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill2TimerTag));
			timer1->setPercentage(100);
			HUB->runSkill(2);
		}
    }
	else if (this->id == 2)
    {
       // showInfo(9);
		KingData->settmpbajiubei(true);
		if (HUB != NULL)
		{
			CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill3TimerTag));
			timer1->setPercentage(100);
			HUB->runSkill(3);
		}
    }
	else if (this->id == 3)
    {
        //showInfo(23);
		KingData->settmpjinjiDuobi(true);
		if (HUB != NULL)
		{

			CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill4TimerTag));
			timer1->setPercentage(100);
			HUB->runSkill(4);
		}
    }
}


void Card::showInfo(int id)
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    JniMethodInfo methodInfo;
//    jobject jobj;
//    bool isHave = JniHelper::getStaticMethodInfo(methodInfo, ANDROID_CLASS_NAME1,
//                                                 ANDROID_FUNCTION_NAME1,
//                                                 "(I)V");
//    if (isHave)
//    {
//        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, id);
//        
//    }else
//    {
//        
//    }
//#else
//	GlobleUnits::getInstance()->paySuccess(id);
//	CCLog("");
//#endif
}








