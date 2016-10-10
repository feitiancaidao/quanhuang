//
//  ShopBuy.cpp
//  King
//
//  Created by mac on 14-3-28.
//
//

#include "ShopBuy.h"
#include "ShopBuyLayer.h"
#include "HubLayer.h"
#include "Define.h"
#include "cocos-ext.h"
#include "GameData.h"
#include "HubLayer.h"
#include "PlayerHeadUI.h"
#include "PersonalAudioEngine.h"
#include "GlobleUnits.h"
#include "XXIconv.h"
#include "TextInfos.h"
#include "openalertJni.h"
//static std::string nenglidescTitle[4] = {"八稚女","八酒杯","死亡复活","怒气包"};
//static std::string nenglidescText[5] = {"用强有力的爪在敌方身体上狂撕，之后双手锁定对方头部发劲，令敌方遍布全身的撕伤同时喷血，以残忍暴虐著称","出招之际，紫焰纵横，使受术者体感停止","在主角死亡时原地满血复活","获得10个怒气!用你的技能去收割敌人吧!消耗1000金币","在主角死亡时原地满血复活,此次购买免费"};
//static std::string shopdescTitle[5] = {"金币礼包(小)","金币礼包(中)","金币礼包(大)","怒气大礼包","超级大礼包"};
//static std::string shopdescText[5] = {"1888金币礼包!","5888金币礼包!","18888金币礼包","30个怒气包! 额外附赠5个! 共35个!","8888金币! 50个怒气包! 学会全部技能! 额外附赠一次死亡复活!"};






using namespace gui;






ShopBuy::ShopBuy()
{
    currToshoW = 0;
    nengliSort = 0;
    shopSort = 0;
}
void ShopBuy::isShowFuhuo()
{

}

void ShopBuy::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-129,true);
}

bool ShopBuy::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if(this->isVisible())
    {
        if(bg->boundingBox().containsPoint(pTouch->getLocation()))
        {
            return false;
        }else if(pTouch->getLocation().x < SIZE.width*0.2)
        {
            return false;
        }
        
        return true;
    }else
    {
        return false;
    }
}

bool ShopBuy::init()
{
    if (!CCLayer::init())
    {
      
        return false;
    }
    this->setTouchEnabled(true);
    ShopInit();

	if (5 == currToshoW)
	{
		autoBuyFuhuo();
	}
    return true;
}

void ShopBuy::update(float dt)
{
    char moneyChar[20] = {0};
    sprintf(moneyChar,"x %d",KingData->getMoney());
    current_money_nuM->setText(moneyChar);
    if (KingData->getBazhinv() && duobi->getChildByTag(1001)==NULL)
    {
        addGoumai(duobi, CCPoint(88,88));
    }
    if (KingData->getBajiubei()&& shoushen->getChildByTag(1001)==NULL)
    {
        addGoumai(shoushen,  CCPoint(88,88));
    }
    if (KingData->getShoushen()&& fuhuo->getChildByTag(1001)==NULL )
    {
        addGoumai(fuhuo, CCPoint(88,88));
    }
	if (KingData->getJinjiDuobi() && nuqibao->getChildByTag(1001) == NULL)
	{
		addGoumai(nuqibao, CCPoint(88, 88));
	}

	if (KingData->getFuhuo() && yuanbao3->getChildByTag(1001)==NULL  )
	{
		addGoumai(yuanbao3, CCPoint(60, 48));
	}
    if (this->ispop2) {
        CCDirector::sharedDirector()->popScene();
    }
    
    if (this->ispop)
    {
        Role->fuhuo();
        CCDirector::sharedDirector()->popScene();
    }
}


