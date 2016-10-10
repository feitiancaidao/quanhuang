//
//  AboutScene.cpp
//  King
//
//  Created by mac on 14-3-26.
//
//

#include "AboutScene.h"
#include "Define.h"
#include "MenuScene.h"
#include "XXIconv.h"

bool AboutScene::init()
{
    if ( !BaseLayer::init() )
    {
        return false;
    }
    CCSprite* about = CCSprite::create("UI/guanyu.png");
    this->addChild(about,-1);
    about->setPosition(CCPoint(SIZE.width/2,SIZE.height/2));
    CCMenu* menu = CCMenu::create();
    
    
    CCSprite* back = CCSprite::create();
    UILabel* backI = UILabel::create();
    backI->setText(XXIconv::GBK2UTF("返回"));
    backI->setFontSize(30);
    backI->setTextHorizontalAlignment(kCCTextAlignmentCenter);
    backI->setAnchorPoint(ccp(0.5, 0.5));
    backI->setColor(ccc3(0, 0, 0));
    back->addChild(backI);
    back->setContentSize(CCSize(180,50));
 
    CCMenuItem* beginItem = CCMenuItemSprite::create(back, back, this, menu_selector(AboutScene::Return));
    menu->addChild(beginItem,2);
    beginItem->setPosition(CCPoint(7*SIZE.width/8 + 90,SIZE.height/6 - 25));
    
    this->addChild(menu);
    menu->setPosition(ccp(0,0));
    return true;
}

void AboutScene::Return(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}

cocos2d::CCScene* AboutScene::scene()
{
    CCScene *scene = CCScene::create();
    
    AboutScene *layer = AboutScene::create();
    
    scene->addChild(layer);
    
    return scene;
}




