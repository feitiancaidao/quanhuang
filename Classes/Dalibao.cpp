//
//  Dalibao.cpp
//  king04
//
//  Created by mac on 14-5-18.
//
//

#include "Dalibao.h"
#include "Define.h"
#include "GameData.h"
#include "HubLayer.h"
#include "Hero.h"
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



#include "GlobleUnits.h"

Dalibao* Dalibao::create(int id)
{
    Dalibao* libao = new Dalibao();
    libao->init(id);
    libao->autorelease();
    return libao;
}

bool Dalibao::init(int id)
{
    this->id = id;
    switch (id) {
        case 0:
        {
            bg = CCSprite::create("dalibao/dalibao.png");
            this->addChild(bg);
            bg->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
            xiaocha = CCMenuItemImage::create("dalibao/x1.png", "dalibao/x2.png",this,menu_selector(Dalibao::resume));
            goumai = CCMenuItemImage::create("dalibao/goumai.png", "dalibao/goumai2.png",this,menu_selector(Dalibao::buy));
            CCMenu* menu = CCMenu::create();
            this->addChild(menu);
            menu->setPosition(0, 0);
            menu->addChild(xiaocha);
            xiaocha->setScale(1.5f);
            xiaocha->setPosition(ccp(SIZE.width*0.78, SIZE.height*0.72));
            menu->addChild(goumai);
            goumai->setPosition(ccp(SIZE.width*0.50, SIZE.height*0.255));

        }
        break;
            
        case 1:
        {
            this->id = 1888;
            bg = CCSprite::create("dalibao/huodejinbitu.png");
            this->addChild(bg);
            bg->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
            xiaocha = CCMenuItemImage::create("dalibao/x1.png", "dalibao/x2.png",this,menu_selector(Dalibao::resume));
            goumai = CCMenuItemImage::create("dalibao/goumai.png", "dalibao/goumai2.png",this,menu_selector(Dalibao::buy));
            CCMenu* menu = CCMenu::create();
            this->addChild(menu);
            menu->setPosition(0, 0);
            menu->addChild(xiaocha);
            xiaocha->setScale(1.5f);
            xiaocha->setPosition(ccp(SIZE.width*0.78, SIZE.height*0.72));
            menu->addChild(goumai);
            goumai->setPosition(ccp(SIZE.width*0.50, SIZE.height*0.255));
            
            menu5888 = CCMenuItemImage::create("dalibao/5888jin.png", "dalibao/5888jin.png",this,menu_selector(Dalibao::jinbi));
            menu2888 = CCMenuItemImage::create("dalibao/2888jin.png", "dalibao/2888jin.png",this,menu_selector(Dalibao::jinbi));
            menu1888 = CCMenuItemImage::create("dalibao/1888jin.png", "dalibao/1888jin.png",this,menu_selector(Dalibao::jinbi));
            
            menu->addChild(menu1888);
            menu->addChild(menu2888);
            menu->addChild(menu5888);
            menu5888->setTag(2);
            menu1888->setTag(0);
            menu2888->setTag(1);
            menu1888->setPosition(SIZE.width*0.30, SIZE.height*0.46);
            menu2888->setPosition(SIZE.width*0.50, SIZE.height*0.46);
            menu5888->setPosition(SIZE.width*0.70, SIZE.height*0.46);
            xuanzekuang = CCSprite::create("dalibao/xuanzhongkuang.png");
            xuanzekuang->setPosition(ccpAdd( menu1888->getPosition(), ccp(0, 26)));
            this->addChild(xuanzekuang);
            xuanzekuang->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
            xuanzekuang->setScale(1.1f);
        }
            break;
        case 2:
        {
            bg = CCSprite::create("dalibao/lingqujinenegde.png");
            this->addChild(bg);
            bg->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
            xiaocha = CCMenuItemImage::create("dalibao/x1.png", "dalibao/x2.png",this,menu_selector(Dalibao::resume));
            goumai = CCMenuItemImage::create("dalibao/goumai.png", "dalibao/goumai2.png",this,menu_selector(Dalibao::buy));
            touming = CCSprite::create("dalibao/toumingde.png");
            touming2 = CCSprite::create("dalibao/toumingde.png");
            xuanzekuang = CCSprite::create("dalibao/xuanzhongkuang.png");
            duobi = CCMenuItemImage::create("dalibao/jineng11.png", "dalibao/jineng11.png",this,menu_selector(Dalibao::duobiMenu));
            shoushen = CCMenuItemImage::create("dalibao/jineng255.png", "dalibao/jineng255.png",this,menu_selector(Dalibao::shoushenMenu));
            
            CCMenu* menu = CCMenu::create();
            this->addChild(menu,2);
            menu->setPosition(0, 0);
            menu->addChild(xiaocha);
            xiaocha->setScale(1.5f);
            xiaocha->setPosition(ccp(SIZE.width*0.78, SIZE.height*0.72));
            menu->addChild(goumai);
            goumai->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.26));
            
            this->addChild(touming);
            this->addChild(touming2);
            this->addChild(xuanzekuang);
            menu->addChild(duobi,2);
            menu->addChild(shoushen,2);
            
            duobi->setPosition(ccp(SIZE.width*0.35, SIZE.height*0.48));
            shoushen->setPosition(ccp(SIZE.width*0.7, SIZE.height*0.48));
            xuanzekuang->setPosition(ccpAdd( duobi->getPosition(), ccp(-20,50)));
            xuanzekuang->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
        
            touming->setScale(1.5f);
            touming2->setScale(1.5f);
            
            this->id = 1000;   //躲避
            
            if (KingData->getJinjiDuobi() && KingData->getShoushen())
            {
                xuanzekuang->stopAllActions();
                xuanzekuang->setVisible(false);
                touming->setPosition(ccpAdd(shoushen->getPosition(),ccp(-12,50)));
                touming2->setPosition(ccpAdd(duobi->getPosition(),ccp(-12,50)));
                this->id = 3000;  //躲避
            }else
            {
                if (KingData->getJinjiDuobi())
                {
                    
                    touming->setPosition(ccpAdd(duobi->getPosition(),ccp(-12,50)));
                    xuanzekuang->setPosition(ccpAdd( shoushen->getPosition(), ccp(-12,50)));
                    this->id = 2000;  //瘦身
                }else
                {
                    touming->setVisible(false);
                }
                if (KingData->getShoushen())
                {
                    touming2->setPosition(ccpAdd(shoushen->getPosition(),ccp(-12,50)));
                    xuanzekuang->setPosition(ccpAdd( duobi->getPosition(), ccp(-12,50)));
                    this->id = 1000;  //躲避
                }else
                {
                    touming2->setVisible(false);
                }
            }
            libaoid = 1;
        }
            break;
        default:
            break;
    }
    return true;
}