void ShopBuy::ShopInit()
{
    
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
    
    
    ispop = false;
    ispop2 = false;
    Game::instance()->setShopLayer(this);
    this->scheduleUpdate();
    current_money = CCSprite::create("shop/scnl_qb.png");
    current_money_nuM = UILabel::create();
    current_money->addChild(current_money_nuM);
    current_money_nuM->setFontName("宋体");
    current_money_nuM->setColor(ccc3(0xe3, 0x9e, 0x78));
    current_money_nuM->setFontSize(16);
    current_money_nuM->setPosition(ccp(130,10));
    char moneyChar[20] = {0};
    sprintf(moneyChar,"x %d",KingData->getMoney());
    current_money_nuM->setText(moneyChar);
    this->addChild(current_money,200);
    current_money->setPosition(ccp(SIZE.width*0.7,SIZE.height*0.86));
    bg = CCScale9Sprite::create("shop/scnl_dk1.png");
    this->addChild(bg);
    bg->setPosition(ccp(SIZE.width*0.5325, SIZE.height/2));
    bg->setContentSize(CCSize(SIZE.width*0.8,SIZE.height*0.8));
    CCMenuItem* nengli = CCMenuItemImage::create( "shop/scnl_nl_down.png","shop/scnl_nl.png", "shop/scnl_nl.png",this, menu_selector(ShopBuy::qiehuanCallback));
    CCMenuItem* xuetong = CCMenuItemImage::create( "shop/scnl_xt_down.png","shop/scnl_xt.png","shop/scnl_xt.png", this, menu_selector(ShopBuy::qiehuanCallback));
    CCMenuItem* shangcheng = CCMenuItemImage::create( "shop/scnl_sc_down.png", "shop/scnl_sc.png","shop/scnl_sc.png", this, menu_selector(ShopBuy::qiehuanCallback));
    nengli->setEnabled(false);
    menus = CCArray::create();
    menus->retain();
    menus->addObject(nengli);
    menus->addObject(xuetong);
    menus->addObject(shangcheng);
    menu = CCMenu::create();
    this->addChild(menu);
    menu->setPosition(ccp(0,0));
    menu->addChild(shangcheng);
    menu->addChild(xuetong);
    menu->addChild(nengli);
    nengli->setPosition(ccp(SIZE.width*0.1,SIZE.height*0.64));
    xuetong->setPosition(ccp(SIZE.width*0.1,SIZE.height*0.47));
    shangcheng->setPosition(ccp(SIZE.width*0.1,SIZE.height*0.30));
    /*****    能力          *****/
    nengliNode = CCNode::create();
    this->addChild(nengliNode);
    nengliNode->setPosition(ccp(0, 0));
    CCScale9Sprite* bg1 = CCScale9Sprite::create("shop/scnl_dk2.png");
    nengliNode->addChild(bg1);
    bg1->setPosition(ccp(SIZE.width*0.37, SIZE.height/2));
    bg1->setContentSize(CCSize(SIZE.width*0.38,SIZE.height*0.6));
    CCScale9Sprite* bg2 = CCScale9Sprite::create("shop/scnl_dk2.png");
    nengliNode->addChild(bg2);
    bg2->setPosition(ccp(SIZE.width*0.73, SIZE.height/2));
    bg2->setContentSize(CCSize(SIZE.width*0.32,SIZE.height*0.6));
    CCSprite* nenglidescSprite = CCSprite::create("shop/scnl_dk3.png");
    nengliNode->addChild(nenglidescSprite);
    nenglidescSprite->setPosition(ccp(SIZE.width*0.735,SIZE.height*0.58));
    CCSize descSize = nenglidescSprite->getContentSize();
    nengliDescTitle = UILabel::create();
    nengliDescTitle->setFontName("宋体");
    nengliDescTitle->setColor(ccc3(0xe3, 0x9e, 0x78));
    nengliDescTitle->setFontSize(22);
    nengliDescTitle->setPosition(ccp(descSize.width/2, descSize.height-20));
    nengliDescTitle->setText(XXIconv::GBK2UTF( nenglidescTitle[0].c_str()));
    nenglidescSprite->addChild(nengliDescTitle);
    nengliDesc = UILabel::create();
    nengliDesc->setColor(ccc3(0xff, 0xae, 0x00));
    nengliDesc->setFontSize(16);
    nengliDesc->setFontName("宋体");
    nengliDesc->setPosition(ccp(descSize.width/2, descSize.height-34));
    nengliDesc->setText(XXIconv::GBK2UTF(nenglidescText[0].c_str()));
    nenglidescSprite->addChild(nengliDesc);
    nengliDesc->setTextAreaSize(CCSize(descSize.width-20,descSize.height-40));
    nengliDesc->setTextVerticalAlignment(kCCVerticalTextAlignmentTop);
    nengliDesc->setAnchorPoint(ccp(0.5,1));
    duobi = CCMenuItemImage::create("shop/scnl_jjdb.png", "shop/scnl_jjdb.png", this, menu_selector(ShopBuy::nengliCallback));
    shoushen = CCMenuItemImage::create("shop/scnl_ss.png", "shop/scnl_ss.png", this, menu_selector(ShopBuy::nengliCallback));
    fuhuo = CCMenuItemImage::create("shop/scnl_swfh.png", "shop/scnl_swfh.png", this, menu_selector(ShopBuy::nengliCallback));
    nuqibao = CCMenuItemImage::create("shop/scnl_nqb.png", "shop/scnl_nqb.png", this, menu_selector(ShopBuy::nengliCallback));
 
    nengliArr = CCArray::create();
    nengliArr->retain();
    nengliArr->addObject(duobi);
    nengliArr->addObject(shoushen);
    nengliArr->addObject(fuhuo);
    nengliArr->addObject(nuqibao);
    CCMenu* menuNengLiang = CCMenu::create();
    menuNengLiang->setPosition(ccp(0, 0));
    nengliNode->addChild(menuNengLiang);
    menuNengLiang->addChild(duobi);
    menuNengLiang->addChild(shoushen);
    menuNengLiang->addChild(fuhuo);
    menuNengLiang->addChild(nuqibao);
    duobi->setPosition(ccp(SIZE.width*0.28,SIZE.height*0.65));
    shoushen->setPosition(ccp(SIZE.width*0.46,SIZE.height*0.65));
    fuhuo->setPosition(ccp(SIZE.width*0.28,SIZE.height*0.35));
    nuqibao->setPosition(ccp(SIZE.width*0.46,SIZE.height*0.35));
    CCMenuItem* huode = CCMenuItemImage::create("shop/scnl_hd.png", "shop/scnl_hd_down.png", this, menu_selector(ShopBuy::huodenengli) );
    menuNengLiang->addChild(huode);
    huode->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.28));
    xuanzhongkuang = CCSprite::create("shop/scnl_xzk.png");
    xuanzhongkuang->setContentSize(duobi->getContentSize());
    xuanzhongkuang->runAction(CCRepeatForever::create(CCSequence::create( CCScaleBy::create(0.2, 1.1),CCScaleBy::create(0.2, 1/1.1) ,NULL ) ));
    nengliNode->addChild(xuanzhongkuang,1000);
    xuanzhongkuang->setPosition(duobi->getPosition());
    if(currToshoW == 5)
    {
       /* labelnuqi = UILabel::create();
        labelnuqi->setFontSize(25);
        labelnuqi->setColor(ccc3(0xff, 0xae, 0x00));
		labelnuqi->setText(XXIconv::GBK2UTF(TEXTINFOS[0].c_str()));
        addChild(labelnuqi,11,9900);
        labelnuqi->setPosition(ccp(SIZE.width*0.73, SIZE.height*0.45));
        
        xuanzhongkuang->setPosition(fuhuo->getPosition());
        if (gameLayer->mapThreeJuqing) {
             nengliDesc->setText(XXIconv::GBK2UTF(nenglidescText[4].c_str()));
            sprite = CCSprite::create("help11.png");
            sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.2f, ccp(0, 50)),CCMoveBy::create(0.2f, ccp(0, -50)),NULL)));
            nengliNode->addChild(sprite,9898);
            sprite->setScale(0.5f);
            sprite->setPosition(ccp(SIZE.width*0.73, SIZE.height*0.3));
        }else{
             nengliDesc->setText(XXIconv::GBK2UTF( nenglidescText[2].c_str()));
        }
        nengliDescTitle->setText(XXIconv::GBK2UTF( nenglidescTitle[2].c_str()));
        nengliSort = 2;*/
    }else if (currToshoW == 3)
    {
//        labelnuqi = UILabel::create();
//        labelnuqi->setFontSize(25);
//        labelnuqi->setColor(ccc3(0xff, 0xae, 0x00));
//		labelnuqi->setText(XXIconv::GBK2UTF(TEXTINFOS[0].c_str()));
//        addChild(labelnuqi,11,9900);
//        labelnuqi->setPosition(ccp(SIZE.width*0.73, SIZE.height*0.45));
////        addTip("首次免费购买");
//        sprite = CCSprite::create("help11.png");
//        sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, 30)),CCMoveBy::create(0.3f, ccp(0, -30)),NULL)));
//        sprite->setPosition(ccp(SIZE.width*0.73, SIZE.height*0.35));
//        sprite->setScale(0.5f);
//    
//        addChild(sprite,2002);
//        
//        xuanzhongkuang->setPosition(nuqibao->getPosition());
//        nengliDesc->setText(XXIconv::GBK2UTF( nenglidescText[3].c_str()));
//        nengliDescTitle->setText(XXIconv::GBK2UTF( nenglidescTitle[3].c_str()));
//        nengliSort = 3;
		sprite = CCSprite::create("help11.png");
		sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, 30)), CCMoveBy::create(0.3f, ccp(0, -30)), NULL)));
		sprite->setPosition(ccp(SIZE.width*0.10, SIZE.height*0.35));

		sprite->setScale(0.5f);
		addChild(sprite, 2002);
		xuanzhongkuang->setVisible(false);
    }else if (currToshoW == 20)
    {
     
        sprite = CCSprite::create("help11.png");
        sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, 30)),CCMoveBy::create(0.3f, ccp(0, -30)),NULL)));
        sprite->setPosition(ccp(SIZE.width*0.10, SIZE.height*0.55));
    
        sprite->setScale(0.5f);
        addChild(sprite,2002);
		xuanzhongkuang->setVisible(false);
    }else if (currToshoW == 30)
    {
        this->setVisible(false);
        showInfo(BUY_Nuqi);
//        xuanzhongkuang->setPosition(nuqibao->getPosition());
//        nengliDesc->setText(nenglidescText[3]);
//        nengliDescTitle->setText(nenglidescTitle[3]);
//        nengliSort = 3;
    }
    
    /*****    血统          *****/
    xuetogNode = CCNode::create();
    this->addChild(xuetogNode);
    xuetogNode->setPosition(ccp(0, 0));
    CCMenu* menuXuetong = CCMenu::create();
    menuXuetong->setPosition(ccp(0, 0));
    xuetogNode->addChild(menuXuetong);
    CCSprite* bashen = CCSprite::create("shop/scxt_rw.png");
    xuetogNode->addChild(bashen);
    bashen->setPosition(ccp(SIZE.width*0.3,SIZE.height*0.5));
    CCSprite* shengmingtiao = CCSprite::create("shop/scxt_k1.png");
    CCSprite* gongjitiao = CCSprite::create("shop/scxt_k1.png");
    CCSprite* fangyutiao = CCSprite::create("shop/scxt_k1.png");
    CCSprite* nuqitiao = CCSprite::create("shop/scxt_k1.png");
    xuetogNode->addChild(shengmingtiao);
    xuetogNode->addChild(gongjitiao);
    xuetogNode->addChild(fangyutiao);
    xuetogNode->addChild(nuqitiao);
    shengmingtiao->setPosition(ccp(SIZE.width*0.55, SIZE.height*0.7));
    gongjitiao->setPosition(ccp(SIZE.width*0.61, SIZE.height*0.58));
    fangyutiao->setPosition(ccp(SIZE.width*0.58, SIZE.height*0.46));
    nuqitiao->setPosition(ccp(SIZE.width*0.55, SIZE.height*0.34));
    UILabel* shengminglabel = UILabel::create();
    UILabel* gongjitiaolabel = UILabel::create();
    UILabel* fangyutiaolabel = UILabel::create();
    UILabel* nuqitiaolabel = UILabel::create();
    shengminglabel->setText(XXIconv::GBK2UTF(TEXTINFOS[1].c_str()));
    gongjitiaolabel->setText(XXIconv::GBK2UTF( TEXTINFOS[2].c_str()));
    fangyutiaolabel->setText(XXIconv::GBK2UTF( TEXTINFOS[3].c_str()));
    nuqitiaolabel->setText(XXIconv::GBK2UTF( TEXTINFOS[4].c_str()));
    CCArray* labelarr = CCArray::create();
    labelarr->addObject(shengminglabel);
    labelarr->addObject(gongjitiaolabel);
    labelarr->addObject(fangyutiaolabel);
    labelarr->addObject(nuqitiaolabel);
    CCObject* object;
    CCARRAY_FOREACH(labelarr, object)
    {
        UILabel* label = dynamic_cast<UILabel*>(object);
        label->setColor(ccc3(0xff, 0xae, 0x00));
        label->setFontSize(16);
        label->setFontName("宋体");
        label->setPosition(ccp(55, 17));
    }
    shengmingtiao->addChild(shengminglabel);
    gongjitiao->addChild(gongjitiaolabel);
    fangyutiao->addChild(fangyutiaolabel);
    nuqitiao->addChild(nuqitiaolabel);
    shengmingbash = CCSpriteBatchNode::create("shop/scxt_bs1.png");
    gongjibash = CCSpriteBatchNode::create("shop/scxt_bs2.png");
    fangyubash = CCSpriteBatchNode::create("shop/scxt_bs3.png");
    nuqibash = CCSpriteBatchNode::create("shop/scxt_bs4.png");
    shengmingtiao->addChild(shengmingbash);
    gongjitiao->addChild(gongjibash);
    fangyutiao->addChild(fangyubash);
    nuqitiao->addChild(nuqibash);
    shengmingbash->setPosition(ccp(70, 12));
    gongjibash->setPosition(ccp(70, 12));
    fangyubash->setPosition(ccp(70, 12));
    nuqibash->setPosition(ccp(70, 12));
    for (int i=1; i<=KingData->getShengmingLevel(); i++)
    {
        CCSprite* shengmingdou =CCSprite::createWithTexture(shengmingbash->getTexture());
        shengmingbash->addChild(shengmingdou);
        shengmingdou->setPosition(ccp(1*i*shengmingdou->getContentSize().width,0));
    }
    for (int i=1; i<= KingData->getGongjiLevel(); i++)
    {
        CCSprite* gongjidou =CCSprite::createWithTexture(gongjibash->getTexture());
        gongjibash->addChild(gongjidou);
        gongjidou->setPosition(ccp(1*i*gongjidou->getContentSize().width,0));
    }
    for (int i=1; i<= KingData->getFangyuLevel(); i++)
    {
        CCSprite* fangyudou =CCSprite::createWithTexture(fangyubash->getTexture());
        fangyubash->addChild(fangyudou);
        fangyudou->setPosition(ccp(1*i*fangyudou->getContentSize().width,0));
    }
    for (int i=1; i<= KingData->getNuqiLevel(); i++)
    {
        CCSprite* nuqidou =CCSprite::createWithTexture(nuqibash->getTexture());
        nuqibash->addChild(nuqidou);
        nuqidou->setPosition(ccp(1*i*nuqidou->getContentSize().width,0));
    }
    
    CCMenuItem* shengmingAdd = CCMenuItemImage::create("shop/scxt_jh.png", "shop/scxt_jh_down.png", this, menu_selector(ShopBuy::addCallback));
    CCMenuItem* gongjiAdd = CCMenuItemImage::create("shop/scxt_jh.png", "shop/scxt_jh_down.png", this, menu_selector(ShopBuy::addCallback));
    CCMenuItem* fangyuAdd = CCMenuItemImage::create("shop/scxt_jh.png", "shop/scxt_jh_down.png", this, menu_selector(ShopBuy::addCallback));
    CCMenuItem* nuqiAdd = CCMenuItemImage::create("shop/scxt_jh.png", "shop/scxt_jh_down.png", this, menu_selector(ShopBuy::addCallback));
  
    shengmingAdd->setOpacity(0);
    gongjiAdd->setOpacity(0);
    fangyuAdd->setOpacity(0);
    nuqiAdd->setOpacity(0);
    
    shengmingAdd->setScale(2.0);
    gongjiAdd->setScale(2.0);
    fangyuAdd->setScale(2.0);
    nuqiAdd->setScale(2.0);
    
    CCMenuItem* shengmingAdd1 = CCMenuItemImage::create("shop/scxt_jh.png", "shop/scxt_jh_down.png");
    CCMenuItem* gongjiAdd1 = CCMenuItemImage::create("shop/scxt_jh.png", "shop/scxt_jh_down.png");
    CCMenuItem* fangyuAdd1 = CCMenuItemImage::create("shop/scxt_jh.png", "shop/scxt_jh_down.png");
    CCMenuItem* nuqiAdd1 = CCMenuItemImage::create("shop/scxt_jh.png", "shop/scxt_jh_down.png");

    xuetongAdd = CCArray::create();
    xuetongAdd->retain();
    xuetongAdd->addObject(shengmingAdd);
    xuetongAdd->addObject(gongjiAdd);
    xuetongAdd->addObject(fangyuAdd);
    xuetongAdd->addObject(nuqiAdd);
    menuXuetong->addChild(shengmingAdd);
    menuXuetong->addChild(gongjiAdd);
    menuXuetong->addChild(fangyuAdd);
    menuXuetong->addChild(nuqiAdd);
    shengmingAdd->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.685));
    gongjiAdd->setPosition(ccp(SIZE.width*0.78,SIZE.height*0.565));
    fangyuAdd->setPosition(ccp(SIZE.width*0.75,SIZE.height*0.445));
    nuqiAdd->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.325));
    
    menuXuetong->addChild(shengmingAdd1);
    menuXuetong->addChild(gongjiAdd1);
    menuXuetong->addChild(fangyuAdd1);
    menuXuetong->addChild(nuqiAdd1);
    shengmingAdd1->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.685));
    gongjiAdd1->setPosition(ccp(SIZE.width*0.78,SIZE.height*0.565));
    fangyuAdd1->setPosition(ccp(SIZE.width*0.75,SIZE.height*0.445));
    nuqiAdd1->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.325));
    
    CCSprite* shengmingMoney = CCSprite::create("shop/scxt_jbk.png");
    CCSprite* gongjiMoney = CCSprite::create("shop/scxt_jbk.png");
    CCSprite* fangyuMoney = CCSprite::create("shop/scxt_jbk.png");
    CCSprite* nuqiMoney = CCSprite::create("shop/scxt_jbk.png");
    xuetogNode->addChild(shengmingMoney);
    xuetogNode->addChild(gongjiMoney);
    xuetogNode->addChild(fangyuMoney);
    xuetogNode->addChild(nuqiMoney);
    shengmingMoney->setPosition(ccp(SIZE.width*0.80, SIZE.height*0.685));
    gongjiMoney->setPosition(ccp(SIZE.width*0.86, SIZE.height*0.565));
    fangyuMoney->setPosition(ccp(SIZE.width*0.84, SIZE.height*0.445));
    nuqiMoney->setPosition(ccp(SIZE.width*0.80, SIZE.height*0.325));
    shengminglabel->setText(XXIconv::GBK2UTF( TEXTINFOS[1].c_str()));
    gongjitiaolabel->setText(XXIconv::GBK2UTF( TEXTINFOS[2].c_str()));
    fangyutiaolabel->setText(XXIconv::GBK2UTF( TEXTINFOS[3].c_str()));
    nuqitiaolabel->setText(XXIconv::GBK2UTF( TEXTINFOS[4].c_str()));
    shengmingMoneylabel = UILabel::create();
    gongjitiaoMoneylabel = UILabel::create();
    fangyutiaoMoneylabel = UILabel::create();
    nuqitiaoMoneylabel = UILabel::create();
    CCArray* labelarrMoney = CCArray::create();
    labelarrMoney->addObject(shengmingMoneylabel);
    labelarrMoney->addObject(gongjitiaoMoneylabel);
    labelarrMoney->addObject(fangyutiaoMoneylabel);
    labelarrMoney->addObject(nuqitiaoMoneylabel);
    CCObject* objectMoney;
    CCARRAY_FOREACH(labelarrMoney, objectMoney)
    {
        UILabel* label = dynamic_cast<UILabel*>(objectMoney);
        label->setColor(ccc3(0xff, 0xae, 0x00));
        label->setFontSize(16);
        label->setFontName("宋体");
        label->setPosition(ccp(30, 10));
    }
    char moneyChar2[10] = {0};
    sprintf(moneyChar2, "- %d",200*(1+KingData->getShengmingLevel()));
    shengmingMoneylabel->setText(moneyChar2);
    if(KingData->getShengmingLevel()>=10)
    {
        shengmingMoneylabel->setText(XXIconv::GBK2UTF(TEXTINFOS[5].c_str()));
    }
    sprintf(moneyChar2, "- %d", 200+400*(KingData->getGongjiLevel()-1 ));
    gongjitiaoMoneylabel->setText(moneyChar2);
    if(KingData->getGongjiLevel()>=10)
    {
		gongjitiaoMoneylabel->setText(XXIconv::GBK2UTF(TEXTINFOS[5].c_str()));
    }
    sprintf(moneyChar2, "- %d",200*(1+KingData->getFangyuLevel()));
    fangyutiaoMoneylabel->setText(moneyChar2);
    
    if(KingData->getFangyuLevel()>=10)
    {
		fangyutiaoMoneylabel->setText(XXIconv::GBK2UTF(TEXTINFOS[5].c_str()));
    }
    sprintf(moneyChar2, "- %d",500*(KingData->getNuqiLevel()+1-2));
    nuqitiaoMoneylabel->setText(moneyChar2);
    if(KingData->getNuqiLevel()>=5)
    {
		nuqitiaoMoneylabel->setText(XXIconv::GBK2UTF(TEXTINFOS[5].c_str()));
    }
    shengmingMoney->addChild(shengmingMoneylabel);
    gongjiMoney->addChild(gongjitiaoMoneylabel);
    fangyuMoney->addChild(fangyutiaoMoneylabel);
    nuqiMoney->addChild(nuqitiaoMoneylabel);
    
    /*****    商城           *****/
    shangchengNode = CCNode::create();
    this->addChild(shangchengNode);
    shangchengNode->setPosition(ccp(0, 0));
    CCScale9Sprite* shangchengbg1 = CCScale9Sprite::create("shop/scnl_dk2.png");
    shangchengNode->addChild(shangchengbg1);
    shangchengbg1->setPosition(ccp(SIZE.width*0.37, SIZE.height/2));
    shangchengbg1->setContentSize(CCSize(SIZE.width*0.38,SIZE.height*0.64));
    CCScale9Sprite* shangchengbg2 = CCScale9Sprite::create("shop/scnl_dk2.png");
    shangchengNode->addChild(shangchengbg2);
    shangchengbg2->setPosition(ccp(SIZE.width*0.735, SIZE.height/2));
    shangchengbg2->setContentSize(CCSize(SIZE.width*0.32,SIZE.height*0.64));
    CCMenuItem* yuanbao1 = CCMenuItemImage::create("shop/scsc_tb1.png","shop/scsc_tb1.png", this, menu_selector(ShopBuy::shopCallback));
    CCMenuItem* yuanbao2 = CCMenuItemImage::create("shop/scsc_tb2.png", "shop/scsc_tb2.png", this, menu_selector(ShopBuy::shopCallback));
    yuanbao3 = CCMenuItemImage::create("shop/scsc_tb3.png","shop/scsc_tb3.png", this, menu_selector(ShopBuy::shopCallback));
    yuanbao4 = CCMenuItemImage::create("shop/scsc_tb4.png", "shop/scsc_tb4.png", this, menu_selector(ShopBuy::shopCallback));
    CCMenuItem* yuanbao5 = CCMenuItemImage::create("shop/scsc_cjdlb1.png", "shop/scsc_cjdlb1.png", this, menu_selector(ShopBuy::shopCallback));
    shopArr = CCArray::create();
    shopArr->retain();
    shopArr->addObject(yuanbao1);
    shopArr->addObject(yuanbao2);
    shopArr->addObject(yuanbao3);
    shopArr->addObject(yuanbao4);
    shopArr->addObject(yuanbao5);
    CCMenu* menuShop = CCMenu::create();
    menuShop->setPosition(ccp(0, 0));
    shangchengNode->addChild(menuShop);
    menuShop->addChild(yuanbao1);
    menuShop->addChild(yuanbao2);
    menuShop->addChild(yuanbao3);
    menuShop->addChild(yuanbao4);
    menuShop->addChild(yuanbao5);
    yuanbao1->setPosition(ccp(SIZE.width*0.28,SIZE.height*0.70));
    yuanbao2->setPosition(ccp(SIZE.width*0.46,SIZE.height*0.70));
    yuanbao3->setPosition(ccp(SIZE.width*0.28,SIZE.height*0.50));
    yuanbao4->setPosition(ccp(SIZE.width*0.46,SIZE.height*0.50));
    yuanbao5->setPosition(ccp(SIZE.width*0.37,SIZE.height*0.30));
    CCMenuItem* huode2 = CCMenuItemImage::create("shop/scnl_hd.png", "shop/scnl_hd_down.png", this, menu_selector(ShopBuy::huodeShop) );
    menuShop->addChild(huode2);
    huode2->setPosition(ccp(SIZE.width*0.72,SIZE.height*0.28));
    xuanzhongkuang2 = CCSprite::create("shop/scnl_xzk.png");
    xuanzhongkuang2->setScale(0.75);
    xuanzhongkuang2->runAction(CCRepeatForever::create(CCSequence::create( CCScaleBy::create(0.2, 1.1),CCScaleBy::create(0.2, 1/1.1) ,NULL ) ));
    shangchengNode->addChild(xuanzhongkuang2,1000);
    xuanzhongkuang2->setPosition(yuanbao1->getPosition());
    xuanzhongkuang3 = CCSprite::create("shop/scnl_xzk.png");
    xuanzhongkuang3->setScaleX(2.0);
    xuanzhongkuang3->setScaleY(0.75);
    xuanzhongkuang3->runAction(CCRepeatForever::create(CCSequence::create( CCScaleBy::create(0.2, 1.1),CCScaleBy::create(0.2, 1/1.1) ,NULL ) ));
    shangchengNode->addChild(xuanzhongkuang3,1000);
    xuanzhongkuang3->setPosition(yuanbao5->getPosition());
    xuanzhongkuang3->setVisible(false);
    CCSprite* shopdescSprite = CCSprite::create("shop/scnl_dk3.png");
    shangchengNode->addChild(shopdescSprite);
    shopdescSprite->setPosition(ccp(SIZE.width*0.735,SIZE.height*0.60));
    CCSize descSize2 = shopdescSprite->getContentSize();
    shopDescTitle = UILabel::create();
    shopDescTitle->setColor(ccc3(0xe3, 0x9e, 0x78));
    shopDescTitle->setFontSize(22);
    shopDescTitle->setFontName("宋体");
    shopDescTitle->setPosition(ccp(descSize.width/2, descSize.height-20));
	shopDescTitle->setText(XXIconv::GBK2UTF(shopdescTitle[0].c_str()));
    shopdescSprite->addChild(shopDescTitle);
    shopDesc = UILabel::create();
    shopDesc->setColor(ccc3(0xff, 0xae, 0x00));
    shopDesc->setFontSize(16);
    shopDesc->setFontName("宋体");
    shopDesc->setPosition(ccp(descSize.width/2, descSize.height-44));
	shopDesc->setText(XXIconv::GBK2UTF(shopdescText[0].c_str()));
    shopdescSprite->addChild(shopDesc);
    shopDesc->setTextAreaSize(CCSize(descSize.width-20,descSize.height-40));
    shopDesc->setTextVerticalAlignment(kCCVerticalTextAlignmentTop);
    shopDesc->setAnchorPoint(ccp(0.5,1));
    
    if (currToshoW == 10) {
        nengliNode->setVisible(false);
        xuetogNode->setVisible(true);
        shangchengNode->setVisible(false);
        sprite = CCSprite::create("help11.png");
        sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.2f, ccp(0, 50)),CCMoveBy::create(0.2f, ccp(0, -50)),NULL)));
        xuetogNode->addChild(sprite,1,9898);
        sprite->setPosition(ccp(SIZE.width*0.7, SIZE.height*0.6));
    }else if (currToshoW == 100)
    {
        nengliNode->setVisible(false);
        xuetogNode->setVisible(true);
        shangchengNode->setVisible(false);
    }else
    {
        nengliNode->setVisible(true);
        xuetogNode->setVisible(false);
        shangchengNode->setVisible(false);
    }
    
    CCMenuItemImage* xiaocha = CCMenuItemImage::create("shop/scnl_gb.png", "shop/scnl_gb_down.png", this,  menu_selector(ShopBuy::resume));
    menu->addChild(xiaocha);
    xiaocha->setPosition(ccp(SIZE.width*0.915,SIZE.height*0.845));
}

