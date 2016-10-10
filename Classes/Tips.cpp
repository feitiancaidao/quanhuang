//
//  Tips.cpp
//  King
//
//  Created by mac on 14-4-22.
//
//

#include "Tips.h"
#include "Define.h"
static int tipsAll[] = {0,1,1,1,2,2,2 ,3,3,3,1,1,1,2,2,2};

Tips::~Tips()
{
    
}

CCScene* Tips::scene(int id)
{
    CCScene* scene = CCScene::create();
    Tips* tips = Tips::create(id);
    scene->addChild(tips);
    return scene;
}

Tips* Tips::create(int id)
{
    Tips* tips = new Tips();
    tips->autorelease();
    tips->init(id);
    return tips;
}

bool Tips::init(int id)
{
    if (!CCLayer::init())
    {
        return false;
    }
    this->setTouchEnabled(true);
    char mapchar[15] = {0};
    sprintf(mapchar, "maps/map0%d.png",tipsAll[id]);
    back = CCSprite::create(mapchar);
    this->addChild(back,-2);
    back->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));
    hero = Hero::create();
    monster = Monster::create(2, 1);
    return true;
}

void Tips::addTips(CCObject* pSender)
{
    
}