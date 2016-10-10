//
//  HubLayer.cpp
//  King
//
//  Created by mac on 14-3-26.
//
//

#include  "HubLayer.h"
#include "Define.h"
#include "MakeNumbers.h"
#include "Flower.h"
#include "GameData.h"
#include "ShopBuy.h"
#include "XXIconv.h"
#include "TextInfos.h"

HubLayer::HubLayer()
{
    isTishinuqi1 = false;
    labelnuqi = NULL;
    tishiNuqiSprite = NULL;
    type = 0;
}
bool HubLayer::init(){
    bool bRet = false;
	do
	{
        if ( !CCLayer::init() )
        {
            return false;
        }
    
        tip1 = CCSprite::create("duihuakuang/UI80.png");
        jiaoshi = CCSprite::create("duihuakuang/jiaoshi.png");
        this->addChild(jiaoshi,9999999);
        this->addChild(tip1,999999);
        jiaoshi->setPosition(ccp(-0.15*SIZE.width,10));
        jiaoshi->setAnchorPoint(ccp(0.5, 0));
        tip1->setPosition(ccp( -150, -120));
        label = UILabel::create();
        tip1->addChild(label);
        label->setFontName("宋体");
        label->setFontSize(20);
        label->setPosition(ccp(120, tip1->getContentSize().height));
        label->setAnchorPoint(ccp(0, 1));
        label->setColor(ccc3(241, 191, 194));
        label->setTextAreaSize(CCSize(200,150));
        tip1->setVisible(false);
        jiaoshi->setVisible(false);
        label->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
        
        
        canTouch = true;
        teachID = 0;
        isTeach = false;
        
        zhishiWaitTime = 90;
        this->setTouchEnabled(true);
        //bug
        lastzuoTime = LONG_MAX;
        
        lastyouTime = LONG_MAX;
        
        LeftisTouched = false;
        
        RightisTouched = false;

        zhishi = false;
        
        addJoy();
        
        addButton();
        
        headUI = new PlayerHeadUI();
        
        headUI->bindPlayer(Role);
        
        this->addChild(headUI);
        
        headUI->setAnchorPoint(ccp(0,1));
        
        headUI->setPosition(-SIZE.width/20, SIZE.height/2+SIZE.height/30);
        
        jinengban();
    
        goSprite1 = CCSprite::create("UI/qtsz_fxj.png");
        goSprite1->setFlipX(true);
        goSprite2 = CCSprite::create("UI/qtsz_fxj.png");
        
        goSprite1->setPosition(ccp(SIZE.width/10,7*SIZE.height/10));
        goSprite2->setPosition(ccp(9*SIZE.width/10,7*SIZE.height/10));
        
        addChild(goSprite1);
        addChild(goSprite2);
        
        goSprite1->setVisible(false);
        goSprite2->setVisible(false);
        
        CCMenuItemSprite* pause = CCMenuItemSprite::create(CCSprite::create("util/zhantinganniu1.png"), CCSprite::create("util/zhantinganniu2.png"),this,menu_selector(GameScene::pause));
        CCMenu* menu = CCMenu::create();
        this->addChild(menu,1000);
        CCSize pauseSize = pause->getContentSize();
        menu->setPosition(CCPointMake(SIZE.width*9/10,SIZE.height*9/10));
        
        CCMenuItemSprite* shop = CCMenuItemSprite::create(CCSprite::create("res/select/shangcheng1.png"), CCSprite::create("res/select/shangcheng2.png"),this,menu_selector(GameScene::shop));
        menu->addChild(pause);
        menu->addChild(shop);
        shop->setPositionX(-1.5*shop->getContentSize().width);
        
        sprite = CCSprite::create("help11.png");
        sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.2f, ccp(0, 50)),CCMoveBy::create(0.2f, ccp(0, -50)),NULL)));
        this->addChild(sprite, 9898);
        sprite->setVisible(false);
        
        juqingTishiLabel = UILabel::create();
        juqingTishiLabel->setColor(ccc3(0xff, 0xae, 0x00));
        juqingTishiLabel->setFontSize(32);
        juqingTishiLabel->setFontName("宋体");
        juqingTishiLabel->setPosition(ccp(SIZE.width/2, SIZE.height/2));
        this->addChild(juqingTishiLabel);
        juqingTishiLabel->setVisible(false);
        
        this->scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}


void HubLayer::addTip(std::string text)
{
    jiaoshi->setFlipX(false);
    tip1->runAction(CCMoveTo::create(0.2f, ccp(210,70)));
    jiaoshi->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.085, 2))
                                          ,NULL ));
    
    label->setPosition(ccp(220, tip1->getContentSize().height));
    tip1->setVisible(true);
    jiaoshi->setVisible(true);
    label->setText(XXIconv::GBK2UTF(text.c_str()));
}