void ShopBuy::addCallback(CCObject* pSender)
{
    if (currToshoW == 21)
    {
        return;
    }
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
    int order = xuetongAdd->indexOfObject(pSender);
    int money = KingData->getMoney();
    if(order==0)
    {
        if (currToshoW == 10)
        {
            return;
        }
        if (currToshoW == 20)
        {
            return;
        }
        int level = KingData->getShengmingLevel();
        if (level>=10)
        {
          //  showInfo(0);
        }else if(money < 200*(level+1))
        {
            qiehuanCallback(2);   ///////////////
           // showInfo(1);
        }else
        {
            KingData->alterMoney(-200*(level+1));
            KingData->alterShengMingLevel();
            CCSprite* shengmingdou =CCSprite::createWithTexture(shengmingbash->getTexture());
            shengmingbash->addChild(shengmingdou);
            shengmingdou->setPosition(ccp(1*(KingData->getShengmingLevel())*shengmingdou->getContentSize().width,0));
        }
    }
    else if (order == 1)
    {
        if (currToshoW == 20)
        {
            

            resetTip();
            sprite->setRotation(180);
            sprite->setPosition(ccp(SIZE.width*0.92, SIZE.height*0.78));
            currToshoW = 21;
            xuetogNode->removeChildByTag(9898, true);
            KingData->alterGongJiLevel();
            CCSprite* gongjidou =CCSprite::createWithTexture(gongjibash->getTexture());
            gongjibash->addChild(gongjidou);
            gongjidou->setPosition(ccp(1*(KingData->getGongjiLevel())*gongjidou->getContentSize().width,0));
            
        }else
        {
            int level = KingData->getGongjiLevel();
            if (level>=10)
            {
               // showInfo(2);
                            
            }else if (money < 200+ 400*(level-1))
            {
                qiehuanCallback(2);   ///////////////
             //   showInfo(3);
                
            }else
            {
                KingData->alterMoney(-(200+ 400*(level-1)));
                KingData->alterGongJiLevel();
                CCSprite* gongjidou =CCSprite::createWithTexture(gongjibash->getTexture());
                gongjibash->addChild(gongjidou);
                gongjidou->setPosition(ccp(1*(KingData->getGongjiLevel())*gongjidou->getContentSize().width,0));
            }
        }
    }
    else if (order == 2)
    {
        if (currToshoW == 10)
        {
            return;
        }
        if (currToshoW == 20)
        {
            return;
        }
        
        int level = KingData->getFangyuLevel();
        if (level>=10)
        {
          //  showInfo(4);
        }else if (money < 200*(level+1))
        {
             qiehuanCallback(2);   ///////////////
           //  showInfo(5);
            
        }else
        {
            KingData->alterMoney(-200*(level+1));
            KingData->alterFangyuLevel();
            CCSprite* fangyudou =CCSprite::createWithTexture(fangyubash->getTexture());
            fangyubash->addChild(fangyudou);
            fangyudou->setPosition(ccp(1*(KingData->getFangyuLevel())*fangyudou->getContentSize().width,0));
        }
    }
    else if (order == 3)
    {
        if (currToshoW == 10)
        {
            return;
        }
        if (currToshoW == 20)
        {
            return;
        }
        
        int level = KingData->getNuqiLevel();
        if (level<2) {
            return;
        }
        if (level>=5) {
           // showInfo(6);
           
        }else if (money < 500*(level-1))
        {
           // showInfo(7);
            qiehuanCallback(2);   ///////////////
        }else
        {
            KingData->alterMoney(-500*(level-1));
            KingData->alterNuqiLevel();
            CCSprite* nuqidou =CCSprite::createWithTexture(nuqibash->getTexture());
            nuqibash->addChild(nuqidou);
            nuqidou->setPosition(ccp(1*(KingData->getNuqiLevel())*nuqidou->getContentSize().width,0));
        }
    }
    char moneyChar2[10] = {0};
    sprintf(moneyChar2, "- %d",200*(1+KingData->getShengmingLevel()));
    shengmingMoneylabel->setText(moneyChar2);
    if(KingData->getShengmingLevel()>=10)
    {
		shengmingMoneylabel->setText(XXIconv::GBK2UTF(TEXTINFOS[5].c_str()));
    }
    sprintf(moneyChar2, "- %d", 200+400*(KingData->getGongjiLevel()-1 ));
    gongjitiaoMoneylabel->setText(moneyChar2);
    if(KingData->getGongjiLevel()>=10)
    {
		gongjitiaoMoneylabel->setText(XXIconv::GBK2UTF(TEXTINFOS[5].c_str()));
    }
    sprintf(moneyChar2, "- %d",200*(1+KingData->getFangyuLevel()));
    fangyutiaoMoneylabel->setText(moneyChar2);
    
    if(KingData->getFangyuLevel()>=10)
    {
		fangyutiaoMoneylabel->setText(XXIconv::GBK2UTF(TEXTINFOS[5].c_str()));
    }
    sprintf(moneyChar2, "- %d",500*(KingData->getNuqiLevel()+1-2));
    nuqitiaoMoneylabel->setText(moneyChar2);
    if(KingData->getNuqiLevel()>=5)
    {
		nuqitiaoMoneylabel->setText(XXIconv::GBK2UTF(TEXTINFOS[5].c_str()));
    }
    
  

}

