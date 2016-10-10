//
//  ShopScene.cpp
//  king04
//
//  Created by mac on 14-5-15.
//
//
//
#include "ShopScene.h"
#include "HubShop.h"
#include "Game.h"
#include "SelectScene.h"
#include "Dalibao.h"
#include "GameData.h"


CCScene* ShopScene::scene()
{
    CCScene* scene = CCScene::create();
    ShopScene* layer = ShopScene::create();
    scene->addChild(layer);
    return scene;
}

bool ShopScene::init()
{
    if (!BaseLayer::init())
    {
        return false;
    }
    goumaiweizhi = 1;
    bg = CCSprite::create("shopsc/ditu.png");
    this->addChild(bg);
    bg->setPosition(ccp(SIZE.width/2, SIZE.height/2));
    
    nvrole = CCSprite::create("shopsc/nvrole.png");
    this->addChild(nvrole);
    nvrole->setPosition(ccp(SIZE.width*0.28, SIZE.height*0.28));
    nvrole->setAnchorPoint(ccp(0.5, 0));
   
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("shopsc/112121/112121.ExportJson");
    duboji = CCArmature::create("112121");
    this->addChild(duboji);
    duboji->setPosition(ccp(SIZE.width*0.2, SIZE.height*0.28));
    duboji->setAnchorPoint(ccp(0.5, 0));
    duboji->getAnimation()->playWithIndex(0);
    duboji->setScale(1.3f);
    
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("shopsc/baoxiang/baoxiang.ExportJson");
    baoxiang = CCArmature::create("baoxiang");
    this->addChild(baoxiang);
    baoxiang->setPosition(ccp(SIZE.width*0.65, SIZE.height*0.32));
    baoxiang->setAnchorPoint(ccp(0.5, 0));
    baoxiang->getAnimation()->playWithIndex(0);
    baoxiang->setScale(1.3f);
    
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("shopsc/texiao1/texiao1.ExportJson");
    texiao = CCArmature::create("texiao1");
    this->addChild(texiao);
  //  texiao->setPosition(ccp(SIZE.width*0.85, SIZE.height*0.12));
	texiao->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.08));
    texiao->setAnchorPoint(ccp(0.5, 0));
    texiao->getAnimation()->playWithIndex(0);
    texiao->setScale(1.3f);
    
    jinbi = CCSprite::create("shopsc/4321.png");
    jinbi->setPosition(ccp(SIZE.width*0.43, SIZE.height*0.32));
    jinbi->setAnchorPoint(ccp(0.5, 0));
    this->addChild(jinbi);
    jinbi->setScale(1.3f);
    
    jiantou = CCSprite::create("shopsc/5432.png");
    this->addChild(jiantou);
    jiantou->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, 20)),CCMoveBy::create(0.5f, ccp(0, -20)),NULL)) );
    
    jiantou->setPosition(ccpAdd( jinbi->getPosition() , ccp(0,jinbi->getContentSize().height + 25)));
    
    hero = Hero::create();
   // this->addChild(hero, 101, 101);
   // Game::instance()->setShopRole(hero);
    hero->setPosition(ccp(SIZE.width*0.5, SIZE.height*0.15));
    hero->setAnchorPoint(ccp(0.5, 0));
    hero->shadow2 = CCSprite::create("res/yingzi.png");
   // this->addChild(hero->shadow2);
    
    
    HubShop* hub = HubShop::create();
    this->addChild(hub,102,102);
    this->scheduleUpdate();
    

	_tag = NONE_HELP;
	addTip();

    return true;
}

void ShopScene::update(float dt)
{
   // updatePosition(dt);
}

void ShopScene::updatePosition(float dt)
{
    //bool canRight = true;
    //bool canLeft = true;
    //
    //if (hero->getPositionX() < SIZE.width*0.34)
    //{
    //    goumaiweizhi = 0;
    //   
    //    
    //}else if (hero->getPositionX() > SIZE.width*0.34 && hero->getPositionX() < SIZE.width*0.55)
    //{
    //    goumaiweizhi = 1;
    //  
    //    
    //}else if (hero->getPositionX() > SIZE.width*0.55)
    //{
    //    goumaiweizhi = 2;
    //}
    //
    //if (goumaiweizhi != oldgoumaiweizhi)
    //{
    //    oldgoumaiweizhi = goumaiweizhi;
    //    
    //    if (goumaiweizhi == 0)
    //    {
    //        jiantou->setPosition(ccpAdd( duboji->getPosition() , ccp(0,duboji->getContentSize().height*1.3 + 30)));
    //        
    //    }else if (goumaiweizhi == 1)
    //    {
    //        jiantou->setPosition(ccpAdd( jinbi->getPosition() , ccp(0,jinbi->getContentSize().height*1.3 + 25)));
    //        
    //    }else if (goumaiweizhi == 2)
    //    {
    //        jiantou->setPosition(ccpAdd( baoxiang->getPosition() , ccp(0,baoxiang->getContentSize().height*1.2 + 15)));
    //    }
    //}
    //
    //if (hero->getPositionX()<100)
    //{
    //    canLeft = false;
    //}else if (hero->getPositionX() > SIZE.width - 100)
    //{
    //    canRight = false;
    //}
    //
    //int x = 0;
    //int speed = hero->speedMain;
    //switch (hero->orientation) {
    //    case  HOLDER:
    //        x = hero->getPositionX();
    //        if(!hero->oldPosition.equals(ccp(0,0))){
    //            
    //        }
    //        if (!canLeft)
    //        {
    //            x = hero->getPositionX();
    //        }else if (!canRight)
    //        {
    //            
    //        }else
    //        {
    //            
    //        }
    //        break;
    //        
    //    case LEFT:
    //        
    //        if (canLeft  /*&& Role->isBeAttack == false*/)
    //        {
    //            x = hero->getPositionX() - dt*speed;
    //            hero->move();
    //        }else{
    //            x = hero->getPositionX();
    //        }
    //        break;
    //    case RIGHT:
    //        if (canRight /*&& Role->isBeAttack == false*/)
    //        {
    //            x = hero->getPositionX() + dt*speed;
    //            hero->move();
    //        }else{
    //            x = hero->getPositionX();
    //        }
    //        break;
    //    default:
    //        break;
    //}
    //hero->setPositionX(x);
    //if (hero->getBondingBox2().intersectsRect(texiao->boundingBox())  && hero->getPositionX() >texiao->getPositionX() + 10 )
    //{
    //    this->unscheduleAllSelectors();
    //    CCDirector::sharedDirector()->replaceScene(SelectScene::scene());
    //}
}



