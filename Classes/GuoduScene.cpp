//
//  GuoduScene.cpp
//  King
//
//  Created by mac on 14-4-18.
//
//

#include "GuoduScene.h"
#include "GameScene.h"
#include "SelectScene.h"
GuoduScene* GuoduScene::create(int guodu)
{
    GuoduScene* SCENE = new GuoduScene();
    SCENE->init(guodu);
    SCENE->autorelease();
    return SCENE;
}

bool GuoduScene::init(int guodu)
{
    CCLayer* layer = CCLayer::create();
    this->addChild(layer);
    this->guodu = guodu;
    this->scheduleOnce(schedule_selector(GuoduScene::yanchi), 0.02f);
    return true;
}
void GuoduScene::yanchi(float dt)
{
    CCDirector::sharedDirector()->replaceScene( SelectScene::scene());

}