void ShopBuy::showInfo(int id)
{
	CCString* str=CCString::createWithFormat("%d",id);
	
	openalertJni::payRequest(std::string(str->getCString()));

}



void ShopBuy::resume(CCObject*)
{
    if (currToshoW == 3)
    {
        return;
    }
    
    if (currToshoW == 10)
    {
        return;
    }
    if (currToshoW == 20)
    {
        return;
    }
    
    PersonalAudioEngine::sharedEngine()->playEffect("music/backSound.wav");
    
    if (gameLayer!=NULL&& gameLayer->mapThreeJuqing&& Role->isDie)
    {
        return;
    }
    if(Role!=NULL &&Role->isDie)
    {
        Role->abDie = true;
        CCDirector::sharedDirector()->popScene();
        return;
    }
    CCDirector::sharedDirector()->popScene();
}

void ShopBuy::nengliCallback(CCObject* pSender)
{
   
    if (currToshoW == 3)
    {
        return;
    }
    if (currToshoW == 20)
    {
        return;
    }
    if (currToshoW == 21)
    {
        return;
    }
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
    if (gameLayer!=NULL&& gameLayer->mapThreeJuqing)
    {
        return;
    }
    CCMenuItem* m_item = dynamic_cast<CCMenuItem*>(pSender);
    nengliSort = nengliArr->indexOfObject(m_item);
    xuanzhongkuang->setPosition(m_item->getPosition());
	nengliDesc->setText(XXIconv::GBK2UTF(nenglidescText[nengliSort].c_str()));
	nengliDescTitle->setText(XXIconv::GBK2UTF(nenglidescTitle[nengliSort].c_str()));
}