void HubLayer::addTip2(std::string text)
{
    jiaoshi->setVisible(false);
    tip1->setVisible(false);
    jiaoshi->setPosition(ccp(1.15*SIZE.width,10));
    tip1->setPosition(ccp( SIZE.width+150, -120));
    tip1->setVisible(true);
    jiaoshi->setVisible(true);
    jiaoshi->setFlipX(true);
    label->setPosition(ccp(100, tip1->getContentSize().height));
    tip1->runAction(CCMoveTo::create(0.2f, ccp(SIZE.width-210,70)));
    jiaoshi->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width-SIZE.width*0.085, 2))
                                          ,NULL ));

    label->setText(XXIconv::GBK2UTF(text.c_str()));
}


void HubLayer::resetTip()
{
    tip1->setVisible(false);
    jiaoshi->setVisible(false);
    label->setText("");
    jiaoshi->setPosition(ccp(-0.15*SIZE.width,10));
    tip1->setPosition(ccp( -150, -120));
}

void HubLayer::readygo(float dt)
{
    resetTip();
}

void HubLayer::update(float dt)
{
    if (this->isTeach)
    {
        if (this->teachID == 0 )
        {
           if(Role->getPositionX() > gameLayer->jiaodiTishi->getPositionX()-50)
           {
               gameLayer->jiaodiTishi->removeFromParent();
               this->teachID = 1;
           }
        }
        if (this->teachID == 0 && zhishi == false)
        {

            addTip2(TIP[0]);
            
            zhishi = true;
            sprite->setVisible(true);
            sprite->setPosition(ccp(SIZE.width*0.30, SIZE.height*0.28));
        }else if(this->teachID == 1)
        {
            resetTip();
            zhishiWaitTime--;
            if (zhishiWaitTime <= 0)
            {
                zhishiWaitTime = 90;
                this->teachID = 2;
            }
            zhishi = false;
            sprite->setVisible(false);
        }else if (this->teachID == 2 && zhishi == false)
        {
            addTip(TIP[1]);
            sprite->setVisible(true);
            sprite->setPosition(ccp(SIZE.width*0.90, SIZE.height*0.25));
            zhishi = true;
        }else if(this->teachID == 3)
        {
            resetTip();
            zhishiWaitTime--;
            if (zhishiWaitTime <= 0)
            {
                zhishiWaitTime = 40;
                this->teachID = 4;
            }
            zhishi = false;
            sprite->setVisible(false);
        }else if (this->teachID == 4  && zhishi == false)
        {
            addTip(TIP[2]);
            zhishi = true;
            sprite->setVisible(true);
            sprite->setPosition(ccp(SIZE.width*0.735, SIZE.height*0.25));
        }else if(this->teachID == 5)
        {
            Role->pauseSchedulerAndActions();
            zhishi = false;
            resetTip();
            addTip(TIP[3]);
            sprite->setPosition(ccp(SIZE.width*0.90, SIZE.height*0.25));
            this->teachID = 6;
        }else if(this->teachID == 6)
        {
            
        }
        else if(this->teachID == 7)
        {
            Role->resumeSchedulerAndActions();
            zhishi = false;
        }
        else if(this->teachID == 8)
        {
            zhishiWaitTime--;
            if (zhishiWaitTime <= 0)
            {
                zhishiWaitTime = 40;
                this->teachID = 9;
            }
            addTip(TIP[4]);
            KingData->setMoney(500);
        }else if(this->teachID == 9)
        {
     
            this->isTeach = false;
            this->scheduleOnce(schedule_selector(HubLayer::readygo), 0.6f);
            gameLayer->scheduleOnce(schedule_selector(GameScene::readyGo), 0.6f);
        }
        
    }else
    {
        sprite->setVisible(false);
    }
    if(!Role->isBeAttack && !Role->isDie)
    {
        if(RightisTouched)
        {
            Role->is_UndoRunState = true;
            Role->orientation = RIGHT;
        }else if (LeftisTouched)
        {
            Role->is_UndoRunState = true;
            Role->orientation = LEFT;
        }
    }
    
    if (Role->isdaodiqishen)
    {
        Role->orientation = HOLDER;
    }
    
    addGoInfo();
}

void HubLayer::tishiNuqi()
{
    isTishinuqi1 = true;
    canTouch = false;
    tishiNuqiSprite = CCSprite::create("help11.png");
    tishiNuqiSprite->setScale(0.4f);
    addChild(tishiNuqiSprite,90909);
    tishiNuqiSprite->setRotation(225);
    tishiNuqiSprite->setTag(8989889);
    tishiNuqiSprite->setPosition(ccp(SIZE.width*0.43, SIZE.height*0.74));
    tishiNuqiSprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, 30)),CCMoveBy::create(0.3f, ccp(0, -30)),NULL)));
    
