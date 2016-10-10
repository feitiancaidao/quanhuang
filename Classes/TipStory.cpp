//
//  TipStory.cpp
//  King
//
//  Created by mac on 14-4-21.
//
//

#include "TipStory.h"
#include "Define.h"
#include "cocos-ext.h"
#include "XXIconv.h"
#include "TextInfos.h"

using namespace gui;

//std::string wordss[] =
//{
//   "老大快看，前面有个美女过来了", "真的是好大的美女啊，快快请美女过来聊聊天。","一群臭屌丝快快让开，本小姐还要赶路呢",
//    "嘿，我就喜欢你这暴脾气，咱们回家好好玩玩。兄弟们，上！","美人别反抗了，我这么帅陪你玩耍你有什么不乐意的","你们干什么，快把小舞放下，不然弄死你们。","嘿，弄死这不长眼，我先回去享受生活了，哈哈哈哈。"
//};

TipStorySprite* TipStorySprite::create(int width,int height)
{
    TipStorySprite* tip = new TipStorySprite();
    tip->autorelease();
    tip->init(width, height);
    return tip;
}
bool TipStorySprite::init(int width,int height)
{
    if(!CCSprite::init())
    {
        return false;
    }
    this->width = width;
    this->height = height;
    this->setContentSize(CCSize(width,height));
    this->setAnchorPoint(ccp(0, 0));
    return true;
}
void TipStorySprite::draw()
{
    ccDrawSolidRect(ccp(0,0), ccp(width,height), ccc4f(4/255.0, 24/255.0, 49/255.0, 75/100));
    glLineWidth( 2.0f );
    ccDrawColor4B(31,124,126,75/100);
    //绘制四个点
    ccDrawRect(ccp(0,0),  ccp(width,height));
}

TipStory::~TipStory()
{
    CCLog("TipStory::~TipStory()");
}
CCScene* TipStory::scene()
{
    CCScene* scene = CCScene::create();
    TipStory* tipsLayer = TipStory::create();
    scene->addChild(tipsLayer);
    return scene;
}

bool TipStory::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    currentduihua_index = 0;
    currentword_index = 0;
    hunhuntouxiang = CCSprite::create("duihuakuang/hunhun.png");
    this->addChild(hunhuntouxiang,100);
    hunhuntouxiang->setPosition(ccp(1.1*SIZE.width,10));
    hunhuntouxiang->setAnchorPoint(ccp(0, 0));
    
    bosstouxiang = CCSprite::create("duihuakuang/BOSS.png");
    this->addChild(bosstouxiang,100);
    bosstouxiang->setPosition(ccp(1.1*SIZE.width,10));
    bosstouxiang->setAnchorPoint(ccp(0, 0));

    nvroletouxiang = CCSprite::create("duihuakuang/xiaowu.png");
    this->addChild(nvroletouxiang,100);
    nvroletouxiang->setPosition(ccp(-0.1*SIZE.width,10));
    nvroletouxiang->setAnchorPoint(ccp(1, 0));
    
    roletouxiang = CCSprite::create("duihuakuang/bashen.png");
    this->addChild(roletouxiang,100);
    roletouxiang->setPosition(ccp(-0.1*SIZE.width,10));
    roletouxiang->setAnchorPoint(ccp(1, 0));
    
    canSay = false;
    this->setTouchEnabled(true);
    juqingIndex = 0;
    back = CCSprite::create("maps/map01.png");
    this->addChild(back,-20000,-10000);
    back->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.5));

    char json[50] = {0};
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"nvzhujiao","nvzhujiao");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    nvRole = CCArmature::create("nvzhujiao");
    nvRole->setPosition(ccp(SIZE.width*(-0.1), SIZE.height/4));
    nvRole->getAnimation()->playWithIndex(1);
    CCMoveTo* moveto = CCMoveTo::create(4, ccp(SIZE.width*(0.5), SIZE.height/4));
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::tiaoxi));
    CCSequence* seq = CCSequence::create(moveto,call,NULL);
    nvRole->runAction(seq);
    this->addChild(nvRole);
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"g2","g2");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    g2 = CCArmature::create("g2");
    this->addChild(g2);

    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"boss1","boss1");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    boss = CCArmature::create("boss1");
    this->addChild(boss);
    
    
    sprintf( json, "%s/%s/%s.ExportJson",dirOfani,"g1","g1");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    g1 = CCArmature::create("g1");
    this->addChild(g1);
    
    boss->setPosition(SIZE.width*(1.20) ,SIZE.height/4 );
    g1->setPosition(SIZE.width*(1.28) ,SIZE.height/4 -50 );
    g2->setPosition(SIZE.width*(1.28) ,SIZE.height/4 + 50 );
    boss->setScaleX(-1);
    g1->setScaleX(-1);
    g2->setScaleX(-1);
    return true;
}