void ShopScene::dalibao()
{
	if (_tag == SHUXING_HELP&&goumaiweizhi != 2)
		return;
	else if (_tag==SHUXING_HELP&&goumaiweizhi==2)
	{
		_tag = NONE_HELP;
		tip1->setVisible(false);
	}

    if (this->getChildByTag(dalibaotag)!=NULL)
    {
        return;
    }
	if (goumaiweizhi == 0)
	{
		return;
	}

	if (goumaiweizhi == 2)
	{
		PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
		CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
		renderTexture->begin();
		this->visit();
		renderTexture->end();
		CCDirector::sharedDirector()->pushScene(ShopBuy::scene(renderTexture, false));
	}
	else if (goumaiweizhi == 3)
	{
		this->unscheduleAllSelectors();
		CCDirector::sharedDirector()->replaceScene(SelectScene::scene());
	}
	else if (goumaiweizhi != 3)
	{
		Dalibao* dalibao = Dalibao::create(goumaiweizhi);
		dalibao->setPosition(ccp(0, SIZE.height * 1));
		dalibao->runAction(CCEaseIn::create(CCMoveTo::create(0.5f, ccp(0, 0)), 2));
		this->addChild(dalibao, dalibaozorder, dalibaotag);
	}
	
}

void ShopScene::changeSelect(int fangxiang)
{
	if (fangxiang)
		goumaiweizhi = goumaiweizhi + 1 > 3 ? 0 : goumaiweizhi + 1;
	else
		goumaiweizhi = goumaiweizhi - 1 >= 0 ? goumaiweizhi - 1 : 3;

	if (goumaiweizhi == 0)
	{
		jiantou->setPosition(ccpAdd(duboji->getPosition(), ccp(0, duboji->getContentSize().height*1.3 + 30)));

	}
	else if (goumaiweizhi == 1)
	{
		jiantou->setPosition(ccpAdd(jinbi->getPosition(), ccp(0, jinbi->getContentSize().height*1.3 + 25)));

	}
	else if (goumaiweizhi == 2)
	{
		jiantou->setPosition(ccpAdd(baoxiang->getPosition(), ccp(0, baoxiang->getContentSize().height*1.2 + 15)));
	}
	else if (goumaiweizhi == 3)
	{
		jiantou->setPosition(ccpAdd(texiao->getPosition(), ccp(0, texiao->getContentSize().height*1.2 + 15)));
	}

}


void ShopScene::addTip()
{
	if (!KingData->getFirstTishiShuxing())
	{
		CCPoint pos = baoxiang->getPosition();
		CCSprite* help = CCSprite::create("help11.png");
		help->setPosition(CCPoint(pos.x, pos.y + 100));
		help->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, 30)), CCMoveBy::create(0.3f, ccp(0, -30)), NULL)));
		this->addChild(help);

		addDialog();

		_tag = SHUXING_HELP;
		KingData->setFirstTishiShuxing(true);
	}

}



void ShopScene::addDialog()
{
	tip1 = CCSprite::create("duihuakuang/UI80.png");
	jiaoshi = CCSprite::create("duihuakuang/jiaoshi.png");
	this->addChild(jiaoshi, 9999999);
	this->addChild(tip1, 999999);
	jiaoshi->setPosition(ccp(-0.15*SIZE.width, 10));
	jiaoshi->setAnchorPoint(ccp(0.5, 0));
	tip1->setPosition(ccp(-150, -120));
	label = UILabel::create();
	tip1->addChild(label);
	label->setFontName("ËÎÌו");
	label->setFontSize(20);
	label->setPosition(ccp(120, tip1->getContentSize().height));
	label->setAnchorPoint(ccp(0, 1));
	label->setColor(ccc3(241, 191, 194));
	label->setTextAreaSize(CCSize(200, 150));
	label->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);



	jiaoshi->setFlipX(false);
	tip1->runAction(CCMoveTo::create(0.2f, ccp(410, 70)));
	jiaoshi->runAction(CCSequence::create(CCDelayTime::create(0.2f), CCMoveTo::create(0.2f, ccp(SIZE.width*0.085, 2))
		, NULL));

	label->setPosition(ccp(220, tip1->getContentSize().height));
	tip1->setVisible(true);
	jiaoshi->setVisible(true);
	label->setText(XXIconv::GBK2UTF(TIP[7].c_str()));
}