//    labelnuqi = UILabel::create();
//    labelnuqi->setFontSize(25);
//    labelnuqi->setColor(ccc3(0xff, 0xae, 0x00));
//    labelnuqi->setText("没有怒气是无法释放技能的哦");
//    addChild(labelnuqi,11,9900);
//    labelnuqi->setPosition(ccp(SIZE.width*0.4, SIZE.height*0.65));
    resetTip();
    addTip(TIP[5]);
    
}

void HubLayer::tishiNuqi2(float dt)
{
    resetTip();
    addTip(TIP[6]);
    tishiNuqiSprite->setPosition(ccp(SIZE.width*0.79, SIZE.height*0.84));
}

void HubLayer::removetishiNuqi(float dt)
{
    this->canTouch = true;
    if (labelnuqi!=NULL)
    {
         labelnuqi->removeFromParent();
    }
    if (tishiNuqiSprite !=NULL)
    {
         tishiNuqiSprite->removeFromParent();
    }
    gameLayer->resume1();
}

void HubLayer::removetishiNuqi1()
{
    tishiNuqiSprite->setPosition(ccp(SIZE.width*0.43, SIZE.height*0.77));
    this->scheduleOnce(schedule_selector(HubLayer::removetishiNuqi), 1.2f);
    resetTip();
    addTip(TIP[7]);
    this->scheduleOnce(schedule_selector(HubLayer::readygo), 1.6f);
}

void HubLayer::addGoInfo()
{
    bool isUnsee = true;
    CCObject* obj;
    int minDistance = 10000;
    int goDirection = 0;
    CCARRAY_FOREACH(gameLayer->npc, obj)
    {
        Monster* monster = dynamic_cast<Monster*>(obj);
        CCPoint position = monster->getPosition();
        CCPoint worldposition =gameLayer->convertToWorldSpace(position);
        if(worldposition.x>0&&worldposition.x<SIZE.width)
        {
            goDirection = 0;   //不显示go信息
            isUnsee = false;
            break;
        }
        if(position.x<300 || position.x>gameLayer->bg1->getContentSize().width-300)
        {
          
        }
        else if(abs(int(monster->getPositionX()-Role->getPositionX())) < minDistance)
        {
            minDistance = abs(int(monster->getPositionX()-Role->getPositionX()));
            if(monster->getPositionX()-Role->getPositionX() < 0 && position.x >100)
            {
                goDirection = -1;    //左边显示go信息
            }else if(monster->getPositionX()-Role->getPositionX() > 0  && position.x < gameLayer->bg1->getContentSize().width-300)
            {
                goDirection = 1;    //右边显示go信息
            }
        }
    }
    showGoInfo(goDirection);
}

void HubLayer::showGoInfo(int goDirection)
{
    switch (goDirection)
    {
        case -1:
        {
            if (goSprite1->isVisible() == false && gameLayer->modeID != 3)
            {
                goSprite1->setVisible(true);
                goSprite1->runAction(CCRepeatForever::create(CCSequence::create(CCShow::create(),CCFadeOut::create(1.0f),NULL)));
            }

            goSprite2->setVisible(false);
            break;
        }
        case 1:
        {
            if (goSprite2->isVisible() == false)
            {
                goSprite2->setVisible(true);
                goSprite2->runAction(CCRepeatForever::create(CCSequence::create(CCShow::create(),CCFadeOut::create(1.0f),NULL)));
            }
            goSprite1->setVisible(false);
            break;
        }
        case 0 :
        {
            goSprite1->setVisible(false);
            goSprite2->setVisible(false);
            break;
        }
    }
}

void HubLayer::shop(CCObject* pSender)
{
    ShopBuy::isShowFuhuo();
}

void HubLayer::addButton()
{
    SneakyButtonSkinnedBase *attackButtonBase = new SneakyButtonSkinnedBase();
    attackButtonBase->autorelease();
    attackButtonBase->init();
    CCSprite* spriteBase = CCSprite::create("util/gongjijian1.png");
    attackButtonBase->setDefaultSprite(spriteBase);
    CCSprite* ActivatedSprite = CCSprite::create("util/gongjijian2.png");
    ActivatedSprite->setScale(1.3f);
    CCSprite* ActivatedSprite2 = CCSprite::create("util/gongjijian2.png");
    ActivatedSprite2->setScale(1.3f);
    attackButtonBase->setActivatedSprite(ActivatedSprite);
    attackButtonBase->setPressSprite(ActivatedSprite2);
    attackButtonBase->setPosition(9*SIZE.width/10,SIZE.height/7);
    commonAttackButton = new SneakyButton(); //按钮
    commonAttackButton->autorelease();
    commonAttackButton->initWithRect(CCRectMake(0,0,12,12));
    commonAttackButton->setIsToggleable(false);
    commonAttackButton->setIsHoldable(true); //设置在按下时，是否保持按下状态
    attackButtonBase->setButton(commonAttackButton);
    this->addChild(attackButtonBase);
}