void TipStory::tiaoxi()
{
    CCMoveBy* moveBy = CCMoveBy::create(2, ccp(-400, 0));
    CCMoveBy* moveBy1 = CCMoveBy::create(2, ccp(-400, 0));
    CCMoveBy* moveBy2 = CCMoveBy::create(2, ccp(-400, 0));
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::addTips));
    CCSequence* seq = CCSequence::create(moveBy,call,NULL);
    boss->runAction(seq);
    g1->runAction(moveBy1);
    g2->runAction(moveBy2);
    nvRole->getAnimation()->playWithIndex(0);
    boss->getAnimation()->playWithIndex(1);
    g1->getAnimation()->playWithIndex(1);
    g2->getAnimation()->playWithIndex(1);
}

void TipStory::tiaoxi2()
{
    CCMoveBy* moveBy = CCMoveBy::create(1, ccp(-120, 0));
    CCMoveBy* moveBy1 = CCMoveBy::create(1, ccp(-120, 0));
    CCMoveBy* moveBy2 = CCMoveBy::create(1, ccp(-120, 0));
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::newblackScreen));
    CCSequence* seq = CCSequence::create(moveBy,call,NULL);
    boss->runAction(seq);
    g1->runAction(moveBy1);
    g2->runAction(moveBy2);
    nvRole->getAnimation()->playWithIndex(0);
    boss->getAnimation()->playWithIndex(1);
    g1->getAnimation()->playWithIndex(1);
    g2->getAnimation()->playWithIndex(1);
}


void TipStory::newblackScreen()
{
    black = CCLayerColor::create(ccc4(0, 0, 0,255), SIZE.width, SIZE.height);
    this->addChild(black,999999);
    
    UILabel* label = UILabel::create();
	label->setText(XXIconv::GBK2UTF("Ah! No,stay away!"));

    label->setColor(ccc3(0xff, 0xae, 0x00));
    label->setFontSize(32);
    label->setFontName("宋体");
    label->setPosition(ccp(SIZE.width/2, SIZE.height/2));
    black->addChild(label);

    CCFadeOut* fade = CCFadeOut::create(3);
    CCCallFunc* call = CCCallFunc::create(this,callfunc_selector(TipStory::resumeTip));
    CCSequence* seq = CCSequence::create(fade,call,NULL);
    this->runAction(seq);

}

void TipStory::xiechi()
{
    black->setVisible(false);
    
    monsterSay();
    addTip01(4, 1);
    
    CCMoveBy* moveBy = CCMoveBy::create(3, ccp(300, 0));
    CCDelayTime* delay = CCDelayTime::create(1.0f);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::zhuiji));
    CCSequence* seq = CCSequence::create(delay,call,NULL);
    
    nvRole->runAction(moveBy);
    CCMoveBy* moveBy1 = CCMoveBy::create(3, ccp(300, 0));
    g1->runAction(moveBy1);
    CCMoveBy* moveBy2 = CCMoveBy::create(3, ccp(300, 0));
    g2->runAction(moveBy2);
    g1->setScaleX(1);
    g2->setScaleX(1);
    this->runAction(seq);
}