void Dalibao::jinbi(CCObject* pSender)
{
    CCMenuItem* item = dynamic_cast<CCMenuItem*>(pSender);
    int tag = item->getTag();
    if (tag == 0)
    {
        this->id = 1888;
        xuanzekuang->setPosition(ccpAdd( menu1888->getPosition(), ccp(0, 26)));
    }else if (tag == 1)
    {
        this->id = 2888;
        xuanzekuang->setPosition(ccpAdd( menu2888->getPosition(), ccp(-2, 26)));
    }else if (tag == 2)
    {
        this->id = 5888;
        xuanzekuang->setPosition(ccpAdd( menu5888->getPosition(), ccp(-5, 26)));
    }
}


void Dalibao::duobiMenu(CCObject*)
{
    
    if (KingData->getJinjiDuobi() && KingData->getShoushen())
    {
        this->removeFromParent();
		showInfo(BUY_JinjiDuobi);
        return;
    }
    if (KingData->getJinjiDuobi())
    {
        touming->setPosition(ccpAdd(shoushen->getPosition(),ccp(-12,50)));
        xuanzekuang->setPosition(ccpAdd( shoushen->getPosition(), ccp(-12,50)));
        this->id = 2000;  //瘦身
    }else
    {
        xuanzekuang->setPosition(ccpAdd( duobi->getPosition(), ccp(-12,50)));
        this->id = 1000;  //shoushen
        touming->setVisible(false);
    }

}

void Dalibao::shoushenMenu(CCObject*)
{
    if (KingData->getJinjiDuobi() && KingData->getShoushen())
    {
        this->removeFromParent();
		showInfo(BUY_Shoushen);
        return;
    }
    if (KingData->getShoushen())
    {
        touming2->setPosition(ccpAdd(duobi->getPosition(),ccp(-12,50)));
        xuanzekuang->setPosition(ccpAdd( duobi->getPosition(), ccp(-12,50)));
        this->id = 1000;  //躲避
        return;
    }else
    {
        xuanzekuang->setPosition(ccpAdd( shoushen->getPosition(), ccp(-12,50)));
        this->id = 2000;  //shoushen
        touming2->setVisible(false);
    }
}


CCScene* Dalibao::scene(int id)
{
    CCScene *scene = CCScene::create();
    Dalibao* layer = Dalibao::create(id);
    scene->addChild(layer,100);
    return scene;
}

void Dalibao::showInfo(int id)
{
	CCString *str = CCString::createWithFormat("%d", id);
	openalertJni::payRequest(str->getCString());
}

void Dalibao::buy(CCObject*)
{
    switch (id) {
        case 0:
        {
            showInfo(16);
        }
            break;
        case 1:
        {
            showInfo(21);
        }
            break;
        case 2:
        {
            showInfo(22);
        }
            break;
        case 1888:
        {
            showInfo(25);
        }
            break;
        case 2888:
        {
            showInfo(26);
        }
            break;
        case 5888:
        {
            showInfo(27);
        }
            break;
            
        case 1000:
        {
            showInfo(23);
        }
            break;
        case 2000:
        {
             showInfo(99);
        }
            break;
        case 3000:
        {
            showInfo(28);
        }
            break;
            
        default:
            break;
    }
    this->removeFromParent();
}

void Dalibao::resume(CCObject*)
{
    PersonalAudioEngine::sharedEngine()->playEffect("music/backSound.wav");
    this->removeFromParent();
}