void ShopBuy::autoBuyFuhuo()
{
	qiehuanCallback(2);
}


void ShopBuy::qiehuanCallback(int index)
{
    CCObject* p = menus->objectAtIndex(2);
    qiehuanCallback(p);
}

void ShopBuy::qiehuanCallback(CCObject* pSender)
{
   
    if (gameLayer!=NULL&& gameLayer->mapThreeJuqing)
    {
        return;
    }
	if (currToshoW == 5)
	{
		if (!KingData->getFirstFuHuo())
		{
			labelnuqi = UILabel::create();
			labelnuqi->setFontSize(20);
			labelnuqi->setColor(ccc3(0xff, 0xae, 0x00));
			labelnuqi->setText(XXIconv::GBK2UTF(TEXTINFOS[0].c_str()));
			addChild(labelnuqi, 11, 9900);
			labelnuqi->setPosition(ccp(SIZE.width*0.73, SIZE.height*0.45));
		}
		xuanzhongkuang2->setPosition(yuanbao3->getPosition());
		shopSort = 2;

		shopDescTitle->setText(XXIconv::GBK2UTF(shopdescTitle[shopSort].c_str()));
		shopDesc->setText(XXIconv::GBK2UTF(shopdescText[shopSort].c_str()));
	}

	

	
    
    if (currToshoW == 10)
    {
        return;
    }
    if (currToshoW == 21)
    {
        return;
    }
    CCMenuItem* m_item = dynamic_cast<CCMenuItem*>(pSender);
    int sort = menus->indexOfObject(m_item);
    
    if (currToshoW == 20 && sort!=1)
    {
        return;
    }
   
	if (currToshoW == 3 && sort != 2)
	{
		return;
	}

	if (currToshoW == 3)
	{
		sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, 30)), CCMoveBy::create(0.3f, ccp(0, -30)), NULL)));
		sprite->setPosition(ccp(SIZE.width*0.73, SIZE.height*0.35));
		sprite->setScale(0.5f);

		shopSort = 3;


		xuanzhongkuang2->setPosition(yuanbao4->getPosition());
		xuanzhongkuang3->setVisible(false);
		xuanzhongkuang2->setVisible(true);

		shopDescTitle->setText(XXIconv::GBK2UTF(shopdescTitle[shopSort].c_str()));
		shopDesc->setText(XXIconv::GBK2UTF(shopdescText[shopSort].c_str()));
	}


    CCObject* obj;
    CCARRAY_FOREACH(menus, obj)
    {
        CCMenuItem* m_item = dynamic_cast<CCMenuItem*>(obj);
        m_item->setEnabled(true);
        m_item->setZOrder(1000-menus->indexOfObject(obj));
    }

    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
    m_item->setEnabled(false);
    m_item->setZOrder(1001);
    if(sort == 0)
    {
        nengliNode->setVisible(true);
        xuetogNode->setVisible(false);
        shangchengNode->setVisible(false);

    }else if (sort == 1)
    {
        
        if (currToshoW == 20)
        {
			addTip(TEXTINFOS[0].c_str());
            sprite->setPosition(ccp(SIZE.width*0.78, SIZE.height*0.65));
            sprite->setScale(0.4f);
        }
        
        nengliNode->setVisible(false);
        xuetogNode->setVisible(true);
        shangchengNode->setVisible(false);

    }else if (sort == 2)
    {
        nengliNode->setVisible(false);
        xuetogNode->setVisible(false);
        shangchengNode->setVisible(true);
    }
}