void HubLayer::addSkillButton(const char* skilltubiao,const char* skilltubiao2,CCPoint skillpostion,SneakyButton* skillButton1)
{
    SneakyButtonSkinnedBase *skillButtonBase1 = new SneakyButtonSkinnedBase();
    skillButtonBase1->autorelease();
    skillButtonBase1->init();
    CCSprite* spriteBase = CCSprite::create(skilltubiao);
    skillButtonBase1->setDefaultSprite(spriteBase);
    CCSprite* ActivatedSprite = CCSprite::create( skilltubiao2);
    ActivatedSprite->setScale(1.3f);
    CCSprite* ActivatedSprite2 = CCSprite::create(skilltubiao2);
    ActivatedSprite2->setScale(1.3f);
    skillButtonBase1->setButton( skillButton1 );
    this->addChild(skillButtonBase1);
    skillButtonBase1->setPosition(skillpostion);
}

void HubLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-126,true);
}

bool HubLayer::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if (isTishinuqi1)
    {
        isTishinuqi1 = false;
        tishiNuqi2(1.0f);
    }
    
    if (!canTouch)
    {
        return false;
    }
    
    if (!this->isTeach)
    {
        if (Role->isDie || (gameLayer->isGameStart ==false)  )
        {
            return false;
        }
    }else
    {
        if (this->teachID != 0)
        {
            return false;
        }
    }
    CCPoint p  = touch->getLocation();
    if (zuo->boundingBox().containsPoint(p))
    {
        if (this->isTeach)
        {
            return false;
        }
        zuo->setDisplayFrame(CCSpriteFrame::create("util/gangxiangjian1.png",CCRect(0,0,zuo->getContentSize().width, zuo->getContentSize().height )));
        zuo->setScale(1.4);
        LeftisTouched = true;
        if(Role->isBeAttack)
        {
            return true;
        }
        Role->is_UndoRunState = true;
        Role->orientation = LEFT;
        
        if(!Role->isBeAttack&&Role->m_state!=s_attack && Role->qianqianNum<60)
        {
            int timeNow = millisecondNow();
            if(timeNow - lastzuoTime > 100 && timeNow - lastzuoTime < 250)
            {
                if (Role->isqianqian == false)
                {
                    Role->qianqian(-1);
                }
                Role->isqianqian = true;
            }else
            {
                Role->isqianqian = false;
            }
            lastzuoTime = millisecondNow();
        }
    }else if (you->boundingBox().containsPoint(p))
    {
      
        you->setDisplayFrame(CCSpriteFrame::create("util/gangxiangjian1.png",CCRect(0,0,zuo->getContentSize().width, zuo->getContentSize().height )));
        you->setScale(1.4);
        RightisTouched = true;
        if(Role->isBeAttack)
        {
            return true;
        }
        Role->is_UndoRunState = true;
        Role->orientation = RIGHT;
        if(!Role->isBeAttack&&Role->m_state!=s_attack)
        {
            int timeNow = millisecondNow();
            if(timeNow - lastyouTime > 100 && timeNow - lastyouTime < 250  && Role->qianqianNum<60)
            {
                if (Role->isqianqian == false)
                {
                    Role->qianqian(1);
                }

                Role->isqianqian = true;
            }else
            {
                Role->isqianqian = false;
            }
            lastyouTime = millisecondNow();
        }
    }else{
        if(Role->isBeAttack)
        {
            return true;
        }
        Role->is_UndoRunState = true;
        Role->orientation = HOLDER;
    }
    return true;
}

void HubLayer::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if (Role->isDie)
    {
        return;
    }
    
    CCPoint p  = touch->getLocation();
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
    }
}

void HubLayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if (Role->isDie)
    {
        return;
    }
    LeftisTouched = false;
    RightisTouched = false;
    zuo->setScale(1.3f);
    you->setScale(1.3f);
    Role->is_UndoRunState = false;
    zuo->setDisplayFrame(CCSpriteFrame::create("util/gangxiangjian2.png",CCRect(0,0,zuo->getContentSize().width, zuo->getContentSize().height )));
    you->setDisplayFrame(CCSpriteFrame::create("util/gangxiangjian2.png",CCRect(0,0,zuo->getContentSize().width, zuo->getContentSize().height )));
    Role->orientation = HOLDER;
    if(!Role->isCommanAttack &&!Role->isSkill2 && !Role->isSkill1 )
    {
        Role->stand();
    }
}

void HubLayer::TouchEnded()
{
    LeftisTouched = false;
    RightisTouched = false;
    zuo->setScale(1.3f);
    you->setScale(1.3f);
    Role->is_UndoRunState = false;
    zuo->setDisplayFrame(CCSpriteFrame::create("util/gangxiangjian2.png",CCRect(0,0,zuo->getContentSize().width, zuo->getContentSize().height )));
    you->setDisplayFrame(CCSpriteFrame::create("util/gangxiangjian2.png",CCRect(0,0,zuo->getContentSize().width, zuo->getContentSize().height )));
    Role->orientation = HOLDER;
    if(!Role->isCommanAttack &&!Role->isSkill2 && !Role->isSkill1 )
    {
        Role->stand();
    }
}

