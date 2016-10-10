//
//  GameOverScene.cpp
//  King
//
//  Created by mac on 14-3-28.
//
//
#include "GameOverScene.h"
#include "Define.h"
#include "GameData.h"
#include "GuoduScene.h"
#include "Counter.h"
#include "GoldCounterLayer.h"
#include "SelectScene.h"
#include "PersonalAudioEngine.h"
#include "XMLData.h"
#include "ShopScene.h"

GameOverScene::GameOverScene()
{
    totalScore = 0;
    HeroIsDie = false;
    goldLayer  = NULL;
    goldLayer2 = NULL;
    goldLayer3 = NULL;
    goldLayer4 = NULL;
    goldLayer5 = NULL;
    jixu = NULL;
}

GameOverScene* GameOverScene::create()
{
	GameOverScene *pRet = new GameOverScene();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}
GameOverScene* GameOverScene::create(int lianji,int hpPercent,int remainTime,int guan,bool heroisDie )
{
    GameOverScene *pRet = new GameOverScene();
    if (pRet && pRet->init(lianji,hpPercent,remainTime,guan,heroisDie))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool GameOverScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if(goldLayer != NULL && menu->isVisible() )
    {
        goldLayer->setNumbet2(this->getLianji()*50);
        goldLayer2->setNumbet2(this->getHpPercent()*50);
        goldLayer3->setNumbet2(this->getRemainTime()*100);
        goldLayer4->setNumbet2(this->getTotalScore());
        if (goldLayer5!=NULL)
        {
            
            if (HeroIsDie)
            {
                goldLayer5->setNumbet2(0);
 
            }else
            {
                float jiangliRate =  powf(0.66, guanjiangli);
                int mm = (guan+1)/4;
                if (mm < 1) {
                    mm = 1;
                }
                int money = (mm)*(this->getTotalScore()/100);
                goldLayer5->setNumbet2(money*jiangliRate);
            }
        }
    }
    return false;
}


void GameOverScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-129,true);
}