void ShopBuy::shopCallback(CCObject* pSender)
{
    if (currToshoW == 21)
    {
        return;
    }

	if (currToshoW == 3)
	{
		return;
	}
	


    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
    CCMenuItem* m_item = dynamic_cast<CCMenuItem*>(pSender);
    shopSort =  shopArr->indexOfObject(m_item);
    if(shopSort == 4)
    {
		//屏蔽大礼包
			return;
		
        xuanzhongkuang3->setVisible(true);
        xuanzhongkuang2->setVisible(false);
    }else
    {
        xuanzhongkuang2->setPosition(m_item->getPosition());
        xuanzhongkuang3->setVisible(false);
        xuanzhongkuang2->setVisible(true);
    }
	shopDescTitle->setText(XXIconv::GBK2UTF(shopdescTitle[shopSort].c_str()));
	shopDesc->setText(XXIconv::GBK2UTF(shopdescText[shopSort].c_str()));
}

void ShopBuy::huodenengli(CCObject* pSender)
{
     if (currToshoW == 20||currToshoW==3)
    {
        return;
    }
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
    if (gameLayer!=NULL&& gameLayer->mapThreeJuqing)
    {
        Role->fuhuo();
        gameLayer->juqingThreeEnd();
        CCDirector::sharedDirector()->popScene();
        return;
    }
    //if (currToshoW == 3)
    //{
    // //   labelnuqi->setVisible(false);
    //   
    //    resetTip();
    //    KingData->setExtraNuqi(KingData->getExtraNuqi()+1000);
    //    sprite->setRotation(180);
    //    sprite->setScale(0.5);
    //    sprite->setPosition(ccp(SIZE.width*0.92, SIZE.height*0.78));
    //    currToshoW = 21;
    //}
    if (currToshoW == 21)
    {
        return;
    }
	bool isGet = false;
    switch (nengliSort) {
        case 0:
        {
           // bool isGet = KingData->getJinjiDuobi();
			isGet = KingData->getBazhinv();
            if (isGet)
            {
                
            }else
            {
                showInfo(BUY_Bazhinv);
            }
            break;
        }
        case 1:
        {
			isGet = KingData->getBajiubei();
            if (isGet)
            {
                
            }else
            {
                showInfo(BUY_Bajiubei);
            }
            break;
        }
        case 2:
        {
			//左下
           // bool isGet = KingData->getFuhuo();
			bool isGet = KingData->getShoushen();
			if (!isGet)
			{
				showInfo(BUY_Shoushen);
			}

           /* if (isGet)
            {
                showInfo(17);
               
            }else
            {
                showInfo(10);
            }*/
            break;
        }
        case 3:
        {
			bool isGet = KingData->getJinjiDuobi();
			if (!isGet)
			{
				showInfo(BUY_JinjiDuobi);
			}

            //if (KingData->getMoney()>=1000)
            //{
            //    KingData->setMoney(KingData->getMoney()-1000);
            //    KingData->setExtraNuqi(KingData->getExtraNuqi()+1000);
            //    showInfo(11);
            //}else
            //{
            //    qiehuanCallback(2);   ///////////////
            //    showInfo(1);
            //}
            break;
        }
        default:
            break;
    }
}