void HubLayer::HeromoveLeft(CCObject* pSender)
{
    Role->setPositionX(Role->getPositionX() - 3);
}

void HubLayer::HeromoveRight(CCObject* pSender)
{
    Role->setPositionX(Role->getPositionX() + 3);
}

void HubLayer::addJoy(){
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

void HubLayer::setDirectionKeyboardDelegate(void* delegate)
{
   
}

void HubLayer::setCommonAttackDelegate(void* delegate)
{
    if (commonAttackButton)
    {
        commonAttackButton->m_delegate = delegate;
    }
}

void HubLayer::AddLianJi()
{
    if (Role)
    {
        Role->lianjiTime = 160;
        Role->lianjiNum++;
        if(Role->lianjiNum > gameLayer->getMaxLianji())
        {
            gameLayer->setMaxLianji(Role->lianjiNum);
        }
        this->removeChildByTag(lianjiTag);
        CCSize winsize = CCDirector::sharedDirector()->getWinSize();
        CCSprite* lianji =  CCSprite::create("UI/qtsz_lj.png");
        lianji->setScale(0.5);
        this->addChild(lianji,lianjiTag*1000,lianjiTag);
        this->setNumber(Role->lianjiNum);
        lianji->setPosition(ccp(winsize.width-lianji->getContentSize().width/2-40,0.7*winsize.height));
        lianji->runAction(CCSequence::create(CCScaleTo::create(0.6, 1.0),CCFadeOut::create(2.8),NULL));
    }
}

void HubLayer::LianJiCallBack(CCObject* pSender)
{
    
}

void HubLayer::setNumber(int number)
{
    char wei[10] = {0};
    sprintf(wei, "%d",number);
    int weishu =  strlen(wei);
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    for(int i = 0 ;i < weishu;i++)
    {
        this->removeChildByTag(lianjiTagNum+i);
        int digit = number / (int)(pow(10.0, weishu-i -1)) % 10;
        char lianChar[50] = {0};
        sprintf(lianChar,"UI/qtsz_%d.png",digit);
        CCSprite* lianjiNum = CCSprite::create(lianChar);
        lianjiNum->setScale(0.6);
        this->addChild(lianjiNum,lianjiTag*1000+1,lianjiTagNum+i);
        lianjiNum->setPosition(ccp(winsize.width-100+i*lianjiNum->getContentSize().width*0.9,0.7*winsize.height));
        lianjiNum->runAction(CCSequence::create(CCScaleTo::create(0.6, 1.0),CCFadeOut::create(2.8),NULL));
    }
}

void HubLayer::showGoMessage()
{
    
}

void HubLayer::showHP()
{
    
    CCSprite* headUI = CCSprite::create("UI/uikuang.png");  //背景ui
    CCSprite* heroHp = CCSprite::create("UI/xuetiao.png");
    CCSprite* head =  CCSprite::create("UI/laotoutouxiang.png");  //老头头像
    CCProgressTimer* heroHpTimer = CCProgressTimer::create(heroHp);
    this->addChild(headUI,0);            //老头血条
    this->addChild(heroHpTimer,1,herohpTag);
    this->addChild(head,1);
    headUI->setAnchorPoint(ccp(0,1));
    headUI->setPosition(ccp(1*SIZE.width/40,SIZE.height));
    heroHpTimer->setAnchorPoint(ccp(0,0));
    heroHpTimer->setPosition(ccp(1*SIZE.width/40 + 1.4*head->getContentSize().width,SIZE.height -0.63*head->getContentSize().height));
    heroHpTimer->setMidpoint(CCPoint(0,0));
    heroHpTimer->setType(kCCProgressTimerTypeBar);
    heroHpTimer->setBarChangeRate(ccp(1, 0));
    heroHpTimer->setPercentage(100);
    head->setAnchorPoint(ccp(0,1));
    head->setPosition(ccp(1*SIZE.width/40,SIZE.height));
}

void HubLayer::showHP(float maxHp ,float hp)
{
    CCProgressTimer* heroHpTimer = dynamic_cast<CCProgressTimer*>(this->getChildByTag(herohpTag));
    if (heroHpTimer != NULL)
    {
          heroHpTimer->setPercentage(100*hp/maxHp);
    }
}

void HubLayer::addShowNumNpc()
{
    CCSprite* npcNum = CCSprite::create("UI/synpc.png");
    this->addChild(npcNum);
    npcNum->setPosition(ccp(SIZE.width/2,SIZE.height));
    npcNum->setAnchorPoint(ccp(1,1));
}

void HubLayer::showNpcNum(int npcnum)
{
    if(this->getChildByTag(shengyuMonsterDescTag) == NULL)
    {
        CCSprite* sprite  = CCSprite::create("UI/qtsz_sydr.png");
        this->addChild(sprite,100,shengyuMonsterDescTag);
        sprite->setPosition(ccp(SIZE.width*0.4,SIZE.height-25));
    }

    if(this->getChildByTag(nowNPCnumberTag)!=NULL){
        this->removeChildByTag(nowNPCnumberTag);
        char char_NPCmun[100] = {0};
        sprintf(char_NPCmun,"%d",npcnum);
        MakeNumbers* nowNPCnumber = new MakeNumbers(npcnum);
        this->addChild(nowNPCnumber->numbers,1000,nowNPCnumberTag);
        nowNPCnumber->numbers->setAnchorPoint(ccp(0,1));
        nowNPCnumber->numbers->setPosition(ccp(SIZE.width*0.42,SIZE.height-12.5));
    }else
    {
        char char_NPCmun[100] = {0};
        sprintf(char_NPCmun,"%d",npcnum);
        MakeNumbers* nowNPCnumber = new MakeNumbers(npcnum);
        this->addChild(nowNPCnumber->numbers,1000,nowNPCnumberTag);
        nowNPCnumber->numbers->setAnchorPoint(ccp(0,1));
        nowNPCnumber->numbers->setPosition(ccp(SIZE.width*0.42,SIZE.height-12.5));
    }
}

void HubLayer::showTime()
{
    if(this->getChildByTag(shengyuTimeTag) == NULL)
    {
        CCSprite* sprite  = CCSprite::create("time/time.png");
        this->addChild(sprite,100,shengyuTimeTag);
        sprite->setPosition(ccp(SIZE.width*0.48,SIZE.height-105));
    }
    this->schedule(schedule_selector(HubLayer::updateTime), 1.0f);
};

void HubLayer::updateTime(float dt)
{
    if(this->getChildByTag(nowShengyuTimeTag)!=NULL){
        this->removeChildByTag(nowShengyuTimeTag);
        char char_NPCmun[100] = {0};
        sprintf(char_NPCmun,"%d",gameLayer->getRemainTime());
        MakeNumbers* nowNPCnumber = new MakeNumbers(gameLayer->getRemainTime(),"time/0.png");
        this->addChild(nowNPCnumber->numbers,1000,nowShengyuTimeTag);
        nowNPCnumber->numbers->setAnchorPoint(ccp(0,1));
        nowNPCnumber->numbers->setPosition(ccp(SIZE.width*0.585,SIZE.height-88.5));
    }else
    {
        char char_NPCmun[100] = {0};
        sprintf(char_NPCmun,"%d",gameLayer->getRemainTime());
        MakeNumbers* nowNPCnumber = new MakeNumbers(gameLayer->getRemainTime(),"time/0.png");
        this->addChild(nowNPCnumber->numbers,1000,nowShengyuTimeTag);
        nowNPCnumber->numbers->setAnchorPoint(ccp(0,1));
        nowNPCnumber->numbers->setPosition(ccp(SIZE.width*0.585,SIZE.height-88.5));
    }
    
    if (gameLayer->getRemainTime() < 5)
    {
        if (this->getChildByTag(timeTips)!=NULL) {
            
        }else
        {
            CCSprite* s = CCSprite::create("time/lala.png");
            this->addChild(s,1000,timeTips);
            s->setPosition(ccp(SIZE.width*0.50,SIZE.height-155));
            s->runAction(CCRepeatForever::create(CCBlink::create(0.5f, 1)));
        }
    }
}

void HubLayer::showKillMonster()
{
    if(this->getChildByTag(shengyuMonsterDescTag) == NULL)
    {
        CCSprite* sprite  = CCSprite::create("util/xintian_jsdr.png");
        this->addChild(sprite,100,shengyuMonsterDescTag);
        sprite->setScale(1.1f);
        sprite->setPosition(ccp(SIZE.width*0.39,SIZE.height-25));
    }
    
    if(this->getChildByTag(nowNPCnumberTag)!=NULL){
        this->removeChildByTag(nowNPCnumberTag);
        char char_NPCmun[100] = {0};
        sprintf(char_NPCmun,"%d",gameLayer->killMonsterNum);
        MakeNumbers* nowNPCnumber = new MakeNumbers(gameLayer->killMonsterNum);
        this->addChild(nowNPCnumber->numbers,1000,nowNPCnumberTag);
        nowNPCnumber->numbers->setAnchorPoint(ccp(0,1));
        nowNPCnumber->numbers->setPosition(ccp(SIZE.width*0.45,SIZE.height-12.5));
    }else
    {
        char char_NPCmun[100] = {0};
        sprintf(char_NPCmun,"%d",gameLayer->killMonsterNum);
        MakeNumbers* nowNPCnumber = new MakeNumbers(gameLayer->killMonsterNum);
        this->addChild(nowNPCnumber->numbers,1000,nowNPCnumberTag);
        nowNPCnumber->numbers->setAnchorPoint(ccp(0,1));
        nowNPCnumber->numbers->setPosition(ccp(SIZE.width*0.45,SIZE.height-12.5));
    }
}

void HubLayer::showKiloMeter()
{
    if(this->getChildByTag(shengyuMonsterDescTag) == NULL)
    {
        CCSprite* sprite  = CCSprite::create("util/xintian_qjjl.png");
        this->addChild(sprite,100,shengyuMonsterDescTag);
        sprite->setScale(1.1f);
        sprite->setPosition(ccp(SIZE.width*0.39,SIZE.height-25));
    }
    this->schedule(schedule_selector(HubLayer::updateKiloMeter) , 0.016f);
}


void HubLayer::updateKiloMeter(float)
{
    int distanse = MAX(0,(Role->getPositionX() - 850)/10) ;
    gameLayer->kilometer = distanse;
    if(this->getChildByTag(nowNPCnumberTag)!=NULL){
        this->removeChildByTag(nowNPCnumberTag);
        char char_NPCmun[100] = {0};
        sprintf(char_NPCmun,"%d",gameLayer->killMonsterNum);
        MakeNumbers* nowNPCnumber = new MakeNumbers(distanse);
        this->addChild(nowNPCnumber->numbers,1000,nowNPCnumberTag);
        nowNPCnumber->numbers->setAnchorPoint(ccp(0,1));
        nowNPCnumber->numbers->setPosition(ccp(SIZE.width*0.45,SIZE.height-12.5));
    }else
    {
        char char_NPCmun[100] = {0};
        sprintf(char_NPCmun,"%d",gameLayer->killMonsterNum);
        MakeNumbers* nowNPCnumber = new MakeNumbers(distanse);
        this->addChild(nowNPCnumber->numbers,1000,nowNPCnumberTag);
        nowNPCnumber->numbers->setAnchorPoint(ccp(0,1));
        nowNPCnumber->numbers->setPosition(ccp(SIZE.width*0.45,SIZE.height-12.5));
    }
    


}

void HubLayer::runSkill(int id)
{
    if (id == 4 )
    {
        CCProgressTimer* ct4 = dynamic_cast<CCProgressTimer*>( this->getChildByTag(skill4TimerTag));
        ct4->setPosition(ccp(SIZE.width/2, SIZE.height/2));
        ct4->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCEaseIn::create(CCMoveTo::create(0.5f, button4->getPosition()), 3.0f),NULL)   );
    }else if (id == 3)
    {
        CCProgressTimer* ct4 = dynamic_cast<CCProgressTimer*>( this->getChildByTag(skill3TimerTag));
        ct4->setPosition(ccp(SIZE.width/2, SIZE.height/2));
        ct4->runAction( CCSequence::create(CCDelayTime::create(0.2f), CCEaseIn::create(CCMoveTo::create(0.5f, button3->getPosition()), 3.0f),NULL) );
    }else if (id == 2)
    {
        CCProgressTimer* ct4 = dynamic_cast<CCProgressTimer*>( this->getChildByTag(skill2TimerTag));
        ct4->setPosition(ccp(SIZE.width/2, SIZE.height/2));
        ct4->runAction( CCSequence::create(CCDelayTime::create(0.2f), CCEaseIn::create(CCMoveTo::create(0.5f, button2->getPosition()), 3.0f),NULL) );
    }
}