void GameOverScene::callback()
{
    
    CCLayerColor* bg2 = CCLayerColor::create(ccc4(0x0c, 0x10, 0x1a, 179), SIZE.width*0.86,SIZE.height*0.73 );
    bg2->ignoreAnchorPointForPosition(false);
    this->addChild(bg2);
    bg2->setPosition(ccp(SIZE.width * 0.5,SIZE.height * 0.44));
    CCScale9Sprite* bgsprite2 = CCScale9Sprite::create("gameover/ggjm_k4.png");
    bgsprite2->setContentSize(bg2->getContentSize());
    this->addChild(bgsprite2,1000);
    bgsprite2->setPosition(bg2->getPosition());
    CCSprite* bg = CCSprite::create("gameover/ggjm_k1.png");
    bg->setPosition(ccp(SIZE.width * 0.5,SIZE.height * 0.45));
    this->addChild(bg);
    CCSprite* lbg1 = CCSprite::create("gameover/ggjm_mj.png");
    CCSprite* lbg2 = CCSprite::create("gameover/ggjm_mj.png");
    CCSprite* lbg3 = CCSprite::create("gameover/ggjm_mj.png");
    CCSprite* lbg4 = CCSprite::create("gameover/ggjm_mj.png");
    
    this->addChild(lbg1,100);
    this->addChild(lbg2,100);
    this->addChild(lbg3,100);
    this->addChild(lbg4,100);
    CCSize bgSize = bg->getContentSize();
    
    lbg1->setAnchorPoint(ccp(0,0));
    lbg2->setAnchorPoint(ccp(0,0));
    lbg3->setAnchorPoint(ccp(0,0));
    lbg4->setAnchorPoint(ccp(0,0));
    lbg1->setPosition(ccp(SIZE.width*0.2,SIZE.height*0.57));
    lbg2->setPosition(ccp(SIZE.width*0.2,SIZE.height*0.455));
    lbg3->setPosition(ccp(SIZE.width*0.2,SIZE.height*0.340));
    lbg4->setPosition(ccp(SIZE.width*0.2,SIZE.height*0.225));
    
    CCSprite* lianji = CCSprite::create("gameover/ggjm_lj.png");
    CCSprite* life = CCSprite::create("gameover/ggjm_sm.png");
    CCSprite* time = CCSprite::create("gameover/ggjm_sj.png");
    CCSprite* total = CCSprite::create("gameover/ggjm_zdf.png");
    
    lianji->setAnchorPoint(ccp(0,0));
    life->setAnchorPoint(ccp(0,0));
    time->setAnchorPoint(ccp(0,0));
    total->setAnchorPoint(ccp(0,0));
    
    lianji->setPositionX(30);
    life->setPositionX(30);
    time->setPositionX(30);
    total->setPositionX(30);
    
    lbg1->addChild(lianji);
    lbg2->addChild(life);
    lbg3->addChild(time);
    lbg4->addChild(total);
    
    CCSprite* reward = CCSprite::create("gameover/ggjm_bx.png");
    this->addChild(reward);
    reward->setPosition(ccp(SIZE.width*0.7,SIZE.height*0.48));
    
    CCSprite* rewardMoney = CCSprite::create("gameover/ggjm_jb.png");
    this->addChild(rewardMoney);
    rewardMoney->setPosition(ccp(SIZE.width*0.7,SIZE.height*0.28));
    
    jixu = CCMenuItemImage::create("gameover/ggjm_jx.png", "gameover/ggjm_jxdown.png", this, menu_selector(GameOverScene::menuCloseCallback));
    menu = CCMenu::create();
    menu->setPosition(ccp(0,0));
    this->addChild(menu);
    menu->addChild(jixu);
    menu->setVisible(false);
    
    this->runAction(CCSequence::create(CCDelayTime::create(1.2f),CCCallFunc::create(this, callfunc_selector( GameOverScene::show )),NULL));
    
    jixu->setPosition(ccp(SIZE.width/2,SIZE.height*0.14));
    
    goldLayer = GoldCounterLayer::create(this->getLianji()*50);
    lbg1->addChild(goldLayer,1000);
    goldLayer->setPosition(ccp(150,20));
    
    
    int hpp = this->getHpPercent();
    if (this->getHpPercent() == 0) {
        hpp = 0;
    }
    
    int hpTole =hpp *50;
    goldLayer2 = GoldCounterLayer::create(hpTole);
    lbg2->addChild(goldLayer2,1500);
    goldLayer2->setPosition(ccp(150,20));
    
    goldLayer3 = GoldCounterLayer::create(this->getRemainTime()*100);
    lbg3->addChild(goldLayer3,1001);
    goldLayer3->setPosition(ccp(150,20));
    
    goldLayer4 = GoldCounterLayer::create(this->getTotalScore());
    lbg4->addChild(goldLayer4,1000);
    goldLayer4->setPosition(ccp(160,20));
    
    if (HeroIsDie)
    {
        goldLayer5 = GoldCounterLayer::create(0);
        rewardMoney->addChild(goldLayer5,1000);
        goldLayer5->setPosition(ccp(70,25));
    }else
    {
         float jiangliRate =  powf(0.66, guanjiangli);
        int mm = (guan+1)/4;
        if (mm<1) {
            mm = 1;
        }
        int money = jiangliRate*mm*(this->getTotalScore()/100);
        goldLayer5 = GoldCounterLayer::create(money);
        rewardMoney->addChild(goldLayer5,1000);
        goldLayer5->setPosition(ccp(70,25));
        KingData->alterMoney((mm)*(totalScore/100));
    }

	CCLog("%s", "gameover end");
}

void GameOverScene::show()
{
    menu->setVisible(true);
}


void GameOverScene::setNumber(int number, int ceiling)
{
    number = MIN(ceiling, number);
    number = MAX(number, 0);
    for(int i = 0 ;i < 6;i++)
    {
        Counter* counter = (Counter*)this->getChildByTag(i);
        int digit = number / (int)(pow(10.0, 6-i-1)) % 10;
        counter->setDigit(digit);
    }
}

