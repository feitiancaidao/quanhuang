//
//  LoadingLayer.cpp
//  king04
//
//  Created by mac on 14-5-15.
//
//
#include "GameScene.h"
#include "LoadingLayer.h"
#include "Define.h"
#include "XXIconv.h"
#include"TextInfos.h"

bool LoadingLayer::init(int current_Select, int modeid)
{
    if ( !BaseLayer::init() )
    {
        return false;
    }
    this->current_Select = current_Select;
    this->modeid = modeid;
    char json[50] = {0};
    sprintf( json, "%s/%s.ExportJson","meinvdazhan","meinvdazhan");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(json);
    meinv = CCArmature::create("meinvdazhan");
    meinv->getAnimation()->playWithIndex(0);
    this->addChild(meinv);
    meinv->setPosition(ccp(SIZE.width/2, SIZE.height*0.53));
    meinv->setAnchorPoint(ccp(0.5, 0.5));
    
    label = UILabel::create();
    label->setFontName("宋体");
    label->setFontSize(20);
    label->setPosition(ccp(SIZE.width/2, SIZE.height*0.35));
    label->setAnchorPoint(ccp(0.5, 1));
    label->setColor(ccc3(0xee, 0xee, 0xee));
    //label->setTextAreaSize(CCSize(260,100));
    
    int ran = CCRANDOM_0_1()*5;
    
   // label->setText(XXIconv::GBK2UTF(loadingTips[ran].c_str()));
	label->setText(XXIconv::GBK2UTF("Loading      "));
	
    this->addChild(label);
    
	this->schedule(schedule_selector(LoadingLayer::Loading_During), 0.3f);
    this->scheduleOnce(schedule_selector(LoadingLayer::Loading_Over), 3.0f);
    return true;
}

CCScene* LoadingLayer::scene(int current_Select, int modeid)
{
    CCScene *scene = CCScene::create();
    LoadingLayer *layer = LoadingLayer::create(current_Select,modeid);
    scene->addChild(layer);
    return scene;
}

LoadingLayer* LoadingLayer::create(int current_Select, int modeid)
{
    LoadingLayer* LAYER = new LoadingLayer();
    LAYER->init(current_Select, modeid);
    LAYER->autorelease();
    return LAYER;
}

void LoadingLayer::loadingBack(CCObject* pSender)
{
    
}

void LoadingLayer::Loading_During(float dt)
{
	static int dot_Nums = 1;
	dot_Nums = dot_Nums < 5 ? dot_Nums + 1 : 1;

	std::string str("Loading ");
	for (int i = 0; i < 5; i++)
	{
		if (i < dot_Nums)
			str += ".";
		else
			str += " ";
	}
	label->setText(str);
}


void LoadingLayer::Loading_Over(float dt)
{
    CCDirector::sharedDirector()->replaceScene(GameScene::scene(current_Select,modeid));
}