void HubLayer::jinengban()
{
    CCMenu* skillMenu = CCMenu::create();
    skillMenu->setPosition(ccp(0,0));
    this->addChild(skillMenu);
    
    /*天怒站*/
    CCMenuItemImage* button1 = CCMenuItemImage::create("util/tubiaokuang1.png", "util/tubiaokuang1.png", Role,menu_selector(Hero::skill1) );
    skillMenu->addChild(button1);
    button1->setPosition(CCPoint(7.4*SIZE.width/10,1.1*SIZE.height/10));

    button2 = CCMenuItemImage::create("util/tubiaokuang1.png", "util/tubiaokuang1.png",Role,menu_selector(Hero::skill2));
    skillMenu->addChild(button2);
    button2->setPosition(CCPoint(7.85*SIZE.width/10,3.12*SIZE.height/10));
    
    button3 = CCMenuItemImage::create("util/tubiaokuang1.png", "util/tubiaokuang1.png",Role,menu_selector(Hero::skill3));
    skillMenu->addChild(button3);
    button3->setPosition(CCPoint(9.05*SIZE.width/10,3.75*SIZE.height/10));
    
    button4 = CCMenuItemImage::create("util/tubiaokuang1.png", "util/tubiaokuang1.png",Role,menu_selector(Hero::skill4));
    skillMenu->addChild(button4);
    button4->setPosition(CCPoint(6.1*SIZE.width/10,1.1*SIZE.height/10));
    
    button1->setScale(1.2);
    button2->setScale(1.2);
    button3->setScale(1.2);
    button4->setScale(1.2);

    CCSprite* mengban = CCSprite::create("util/skill1.png");
    CCProgressTimer* ct1 = CCProgressTimer::create(mengban);   //技能1的冷却条
    ct1->setPosition(button1->getPosition());
    this->addChild(ct1,1000,skill1TimerTag);
    ct1->setPercentage(100);
    ct1->setType(kCCProgressTimerTypeRadial);
    
    CCSprite* mengban2 = CCSprite::create("util/skill2.png");
    CCProgressTimer* ct2 = CCProgressTimer::create(mengban2);   //技能2的冷却条
    ct2->setPosition(button2->getPosition());
    this->addChild(ct2,1000,skill2TimerTag);
    
    if (KingData->getBazhinv())
    {
        ct2->setPercentage(100);
    }else
    {
        ct2->setPercentage(0);
    }
    ct2->setType(kCCProgressTimerTypeRadial);
    CCSprite* mengban3 = CCSprite::create("util/skill3.png");
    CCProgressTimer* ct3 = CCProgressTimer::create(mengban3);   //技能3的冷却条
    ct3->setPosition(button3->getPosition());
    this->addChild(ct3,1000,skill3TimerTag);
    
    if (KingData->getBajiubei())
    {
        ct3->setPercentage(100);
    }else
    {
        ct3->setPercentage(0);
    }
    ct3->setType(kCCProgressTimerTypeRadial);
    CCSprite* mengban4 = CCSprite::create("util/skill4.png");
    CCProgressTimer* ct4 = CCProgressTimer::create(mengban4);   //技能4的冷却条
    ct4->setPosition(button4->getPosition());
    this->addChild(ct4,1000,skill4TimerTag);
    ct4->setPercentage(100);
    ct4->setType(kCCProgressTimerTypeRadial);
    
    if (KingData->getJinjiDuobi()) {
        ct4->setPercentage(100);
    }else
    {
        ct4->setPercentage(0);
    }
    
}

