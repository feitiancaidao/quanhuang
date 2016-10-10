//
//  HubShop.cpp
//  king04
//
//  Created by mac on 14-5-15.
//
//

#include "HubShop.h"
#include "Define.h"
#include "Hero.h"
#include "Game.h"
#include "ShopScene.h"
#include "MenuLayer.h"

HubShop::HubShop()
{
    type = 1;
}
bool HubShop::init()
{
    bool bRet = false;
	do
	{
        if ( !CCLayer::init() )
        {
            return false;
        }

        this->setTouchEnabled(true);
        LeftisTouched = false;
        RightisTouched = false;
        addJoy();
        addButton();
        headUI = new PlayerHeadUI();
        headUI->bindPlayer(Role);
        this->addChild(headUI);
        headUI->setAnchorPoint(ccp(0,1));
        
        headUI->setPosition(-SIZE.width/20, SIZE.height/2+SIZE.height/30);
        
        headUI->unscheduleAllSelectors();
        
        headUI->life->setPercent(100);
        
        CCMenuItemSprite* pause = CCMenuItemSprite::create(CCSprite::create("util/zhantinganniu1.png"), CCSprite::create("util/zhantinganniu2.png"),this,menu_selector(HubShop::pause));
        CCMenu* menu = CCMenu::create();
        this->addChild(menu,1000);
        CCSize pauseSize = pause->getContentSize();
        menu->setPosition(CCPointMake(SIZE.width*9/10,SIZE.height*9/10));
        menu->addChild(pause);

        this->scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}

void HubShop::addJoy()
{
    zuo = CCSprite::create("util/gangxiangjian2.png");
    you = CCSprite::create("util/gangxiangjian2.png");
    you->setFlipX(true);
    zuo->setScale(1.3f);
    you->setScale(1.3f);
    this->addChild(zuo);
    this->addChild(you);
    zuo->setPosition(ccp(SIZE.width/7,SIZE.height/7));
    you->setPosition(ccp(SIZE.width/7 + zuo->getContentSize().width*1.7,SIZE.height/7));
}

void HubShop::pause(CCObject* )
{

    CCDirector::sharedDirector()->pushScene( MenuLayer::scene(1));
}

void HubShop::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-126,true);
}

bool HubShop::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if (this->getParent()->getChildByTag(dalibaotag)!=NULL)
    {
        return false;
    }
    
    CCPoint p  = touch->getLocation();
	ShopScene* shopScene = dynamic_cast<ShopScene*>(this->getParent());
    if (zuo->boundingBox().containsPoint(p))
    {
       // zuo->setDisplayFrame(CCSpriteFrame::create("util/gangxiangjian1.png",CCRect(0,0,zuo->getContentSize().width, zuo->getContentSize().height )));
       // zuo->setScale(1.4);
       // LeftisTouched = true;
		
		shopScene->changeSelect(0);
      //  ShopRole->orientation = LEFT;
        
    }else if (you->boundingBox().containsPoint(p))
    {
       // you->setDisplayFrame(CCSpriteFrame::create("util/gangxiangjian1.png",CCRect(0,0,zuo->getContentSize().width, zuo->getContentSize().height )));
        //you->setScale(1.4);
       // RightisTouched = true;
		shopScene->changeSelect(1);
      //  ShopRole->is_UndoRunState = true;
      //  ShopRole->orientation = RIGHT;

    }else{
      //  ShopRole->is_UndoRunState = true;
      //  ShopRole->orientation = HOLDER;
    }

    return true;
}

void HubShop::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    /*CCPoint p  = touch->getLocation();
    if (!zuo->boundingBox().containsPoint(p))
    {
        LeftisTouched = false;
    }else
    {
        LeftisTouched = true;
        if (zuo->getScale() != 1.4) {
            zuo->setScale(1.4);
        }
        you->setScale(1.0f);
    }
    if (!you->boundingBox().containsPoint(p))
    {
        RightisTouched = false;
    }else
    {
        RightisTouched = true;
        if (you->getScale() != 1.4) {
            you->setScale(1.4);
        }
        zuo->setScale(1.0f);
    }*/
}

void HubShop::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
	/*LeftisTouched = false;
	RightisTouched = false;
	zuo->setScale(1.3f);
	you->setScale(1.3f);
	ShopRole->is_UndoRunState = false;
	zuo->setDisplayFrame(CCSpriteFrame::create("util/gangxiangjian2.png",CCRect(0,0,zuo->getContentSize().width, zuo->getContentSize().height )));
	you->setDisplayFrame(CCSpriteFrame::create("util/gangxiangjian2.png",CCRect(0,0,zuo->getContentSize().width, zuo->getContentSize().height )));
	ShopRole->orientation = HOLDER;*/
}

void HubShop::update(float dt)
{
   /* if(RightisTouched)
    {
        ShopRole->is_UndoRunState = true;
        ShopRole->orientation = RIGHT;
    }else if (LeftisTouched)
    {
        ShopRole->is_UndoRunState = true;
        ShopRole->orientation = LEFT;
    }else
    {
        ShopRole->orientation = HOLDER;
        ShopRole->stand();
    }
    
    headUI->changeMoney();*/
}

void HubShop::addButton()
{
    CCSprite* spriteBase = CCSprite::create("util/gongjijian1.png");
    spriteBase->setScale(1.1f);
    CCSprite* ActivatedSprite = CCSprite::create("util/gongjijian2.png");
    ActivatedSprite->setScale(1.1f);
    CCMenu* menu = CCMenu::create();
    menu->setPosition(0, 0);
    this->addChild(menu,102);
    CCMenuItem* button = CCMenuItemSprite::create(spriteBase, ActivatedSprite, this, menu_selector(HubShop::dalibao));
    menu->addChild(button);
    button->setPosition(0.88*SIZE.width,SIZE.height/7);
}

void HubShop::dalibao(CCObject* pSender)
{
    ShopScene* shopScene = dynamic_cast<ShopScene*>(this->getParent());
    shopScene->dalibao();
}