bool GameOverScene::init(int lianji,int hpPercent,int remainTime,int guan,bool heroisDie )
{
	CCLog("%s", "GameOverScene init");
	CCLog("init infos lianji %d, hpPercent %d,remainTime %d,guan %d", lianji, hpPercent, remainTime, guan);
	bool bRet = false;
    do
    {
        if(!BaseLayer::init())
        {
            return false;
        }
        PersonalAudioEngine::sharedEngine()->playBackgroundMusic("music/gameover.mp3",true);
        this->HeroIsDie = heroisDie;
        this->guan = guan;
    
        this->setLianji(lianji);
        this->setHpPercent(hpPercent);
        
        if (!heroisDie)
        {
            this->setRemainTime(remainTime);
        }else
        {
            this->setRemainTime(remainTime/5);
        }
    
        totalScore = this->getLianji()*50 + this->getHpPercent()*50 + this->getRemainTime()*100;
        
		CCLog("%s", "GameOverScene start use XML");
        XMLData* xmlData = XMLData::sharedXMLData();
        int score = xmlData->getScore(guan-1);
        int times = xmlData->getTimes(guan-1);
        if (totalScore>score)
        {
            xmlData->update(guan-1, totalScore,times+1);
        }else
        {
            xmlData->update(guan-1, score,times+1);
        }
        
        this->guanjiangli = times;

        
        this->setTouchEnabled(true);
        CCLayerColor* colorBackground1 = CCLayerColor::create(ccc4(0, 0, 0, 100),SIZE.width*0.5,SIZE.height);
        CCLayerColor* colorBackground2 = CCLayerColor::create(ccc4(0, 0, 0, 100),SIZE.width*0.5,SIZE.height);
        this->addChild(colorBackground1);
        this->addChild(colorBackground2);
        colorBackground1->setAnchorPoint(ccp(0,0));
        colorBackground2->setAnchorPoint(ccp(0,0));
        colorBackground1->ignoreAnchorPointForPosition(false);
        colorBackground2->ignoreAnchorPointForPosition(false);
        colorBackground1->setPosition(ccp(-SIZE.width/2,0));
        colorBackground2->setPosition(ccp(SIZE.width,0));
        colorBackground1->runAction(CCSequence::create(CCEaseIn::create(CCMoveBy::create(1.5, ccp(SIZE.width/2,0)), 2.0) ,NULL));
        colorBackground2->runAction(CCSequence::create( CCEaseIn::create(CCMoveBy::create(1.5, ccp(-SIZE.width/2,0)), 2.0),CCCallFunc::create(this,callfunc_selector(GameOverScene::callback)),NULL));
        CCSprite* gongxitongguan;
        if(heroisDie == false)
        {
             gongxitongguan = CCSprite::create("gameover/ggjm_gxtg.png");
          
        }else
        {
             gongxitongguan = CCSprite::create("gameover/fail.png");
        }
        this->addChild(gongxitongguan,100);
        gongxitongguan->setPosition(ccp(SIZE.width/2,SIZE.height*0.6));
        gongxitongguan->setScale(4.0f);
        gongxitongguan->runAction(CCScaleBy::create(1, 0.25));
        gongxitongguan->runAction(CCMoveTo::create(1, ccp(SIZE.width/2,SIZE.height*0.87)));
        bRet = true;
    } while (0);
	CCLog("%s", "GameOverScene init end");
    return bRet;
}

bool GameOverScene::init()
{
	bool bRet = false;
    do
    {
        if(!BaseLayer::init())
        {
            return false;
        }
        CCSprite* bg = CCSprite::create("UI/gg2.png");
        bg->setPosition(ccp(SIZE.width * 0.5,SIZE.height * 0.5));
        this->addChild(bg);
        bRet = true;
    } while (0);
    return bRet;
}

void GameOverScene::alertData()  //增加一关
{
    if(HeroIsDie == false)
    {
        KingData->alertMapIndex(1);
    }
}


CCScene* GameOverScene::scene()
{
    CCScene *scene = CCScene::create();
    GameOverScene *layer = GameOverScene::create();
    scene->addChild(layer,0);
    return scene;
}

CCScene* GameOverScene::scene(int lianji,int hpPercent,int remainTime,int guan,CCRenderTexture* tx,bool heroisDie )
{
    CCScene *scene = CCScene::create();
    GameOverScene *layer = GameOverScene::create(lianji,hpPercent,remainTime,guan,heroisDie);
    scene->addChild(layer,0);
    CCSprite *_spr = CCSprite::createWithTexture(tx->getSprite()->getTexture());
    _spr->setPosition(ccp(SIZE.width / 2, SIZE.height / 2));
    _spr->setFlipY(true);  //是否翻转
    _spr->setColor(ccGRAY);  //颜色（变灰暗）
    scene->addChild(_spr,-1);
    return scene;
}

void GameOverScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->purgeCachedData();
   // CCDirector::sharedDirector()->replaceScene(ShopScene::scene());
	CCDirector::sharedDirector()->replaceScene(SelectScene::scene());
}