void HubLayer::jihuo()
{
    CCProgressTimer* timer3 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill3TimerTag));
    timer3->setPercentage(100);
    CCProgressTimer* timer2 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill2TimerTag));
    timer2->setPercentage(100);
}

#pragma ///mark -技能痛苦火海
void HubLayer::zhuangtai()
{
    CCParticleSystem* system1;
    system1 =  CCParticleSystemQuad::create("smallUI/Painfulpurgatory.plist");
    this->addChild(system1,1000,51);
    system1->setPositionType(kCCPositionTypeFree);
    system1->setAutoRemoveOnFinish(true);
    system1->setPosition(ccp(SIZE.width/2,Role_Height));
}

void HubLayer::showMoney()     //显示金币
{
    int money = KingData->getMoney();
    char wei[10] = {0};
    sprintf(wei, "%d",money);
    int weishu =  strlen(wei);
    for(int i = 0 ;i < weishu;i++)
    {
        int digit = money / (int)(pow(10.0, weishu-i -1)) % 10;
        char lianChar[50] = {0};
        sprintf(lianChar,"UI/shuzi%d.png",digit);
        CCSprite* moneySprite = CCSprite::create(lianChar);
        this->addChild(moneySprite,1,moneyTag);
        moneySprite->setAnchorPoint(ccp(1,1));
        moneySprite->setPosition(ccp(32*SIZE.width/40 + i*moneySprite->getContentSize().width,SIZE.height));
    }
}

