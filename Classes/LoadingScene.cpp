//
//  LoadingScene.cpp
//  GedouKing
//
//  Created by mac on 14-3-26.
//
//

#include "LoadingScene.h"
#include "Define.h"
#include  "MenuScene.h"
#include "SelectScene.h"

bool LoadingScene::init()
{
    if ( !BaseLayer::init() )
    {
        return false;
    }
    
    CCSprite* loading_back = CCSprite::create("loading/loading_bj.png");
    this->addChild(loading_back,-4);
    

    CCSprite* loadhei = CCSprite::create("loading/loading_jdt.png");
    CCSprite* loadhong =  CCSprite::create("loading/loading_jdt1.png");
    
    CCProgressTimer* timer = CCProgressTimer::create(loadhong);
    
    this->addChild(timer,-2);
    this->addChild(loadhei,-3);

    loading_back->setPosition(CCPoint(SIZE.width/2,SIZE.height/2));
    
    timer->setPosition(CCPoint(SIZE.width/2,SIZE.height*0.1));
    loadhei->setPosition(CCPoint(SIZE.width/2,SIZE.height*0.1));
    
    timer->setMidpoint(CCPoint(0,0.5));
    timer->setPercentage(0);
    timer->setType(kCCProgressTimerTypeBar);
    timer->setBarChangeRate(ccp(1, 0));
    CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(LoadingScene::loadingBack));
    
    CCProgressTo* progress = CCProgressTo::create(4.0f, 100.0f);
    timer->runAction(CCSequence::create(progress,callback,NULL));
    float timeLength = loadhong->getContentSize().width;
    CCSprite* fjd = CCSprite::create("loading/loading_fgd.png");
    fjd->setPosition(ccp(timer->getPositionX() - timeLength/2,timer->getPositionY()));
    this->addChild(fjd,1);
    fjd->runAction(CCMoveBy::create(4.0f, ccp(timeLength,0)));
    
    CCSprite* title = CCSprite::create("loading/loading_load.png");
    this->addChild(title);
    title->setPosition(ccp(SIZE.width/2,SIZE.height*0.2));
    
    char json[50] = {0};
    
 
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"g3","g3");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"g4","g4");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"g5","g5");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"g6","g6");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"g7","g7");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"g8","g8");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"g9","g9");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"g10","g10");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"boss1","boss1");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"boss2","boss2");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"boss3","boss3");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"boss4","boss4");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"role1","role1");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"g1","g1");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));
    
    
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"g2","g2");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(json,this,schedule_selector(LoadingScene::Loading_Over));

    return true;
}

void LoadingScene::Loading_Over(float dt)
{
    
}

void LoadingScene::loadingBack()
{
    CCScene* scene =  CCTransitionFade::create(2.0f,MenuScene::scene());
    CCDirector::sharedDirector()->replaceScene(scene);
}
cocos2d::CCScene* LoadingScene::scene()
{

    CCScene *scene = CCScene::create();

    LoadingScene *layer = LoadingScene::create();

    scene->addChild(layer);

    return scene;
}