void TipStory::zhuiji()
{
    hero = Hero::create();
    hero->unscheduleAllSelectors();
    hero->setZOrder(-100);
    this->addChild(hero);
    hero->setPosition(SIZE.width*(-0.1) ,SIZE.height/4);
    CCMoveBy* moveBy = CCMoveBy::create(2, ccp(400, 0));
    hero->runAction(moveBy);
    hero->s->getAnimation()->playWithIndex(1);
    
    CCDelayTime* delay = CCDelayTime::create(2.0f);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::zhuiji2));
    CCSequence* seq = CCSequence::create(delay,call,NULL);
    this->runAction(seq);
}

void TipStory::zhuiji2()
{
     monsterSay();
     addTip1(5, 0);
    
     juqingIndex = 5;
     CCDelayTime* delay = CCDelayTime::create(2.0f);
     CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::zhuiji3));
     CCSequence* seq = CCSequence::create(delay,call,NULL);
     this->runAction(seq);
     g1->getAnimation()->playWithIndex(0);
     g2->getAnimation()->playWithIndex(0);
     nvRole->getAnimation()->pause();
     hero->s->getAnimation()->playWithIndex(0);
}

void TipStory::zhuiji3()
{
     g1->getAnimation()->playWithIndex(1);
     g2->getAnimation()->playWithIndex(1);
     nvRole->getAnimation()->resume();
     hero->s->getAnimation()->playWithIndex(1);
    
     monsterSay();
     addTip01(6, 1);
    
     CCMoveBy* moveBy1 = CCMoveBy::create(1, ccp(100, 0));
     CCMoveBy* moveBy2 = CCMoveBy::create(1, ccp(250, 0));
     CCMoveBy* moveBy3 = CCMoveBy::create(1, ccp(-100, 0));
     CCMoveBy* moveBy4 = CCMoveBy::create(1, ccp(-100, 0));
     hero->runAction(moveBy1);
     g2->runAction(moveBy4);
     g1->runAction(moveBy3);
     nvRole->runAction(moveBy2);
     g1->setScaleX(-1);
     g2->setScaleX(-1);
     CCDelayTime* delay = CCDelayTime::create(1.5f);
     CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::heiping));
     CCSequence* seq = CCSequence::create(delay,call,NULL);
     this->runAction(seq);
}

void TipStory::heiping()
{
    g1->getAnimation()->playWithIndex(0);
    g2->getAnimation()->playWithIndex(0);
    hero->s->getAnimation()->playWithIndex(0);
    black->removeAllChildren();
    black->setVisible(true);
    CCFadeIn* fade = CCFadeIn::create(2.5);
    CCDelayTime* delay = CCDelayTime::create(2.5f);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::pop));
    CCSequence* seq = CCSequence::create(delay,call,NULL);
    this->runAction(seq);
    CCSequence* seq2 = CCSequence::create(fade,NULL);
    black->runAction(seq2);
}

void TipStory::pop()
{
    monsterSay();
    CCDirector::sharedDirector()->popScene();
}

void TipStory::addTip1(int index , int roleid)
{
    
    canSay = false;
    label->setVisible(false);
    currentduihua_index = index;
    tip1->runAction(CCMoveTo::create(0.2f, ccp(280,80)));
    
    if (roleid == 0)
    {
        roletouxiang->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.26, 10))
                                                     ,CCCallFunc::create(this, callfunc_selector(TipStory::setText1)),NULL ));
    }else if (roleid == 1)
    {
        nvroletouxiang->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.26, 10))
                                                   ,CCCallFunc::create(this, callfunc_selector(TipStory::setText1)),NULL ));
    }
}

void TipStory::addTip01(int index ,int monsterID)
{
    canSay = false;
    label2->setVisible(false);
    currentduihua_index = index;
    tip01->runAction(CCMoveTo::create(0.2f, ccp(SIZE.width-280,80)));
   
    if (monsterID == 0)
    {
        hunhuntouxiang->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.72, 10))
                                                     ,CCCallFunc::create(this, callfunc_selector(TipStory::setText)),NULL ));
    }else if (monsterID == 1)
    {
        bosstouxiang->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.70, 10))
                                                   ,CCCallFunc::create(this, callfunc_selector(TipStory::setText)),NULL ));
    }
    
}

