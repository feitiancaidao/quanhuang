//
//  TeachScene.cpp
//  King
//
//  Created by mac on 14-4-21.
//
//

#include "TeachScene.h"
#include "Define.h"
CCScene* TeachScene::scene(CCRenderTexture* text)
{
    CCScene* scene = CCScene::create();
    TeachScene* layer = TeachScene::create();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *_spr = CCSprite::createWithTexture(text->getSprite()->getTexture());
    _spr->setPosition(ccp(size.width / 2, size.height / 2));
    _spr->setFlipY(true);  //是否翻转
    _spr->setColor(ccGRAY);  //颜色（变灰暗）
    scene->addChild(layer);
    layer->addChild(_spr,-1);
    return scene;
}
bool TeachScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    CCSprite* tech = CCSprite::create("maps/tech.png");
    this->addChild(tech);
    tech->setPosition(ccp(SIZE.width/2, SIZE.height/2));
    CCMenu* menu = CCMenu::create();
    CCMenuItem* item = CCMenuItemImage::create("maps/iknow1.png", "maps/iknow.png", this, menu_selector(TeachScene::iknow));
    this->addChild(menu);
    menu->addChild(item);
    menu->setPosition(0, 0);
    item->setPosition(ccp(SIZE.width/2, 60));
    return true;
}
void TeachScene::iknow(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}