void HubLayer::addDamageNum(int num,CCPoint p,int dir)
{
    CCLabelAtlas* diceCount=CCLabelAtlas::create( CCString::createWithFormat("%d",num)->getCString(), "util/damageNum.png", 24.4, 28, '0');
    this->addChild(diceCount);
    diceCount->setPosition(p);
    float duration = CCRANDOM_0_1()*0.15 + 0.5;
    if (Role->m_state == s_skill) {
        duration = duration;
    }else
    {
        duration = duration*1.5;
    }
    
    cocos2d::CCPoint position =  CCPoint(dir*CCRANDOM_0_1()*150 + dir*80, CCRANDOM_0_1()*30);
    float height = CCRANDOM_0_1()*30 + 30;
    CCJumpBy* jumpby = CCJumpBy::create(duration,position, height, 1);
    CCCallFuncN* call = CCCallFuncN::create(diceCount, callfuncN_selector ( HubLayer::removeDamage ));
    CCSequence* seq = CCSequence::create(jumpby,call,NULL);
    diceCount->runAction( seq );
}

void HubLayer::removeDamage(CCNode* pSender)
{
    CCLabelAtlas* atlas = dynamic_cast<CCLabelAtlas*>(pSender);
    atlas->removeFromParent();
}
void HubLayer::juqingTishi()
{
    
}

void HubLayer::showHeroAnger()       //显示主角怒气
{
    
}