void TipStory::setText1()
{
    canSay = true;
	label->setText(XXIconv::GBK2UTF(wordss[currentduihua_index].c_str()));
    label->setVisible(true);
}

void TipStory::setText()
{
    canSay = true;
	label2->setText(XXIconv::GBK2UTF(wordss[currentduihua_index].c_str()));
    label2->setVisible(true);
}

void TipStory::scheduleduihua(float dt)
{
    label2->setVisible(true);
    currentword_index++;
    int len = strlen(wordss[currentduihua_index].c_str());
    if (len <= currentword_index)
    {
        this->unschedule(schedule_selector(TipStory::scheduleduihua));
    }
	label2->setText(XXIconv::GBK2UTF(wordss[currentduihua_index].substr(0, currentword_index).c_str()));
    
}

void TipStory::addTips()
{
    boss->getAnimation()->playWithIndex(0);
    g1->getAnimation()->playWithIndex(0);
    g2->getAnimation()->playWithIndex(0);
    canSay = true;
    nvRole->getAnimation()->playWithIndex(0);
    tip1 = CCSprite::create("duihuakuang/UI80.png");
    tip1->setPosition(ccp( -150, -120));
  
    this->addChild(tip1);
    tip01 = CCSprite::create("duihuakuang/UI80.png");
    tip01->setPosition(ccp(SIZE.width+150,-120));

    this->addChild(tip01);
    
    label = UILabel::create();
   
    tip1->addChild(label);
    label->setFontName("宋体");
    label->setFontSize(20);
    label->setPosition(ccp(170, tip1->getContentSize().height));
    label->setAnchorPoint(ccp(0, 1));
    label->setColor(ccc3(241, 191, 194));
    label->setTextAreaSize(CCSize(200,150));
    label->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
    
    label2 = UILabel::create();
    tip01->addChild(label2);
    label2->setFontName("宋体");
    label2->setFontSize(20);
    label2->setPosition(ccp(80, tip01->getContentSize().height));
    label2->setAnchorPoint(ccp(0, 1));
    label2->setColor(ccc3(241, 191, 194));
    label2->setTextAreaSize(CCSize(190,150));
	//label2->setText(XXIconv::GBK2UTF("老大快看，前面有个美女过来了"));
     label2->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
    addTip01(0,0);

    
    label02 = CCLabelTTF::create();
    tip01->addChild(label02);
//
//    tip2 = CCSprite::create("duihuakuang_3.png");
//    this->addChild(tip2);
//    tip2->setAnchorPoint(ccp(0, 0));
//    tip2->setPosition(ccp(0,tip1->getContentSize().height + 0.0f));
//    label1 = UILabel::create();
//    label1->setText("混混");
//    label1->setFontName("宋体");
//    label1->setFontSize(20);
//    label1->setPosition(ccp(35, tip2->getContentSize().height-30));
//    label1->setAnchorPoint(ccp(0, 0));
//    label1->setColor(ccc3(241, 241, 194));
//    tip2->addChild(label1);
    tip3 = CCSprite::create("duihuakuang/duihuakuang_2.png");
    tip3->setPosition(ccp(10, nvRole->getContentSize().height));
    tip3->setAnchorPoint(ccp(0.5, 0));
    tip3->setVisible(false);
    nvRole->addChild(tip3);
    UILabel* label3 = UILabel::create();
	//label3->setText(XXIconv::GBK2UTF("哈哈哈哈!"));
    tip3->addChild(label3);
    label3->setFontName("宋体");
    label3->setFontSize(20);
    label3->setPosition(ccp(20, tip3->getContentSize().height-50));
    label3->setAnchorPoint(ccp(0, 0));
    label3->setColor(ccc3(241, 191, 194));
}