void ShopBuy::huodeShop(CCObject* pSender)
{
    if (currToshoW == 21)
    {
        return;
    }
    if (currToshoW == 20)
    {
        return;
    }
    PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
    switch (shopSort) {
        case 0:
        {
            showInfo(BUY_Money1888);
            break;
        }
        case 1:
        {
            showInfo(BUY_Money18888);
            break;
        }
        case 2:
        {
			if (currToshoW == 5 && !KingData->getFirstFuHuo())
			{
				KingData->setFirstFuHuo(true);
				GlobleUnits::getInstance()->paySuccess(BUY_Fuhuo);
			}
			else if (!KingData->getFuhuo())
					showInfo(BUY_Fuhuo);
            break;
        }
        case 3:
        {
			if (currToshoW == 3)
				GlobleUnits::getInstance()->paySuccess(BUY_Nuqi);
			else
				showInfo(BUY_Nuqi);
           // KingData->setExtraNuqi(KingData->getExtraNuqi()+3500);
            break;
        }
        /*case 4:
        {
            showInfo(16);
            KingData->alterMoney(8888);
            KingData->setExtraNuqi(KingData->getExtraNuqi()+5000);
            KingData->setJinjiDuobi(true);
            KingData->setShoushen(true);
            KingData->setFuhuo(true);
            break;
        }*/
        default:
            break;
    }
}