void TipStory::blackScreen(CCObject* pSender)
{
    black = CCLayerColor::create(ccc4(0, 0, 0,255), SIZE.width, SIZE.height);
    this->addChild(black);
    CCSprite* zhen = CCSprite::create("UI/zhen.png");
    CCSprite* shi = CCSprite::create("UI/shi.png");
    CCSprite* ge = CCSprite::create("UI/ge.png");
    CCSprite* fei = CCSprite::create("UI/fei.png");
    CCSprite* wu = CCSprite::create("UI/wu.png");
    node2 = CCNode::create();
    this->addChild(node2,200);
    node2->setPosition(ccp(SIZE.width/2, SIZE.height/2));
    node2->addChild(zhen);
    node2->addChild(shi);
    node2->addChild(ge);
    node2->addChild(fei);
    node2->addChild(wu);
    CCSize cSize = zhen->getContentSize();
    zhen->setPositionX(cSize.width*-2);
    shi->setPositionX(cSize.width*-1);
    fei->setPositionX(cSize.width*1);
    wu->setPositionX(cSize.width*2.5);

    zhen->setVisible(false);
    shi->setVisible(false);
    ge->setVisible(false);
    fei->setVisible(false);
    wu->setVisible(false);
    
    CCDelayTime* delay1 = CCDelayTime::create(0.4);
    CCShow* show = CCShow::create();
    CCSequence* seq1 = CCSequence::create(delay1,show,NULL);
    CCDelayTime* delay2 = CCDelayTime::create(0.8);
    CCSequence* seq2 = CCSequence::create(delay2,show,NULL);
    CCDelayTime* delay3 = CCDelayTime::create(1.2);
    CCSequence* seq3 = CCSequence::create(delay3,show,NULL);
    CCDelayTime* delay4 = CCDelayTime::create(1.8);
    CCSequence* seq4 = CCSequence::create(delay4,show,NULL);
    CCDelayTime* delay5 = CCDelayTime::create(1.8);
    CCSequence* seq5 = CCSequence::create(delay5,show,NULL);
    zhen->runAction(seq1);
    shi->runAction(seq2);
    ge->runAction(seq3);
    fei->runAction(seq4);
    wu->runAction(seq5);
    CCFadeOut* fade = CCFadeOut::create(3);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::resumeTip));
    CCSequence* seq = CCSequence::create(fade,call,NULL);
    this->runAction(seq);
}

void TipStory::resumeTip()
{
    boss->setVisible(false);
    g1->setPositionX(nvRole->getPositionX() - 100);
    g2->setPositionX(nvRole->getPositionX() - 100);
    nvRole->getAnimation()->playWithIndex(2);

    CCFadeOut* fade = CCFadeOut::create(0.3);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::xiechi));
    CCSequence* seq = CCSequence::create(fade,call,NULL);
    black->runAction(seq);
}

void TipStory::moon(CCObject* pSender)
{
    moonsprite = CCSprite::create("UI/moon.png");
    this->addChild(moonsprite,200);
    moonsprite->setPosition(ccp(SIZE.width, SIZE.height));
    moonsprite->setScale(0.2);
    
    CCMoveTo* moveTO = CCMoveTo::create(2.0, ccp(SIZE.width/2, SIZE.height/2));
    CCScaleBy* scaleBy = CCScaleBy::create(2.0, 5);
    CCSpawn* spawn = CCSpawn::create(moveTO,scaleBy,NULL);
    CCDelayTime* delay = CCDelayTime::create(1);
    CCScaleBy* scaleBy2 = CCScaleBy::create(2.0, 0.2);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::resumeTip2));
    CCSequence* SEQ = CCSequence::create(spawn,delay,scaleBy2,call,NULL);
    
    CCMenu* menu = CCMenu::create();
    this->addChild(menu);
    menu->setPosition(0, 0);
    CCSprite* sprite = CCSprite::create("tg.png");
    CCMenuItemSprite* item = CCMenuItemSprite::create(sprite, sprite,this,menu_selector(TipStory::tiaoguo));
    menu->addChild(item);
    item->setAnchorPoint(ccp(1, 1));
    item->setPosition(ccp(SIZE.width - 30, SIZE.height - 40));
    moonsprite->runAction(SEQ);
}

void TipStory::tiaoguo(CCObject* o)
{
    CCDirector::sharedDirector()->popScene();
}

void TipStory::resumeTip2()
{
    CCFadeOut* fade = CCFadeOut::create(1);
    CCSequence* seq = CCSequence::create(fade,NULL);
    black->runAction(seq);
    CCMoveTo* move = CCMoveTo::create(1.0f, ccp(SIZE.width*0.62, SIZE.height/4+22));
    CCScaleBy* scaleBy = CCScaleBy::create(1.0, 0.2);
    CCFadeOut* fade1 = CCFadeOut::create(1.0f);
    CCSpawn* spawn = CCSpawn::create(move,scaleBy,fade1,NULL);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::fade));
    CCSequence* seq1 = CCSequence::create(spawn,call,NULL);
    moonsprite->runAction(seq1);
}

void TipStory::fade()
{
    CCFadeIn* fade = CCFadeIn::create(2);
    CCFadeOut* fadeo = CCFadeOut::create(2);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::bashenan));
    CCCallFunc* call2 = CCCallFunc::create(this, callfunc_selector(TipStory::bashenan1));
    CCSequence* seq = CCSequence::create(fade,call,fadeo,call2,NULL);
    black->runAction(seq);
}

void TipStory::bashenan()
{
    hero->s->getAnimation()->playWithIndex(18, -1, -1, 0, -1);
}

void TipStory::bashenan1()
{
    CCDelayTime* delay = CCDelayTime::create(1);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::fade2));
    CCSequence* seq1 = CCSequence::create(delay,call,NULL);
    this->runAction(seq1);
}

void TipStory::fade2()
{
    CCFadeIn* fade = CCFadeIn::create(1);
    CCFadeOut* fadeo = CCFadeOut::create(1);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::bashenan2));
    CCSequence* seq = CCSequence::create(fade,call,fadeo,NULL);
    black->runAction(seq);
}

void TipStory::bashenan2()
{
    hero->s->getAnimation()->playWithIndex(0);
    tip1->setVisible(true);
    tip2->setVisible(true);
    menu->setVisible(true);
	label->setText(XXIconv::GBK2UTF("黯月家族，传说中的古武术世家。以月轮为标记，新一代后裔名为：  “琼”"));
	label1->setText(XXIconv::GBK2UTF("系统"));
    CCDelayTime* delay = CCDelayTime::create(3);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(TipStory::pop));
    CCSequence* seq1 = CCSequence::create(delay,call,NULL);
    this->runAction(seq1);
}



void TipStory::nextTips()
{
    if (canSay == false)
    {
        return;
    }
    
    if (juqingIndex == 0)
    {
         monsterSay();
        juqingIndex = 1;
        addTip01(1, 1);
        return;
    }
  
    if (juqingIndex==1)
    {
        monsterSay();
        juqingIndex = 2;
        addTip1(2, 1);
        return;
    }
    
    if (juqingIndex==2)
    {
        monsterSay();
        juqingIndex = 3;
        addTip01(3, 1);
        return;
    }
    
    if (juqingIndex==3)
    {
        monsterSay();
        juqingIndex = 4;
        this->tiaoxi2();
        return;
    }
    
    if (juqingIndex == 5)
    {
//        label->setText("嘿，我就喜欢你这暴脾气，咱们回家好好玩玩。兄弟们，上!");
//        label1->setText("头目");
    }
    
}

void TipStory::monsterSay()
{

    hunhuntouxiang->setPosition(ccp(1.1*SIZE.width,10));
    bosstouxiang->setPosition(ccp(1.1*SIZE.width,10));
    nvroletouxiang->setPosition(ccp(-0.1*SIZE.width,10));
    roletouxiang->setPosition(ccp(-0.1*SIZE.width,10));
    tip1->setPosition(ccp( -150, -120));
    tip01->setPosition(ccp(SIZE.width+150,-120));

}

void TipStory::actionCallback(CCArmature *pArmature,MovementEventType eventType, const char *animationID)
{
    if (eventType == START) {
        this->setZOrder(10000);
    }
    if (eventType == COMPLETE)
    {
        this->monster->actionID = 0;
    }
}

void TipStory::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-125,true);
}

bool TipStory::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    nextTips();
    return true;
}