CCScene* ShopBuy::scene(CCRenderTexture *sqr, bool isFlip )
{
    CCScene *scene = CCScene::create();
    ShopBuy* layer = ShopBuy::create();
    scene->addChild(layer,100);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
    _spr->setPosition(ccp(size.width / 2, size.height / 2));
    _spr->setFlipY(true);  //是否翻转
    _spr->setColor(ccGRAY);  //颜色（变灰暗）
    scene->addChild(_spr);
    return scene;
}

CCScene* ShopBuy::scene()
{
    CCScene *scene = CCScene::create();
    ShopBuy* layer = ShopBuy::create();
    scene->addChild(layer,100);
   // CCSize size = CCDirector::sharedDirector()->getWinSize();
    return scene;
}

CCScene* ShopBuy::scene(CCRenderTexture *sqr, bool isFlip ,int currToshoW)
{
    CCScene *scene = CCScene::create();
    ShopBuy* layer = ShopBuy::create(currToshoW);
    scene->addChild(layer,100);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
    _spr->setPosition(ccp(size.width / 2, size.height / 2));
    _spr->setFlipY(true);  //是否翻转
    _spr->setColor(ccGRAY);  //颜色（变灰暗）
    scene->addChild(_spr);
    return scene;
}

ShopBuy* ShopBuy::create(int currToshoW)
{
    ShopBuy* shopBuy = new ShopBuy();
    shopBuy->autorelease();
    shopBuy->init(currToshoW);
    return shopBuy;
}

bool ShopBuy::init(int currToshoW)
{
    this->currToshoW = currToshoW;
    this->init();
    return true;
}

void ShopBuy::addGoumai(CCNode* n,CCPoint p)
{
    CCSprite* s = CCSprite::create("shop/yihuode.png");
    n->addChild(s,1,1001);
    s->setPosition(p);
    s->setScale(0.5);
}

void ShopBuy::addTip(std::string text)
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

void ShopBuy::addTip2(std::string text)
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

void ShopBuy::resetTip()
{
    tip1->setVisible(false);
    jiaoshi->setVisible(false);
    label->setText("");
    jiaoshi->setPosition(ccp(-0.15*SIZE.width,10));
    tip1->setPosition(ccp( -150, -120));
}



